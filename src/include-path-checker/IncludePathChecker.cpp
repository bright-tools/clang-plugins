/* Copyright 2020 John Bailey

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "IncludePathCheckerConfig.hpp"

#include <clang/AST/AST.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendPluginRegistry.h>
#include <clang/Lex/PPCallbacks.h>
#include <clang/Basic/FileManager.h>

using namespace brighttools;

namespace {

class CheckIncludePath : public clang::PPCallbacks {

  public:
    CheckIncludePath(const clang::CompilerInstance &CI, IncludePathCheckerConfig &config)
        : clang::PPCallbacks(), CI(CI), config(config) {
        initialiseDiagnosticIds();
    }

    virtual void InclusionDirective(clang::SourceLocation HashLoc, const clang::Token &IncludeTok,
                                    clang::StringRef FileName, bool IsAngled,
                                    clang::CharSourceRange FilenameRange,
                                    const clang::FileEntry *File, clang::StringRef SearchPath,
                                    clang::StringRef RelativePath, const clang::Module *Imported,
                                    clang::SrcMgr::CharacteristicKind FileType) {

        clang::SourceManager &sm = CI.getSourceManager();

        const bool isIncludedFromSysHeader = sm.isInSystemHeader(HashLoc);

        if (!isIncludedFromSysHeader) {

            bool shouldReportDiagnostic = false;

            if (config.disallowParentDirIncludeReferences) {
                shouldReportDiagnostic = (FileName.find("../") != clang::StringRef::npos) ||
                                         (FileName.find("..\\") != clang::StringRef::npos);
            }
            if (!shouldReportDiagnostic && config.disallowChildDirIncludeReferences) {
                shouldReportDiagnostic = (FileName.find("/") != clang::StringRef::npos) ||
                                         (FileName.find("\\") != clang::StringRef::npos);

                const bool isSystemHeader = (clang::SrcMgr::CharacteristicKind::C_System == FileType) || (clang::SrcMgr::CharacteristicKind::C_ExternCSystem  == FileType);

                 if (isSystemHeader && config.allowChildDirSystemHeaderIncludeReferences) {
                     shouldReportDiagnostic = false;
                 }
            }

            clang::DiagnosticsEngine &diagEngine = CI.getDiagnostics();

            if (shouldReportDiagnostic) {
                diagEngine.Report(HashLoc, foundRelativePathDiagId) << FileName.str();
            }

            const llvm::StringRef importingFile = sm.getFilename(HashLoc);

            std::string reason;
            if(config.bannedFiles.isStringBanned(FileName, importingFile.str(), &reason, includeCompare)) {
                if (reason.empty()) {
                    diagEngine.Report(HashLoc, bannedIncludeDiagId) << FileName.str();
                } else {
                    diagEngine.Report(HashLoc, bannedIncludeWithReasonDiagId) << FileName.str() << reason;
                }
            }
        }
    }

  private:
    const clang::CompilerInstance &CI;
    IncludePathCheckerConfig config;
    unsigned foundRelativePathDiagId;
    unsigned bannedIncludeDiagId;
    unsigned bannedIncludeWithReasonDiagId;

    void initialiseDiagnosticIds() {
        clang::DiagnosticsEngine &diagEngine = CI.getDiagnostics();
        foundRelativePathDiagId = diagEngine.getCustomDiagID(
            clang::DiagnosticsEngine::Error, "Found use of relative path to include '%0'");
        bannedIncludeDiagId = diagEngine.getCustomDiagID(
            clang::DiagnosticsEngine::Error, "Found use of banned include '%0'");
        bannedIncludeWithReasonDiagId = diagEngine.getCustomDiagID(
            clang::DiagnosticsEngine::Error, "Found use of banned include '%0', ban reason: %1");
    }

    static bool includeCompare(llvm::StringRef stringToCheck, const std::string& bannedString) {
        return (stringToCheck == bannedString) ||
               stringToCheck.endswith("/"+bannedString) ||
               stringToCheck.endswith("\\"+bannedString);
    }
};

class IncludePathCheckerAction : public clang::PluginASTAction {
  public:
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &CI,
                                                          llvm::StringRef InFile) override {
        return std::make_unique<clang::ASTConsumer>();
    }

    bool ParseArgs(const clang::CompilerInstance &CI,
                   const std::vector<std::string> &args) override {

        llvm::Optional<IncludePathCheckerConfig> loadedConfig =
            findConfigInDirectoryHeirachy<IncludePathCheckerConfig>(".include-path-checker.yml");
        if (!loadedConfig) {
            return true;
        }
        addPreProcessorHook(CI, *loadedConfig);
        return true;
    }

  protected:
    clang::PluginASTAction::ActionType getActionType() override {
        return AddBeforeMainAction;
    }

  private:

    void addPreProcessorHook(const clang::CompilerInstance &CI, IncludePathCheckerConfig config) {
        clang::Preprocessor &preprocessor = CI.getPreprocessor();
        preprocessor.addPPCallbacks(std::make_unique<CheckIncludePath>(CI, config));
    }
};

}; // namespace

static clang::FrontendPluginRegistry::Add<IncludePathCheckerAction>
    PLUGIN_REGISTRATION("include-path-checker",
                        "Identifies where paths have been used in include directives");
