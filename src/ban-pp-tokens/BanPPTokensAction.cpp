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

#include "clang/Basic/SourceLocation.h"
#include "clang/Lex/Token.h"
#include <clang/AST/AST.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendPluginRegistry.h>
#include <clang/Lex/PPCallbacks.h>
#include <llvm/Support/MemoryBuffer.h>

#include "BanPPTokensConfig.hpp"

using namespace brighttools;

namespace {

class PrintFunctionsConsumer : public clang::ASTConsumer {
  public:
    PrintFunctionsConsumer(clang::CompilerInstance &Instance,
                           std::shared_ptr<BanPPTokensConfig> cfg)
        : CCI(Instance), config(cfg) {
        addPreProcessorHook();
    }

  private:
    const clang::CompilerInstance &CCI;
    std::shared_ptr<BanPPTokensConfig> config;

    void addPreProcessorHook() {
        CCI.getPreprocessor().setTokenWatcher([this](const clang::Token &tok) {
            clang::SourceLocation sl = tok.getLocation();
            const clang::SourceManager &sm = CCI.getSourceManager();

            if (sl.isMacroID()) {
                sl = sm.getFileLoc(sl);
            }

            const clang::LangOptions &LO = CCI.getLangOpts();
            auto cr = clang::Lexer::getAsCharRange(sl, sm, LO);
            auto tokenString = clang::Lexer::getSourceText(cr, sm, LO);

            for (auto bannedToken : config->bannedTokens) {
                if (tokenString == bannedToken) {
                    clang::DiagnosticsEngine &diagEngine = CCI.getDiagnostics();
                    const unsigned diagID = diagEngine.getCustomDiagID(
                        clang::DiagnosticsEngine::Error, "Found use of banned token '%0'");
                    diagEngine.Report(sl, diagID) << tokenString;
                }
            }
        });
    }
};

class BanPPTokensAction : public clang::PluginASTAction {
  public:
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &CI,
                                                          llvm::StringRef InFile) override {
        assert(config != nullptr && "No config");
        return std::make_unique<PrintFunctionsConsumer>(CI, config);
    }

    bool ParseArgs(const clang::CompilerInstance &CI,
                   const std::vector<std::string> &args) override {

        config = BanPPTokensConfig::readConfig();
        return true;
    }

  protected:
    clang::PluginASTAction::ActionType getActionType() override {
        return AddBeforeMainAction;
    }

  private:
    std::shared_ptr<BanPPTokensConfig> config = nullptr;
};

}; // namespace

static clang::FrontendPluginRegistry::Add<BanPPTokensAction>
    PLUGIN_REGISTRATION("include-path-checker",
                        "Identifies where paths have been used in include directives");
