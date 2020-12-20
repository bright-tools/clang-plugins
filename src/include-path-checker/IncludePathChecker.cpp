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

using namespace clang;

namespace {

class CheckIncludePath : public clang::PPCallbacks {
    CompilerInstance &CI;
    bool disallowParentDirRefs;

  public:
    CheckIncludePath(CompilerInstance &CI, bool disallowParentDirRefs)
        : clang::PPCallbacks(), CI(CI), disallowParentDirRefs(disallowParentDirRefs) {
    }

    virtual void InclusionDirective(clang::SourceLocation HashLoc, const clang::Token &IncludeTok,
                                    clang::StringRef FileName, bool IsAngled,
                                    clang::CharSourceRange FilenameRange,
                                    const clang::FileEntry *File, clang::StringRef SearchPath,
                                    clang::StringRef RelativePath, const clang::Module *Imported,
                                    clang::SrcMgr::CharacteristicKind FileType) {

        if (disallowParentDirRefs) {
            const bool hasParentDirRef = (FileName.find("../") != clang::StringRef::npos) ||
                                         (FileName.find("..\\") != clang::StringRef::npos);
            if (hasParentDirRef) {
                DiagnosticsEngine &diagEngine = CI.getDiagnostics();
                const unsigned DiagID = diagEngine.getCustomDiagID(
                    DiagnosticsEngine::Error, "Found use of relative path to include '%0'");
                diagEngine.Report(HashLoc, DiagID) << FileName.str();
            }
        }
    }
};

class IncludePathCheckerAction : public clang::PluginASTAction {
  public:
    IncludePathCheckerAction() : disallowParentDirRefs(false) {
    }

    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &ci,
                                                          llvm::StringRef InFile) override {
        return std::make_unique<clang::ASTConsumer>();
    }

    bool BeginSourceFileAction(CompilerInstance &CI) override {
        clang::Preprocessor &preprocessor = CI.getPreprocessor();
        preprocessor.addPPCallbacks(std::make_unique<CheckIncludePath>(CI, disallowParentDirRefs));
        return true;
    }

    bool ParseArgs(const clang::CompilerInstance &ci,
                   const std::vector<std::string> &args) override {

        for (unsigned i = 0, e = args.size(); i != e; ++i) {
            if (args[i] == "-disallow-parent-dir-include-references") {
                disallowParentDirRefs = true;
            }
        }
        return true;
    }

  protected:
    clang::PluginASTAction::ActionType getActionType() override {
        return ReplaceAction;
    }

  private:
    bool disallowParentDirRefs;
};

}; // namespace

static clang::FrontendPluginRegistry::Add<IncludePathCheckerAction>
    PLUGIN_REGISTRATION("include-path-checker",
                        "Identifies where paths have been used in include directives");
