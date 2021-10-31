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

#include "BanStringConfig.hpp"

using namespace brighttools;

namespace {

class PrintFunctionsConsumer : public clang::ASTConsumer {
  public:
    PrintFunctionsConsumer(clang::CompilerInstance &Instance, std::shared_ptr<BanStringConfig> cfg)
        : CI(Instance), config(cfg) {
        addPreProcessorHook();
    }

  private:
    const clang::CompilerInstance &CI;
    std::shared_ptr<BanStringConfig> config;

    void checkLocation(const clang::Token &tok, clang::SourceLocation origLocation,
                       clang::SourceLocation currentLocation) {
        const clang::SourceManager &sm = CI.getSourceManager();

        const bool isCurrentLocationMacro = currentLocation.isMacroID();

        if (isCurrentLocationMacro) {
            currentLocation = sm.getExpansionLoc(currentLocation);
        }

        const clang::StringRef tokenString = getTokenString(currentLocation);

        if (isCurrentLocationMacro) {
            checkMacro(tokenString, currentLocation);
        }

        raiseErrorsIfTokenBanned(tokenString, currentLocation);
    }

    clang::StringRef getTokenString(clang::SourceLocation currentLocation) {
        const clang::SourceManager &sm = CI.getSourceManager();
        const clang::LangOptions &LO = CI.getLangOpts();
        auto cr = clang::Lexer::getAsCharRange(currentLocation, sm, LO);
        return clang::Lexer::getSourceText(cr, sm, LO);
    }

    void checkMacro(const clang::StringRef &token, clang::SourceLocation origLocation) {
        const clang::Preprocessor &pp = CI.getPreprocessor();
        const clang::IdentifierInfo *const ii = pp.getIdentifierInfo(token);
        const clang::MacroInfo *const mi = pp.getMacroInfo(ii);
        for (auto macroToken = mi->tokens_begin(); macroToken != mi->tokens_end(); macroToken++) {
            checkLocation(*macroToken, origLocation, macroToken->getLocation());
        }
    }

    void raiseErrorsIfTokenBanned(const clang::StringRef &token, clang::SourceLocation location) {
        std::string reason;
        const clang::SourceManager &sm = CI.getSourceManager();
        const std::string fileName = sm.getFilename(location).str();

        if (config->isStringBanned(token, fileName, &reason)) {
            clang::DiagnosticsEngine &diagEngine = CI.getDiagnostics();
            if (reason.length()) {
                const unsigned diagID =
                    diagEngine.getCustomDiagID(clang::DiagnosticsEngine::Error,
                                               "Found use of banned token '%0'.\nBan reason: %1");
                diagEngine.Report(location, diagID) << token << reason;
            } else {
                const unsigned diagID = diagEngine.getCustomDiagID(
                    clang::DiagnosticsEngine::Error, "Found use of banned token '%0'.");
                diagEngine.Report(location, diagID) << token;
            }
        }
    }

    void addPreProcessorHook() {
        CI.getPreprocessor().setTokenWatcher([this](const clang::Token &tok) {
            const clang::SourceLocation sl = tok.getLocation();
            checkLocation(tok, sl, sl);
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

        llvm::Optional<BanStringConfig> loadedConfig =
            findConfigInDirectoryHeirachy<BanStringConfig>(".ban-pp-tokens.yml");
        if (!loadedConfig) {
            return false;
        }
        config = std::make_shared<BanStringConfig>(*loadedConfig);
        return true;
    }

  protected:
    clang::PluginASTAction::ActionType getActionType() override {
        return AddBeforeMainAction;
    }

  private:
    std::shared_ptr<BanStringConfig> config = nullptr;
};

}; // namespace

static clang::FrontendPluginRegistry::Add<BanPPTokensAction>
    PLUGIN_REGISTRATION("ban-pp-tokens",
                        "Check for (and raise an error upon) banned tokens being found");
