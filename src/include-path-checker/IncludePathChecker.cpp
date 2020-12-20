#include <clang/AST/AST.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendPluginRegistry.h>
#include <clang/Lex/PPCallbacks.h>

using namespace clang;
using namespace ento;

namespace {

class CheckIncludePath : public clang::PPCallbacks {
    CompilerInstance &CI;

  public:
    CheckIncludePath(CompilerInstance &CI) : clang::PPCallbacks(), CI(CI) {
    }

    virtual void InclusionDirective(clang::SourceLocation HashLoc, const clang::Token &IncludeTok,
                                    clang::StringRef FileName, bool IsAngled,
                                    clang::CharSourceRange FilenameRange,
                                    const clang::FileEntry *File, clang::StringRef SearchPath,
                                    clang::StringRef RelativePath, const clang::Module *Imported,
                                    clang::SrcMgr::CharacteristicKind FileType) {

        if (FileName.find("../") != clang::StringRef::npos) {
            DiagnosticsEngine &diagEngine = CI.getDiagnostics();
            const unsigned DiagID = diagEngine.getCustomDiagID(
                DiagnosticsEngine::Error, "Found use of relative path to include '%0'");
            diagEngine.Report(HashLoc, DiagID) << FileName.str();
        }
    }
};

class IncludePathCheckerAction : public clang::PluginASTAction {
  public:
    IncludePathCheckerAction() {
    }

    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &ci,
                                                          llvm::StringRef InFile) override {
        return std::make_unique<clang::ASTConsumer>();
    }

    bool BeginSourceFileAction(CompilerInstance &CI) override {
        clang::Preprocessor &preprocessor = CI.getPreprocessor();
        preprocessor.addPPCallbacks(std::make_unique<CheckIncludePath>(CI));
        return true;
    }

    bool ParseArgs(const clang::CompilerInstance &ci,
                   const std::vector<std::string> &args) override {
        return true;
    }

  protected:
    clang::PluginASTAction::ActionType getActionType() override {
        return ReplaceAction;
    }
};

}; // namespace

static clang::FrontendPluginRegistry::Add<IncludePathCheckerAction>
    PLUGIN_REGISTRATION("include-path-checker",
                        "Identifies where paths have been used in include directives");