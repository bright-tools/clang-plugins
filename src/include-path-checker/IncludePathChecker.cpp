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

#include <clang/AST/AST.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendPluginRegistry.h>
#include <clang/Lex/PPCallbacks.h>

namespace {

class CheckIncludePath : public clang::PPCallbacks {

  public:
    typedef struct {
        bool disallowParentDirRefs = false;
        bool disallowChildDirRefs = false;
    } CheckIncludePathConfigOptions;

    CheckIncludePath(const clang::CompilerInstance &CI, CheckIncludePathConfigOptions &config)
        : clang::PPCallbacks(), CI(CI), config(config) {
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

            if (config.disallowParentDirRefs) {
                shouldReportDiagnostic = (FileName.find("../") != clang::StringRef::npos) ||
                                         (FileName.find("..\\") != clang::StringRef::npos);
            }
            if (!shouldReportDiagnostic && config.disallowChildDirRefs) {
                shouldReportDiagnostic = (FileName.find("/") != clang::StringRef::npos) ||
                                         (FileName.find("\\") != clang::StringRef::npos);
            }
            if (shouldReportDiagnostic) {
                clang::DiagnosticsEngine &diagEngine = CI.getDiagnostics();
                const unsigned diagID = diagEngine.getCustomDiagID(
                    clang::DiagnosticsEngine::Error, "Found use of relative path to include '%0'");
                diagEngine.Report(HashLoc, diagID) << FileName.str();
            }
        }
    }

  private:
    const clang::CompilerInstance &CI;
    const CheckIncludePathConfigOptions config;
};

class IncludePathCheckerAction : public clang::PluginASTAction {
  public:
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &CI,
                                                          llvm::StringRef InFile) override {
        return std::make_unique<clang::ASTConsumer>();
    }

    bool ParseArgs(const clang::CompilerInstance &CI,
                   const std::vector<std::string> &args) override {

        bool shouldInstallHook = false;

        for (unsigned i = 0, e = args.size(); i != e; ++i) {
            if (args[i] == "-disallow-parent-dir-include-references") {
                config.disallowParentDirRefs = true;
                shouldInstallHook = true;
            } else if (args[i] == "-disallow-child-dir-include-references") {
                config.disallowChildDirRefs = true;
                shouldInstallHook = true;
            }
        }

        if (shouldInstallHook) {
            addPreProcessorHook(CI);
        }

        return true;
    }

  protected:
    clang::PluginASTAction::ActionType getActionType() override {
        return AddBeforeMainAction;
    }

  private:
    void addPreProcessorHook(const clang::CompilerInstance &CI) {
        clang::Preprocessor &preprocessor = CI.getPreprocessor();
        preprocessor.addPPCallbacks(std::make_unique<CheckIncludePath>(CI, config));
    }

    CheckIncludePath::CheckIncludePathConfigOptions config;
};

}; // namespace

static clang::FrontendPluginRegistry::Add<IncludePathCheckerAction>
    PLUGIN_REGISTRATION("include-path-checker",
                        "Identifies where paths have been used in include directives");
