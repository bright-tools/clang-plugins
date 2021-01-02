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
#include <clang/StaticAnalyzer/Core/Checker.h>
#include <clang/StaticAnalyzer/Core/PathSensitive/AnalysisManager.h>
#include <clang/StaticAnalyzer/Frontend/CheckerRegistry.h>

#include "BanTokenUsageASTVisitor.hpp"

using namespace clang;
using namespace ento;

namespace {

class BanTokenUsageChecker : public Checker<check::ASTCodeBody> {
  public:
    BanTokenUsageChecker() {
    }

    void checkASTCodeBody(const Decl *D, AnalysisManager &AM, BugReporter &BR) const {
        brighttools::BanTokenUsageASTVisitor visitor(BR);
        visitor.TraverseDecl(const_cast<Decl *>(D));
    }
};

}; // namespace

constexpr const char *CHECKER_PLUGIN_NAME = "brighttools.ban-token-usage";

extern "C" const char clang_analyzerAPIVersionString[] = CLANG_ANALYZER_API_VERSION_STRING;

extern "C" void clang_registerCheckers(CheckerRegistry &registry) {
    registry.addChecker<BanTokenUsageChecker>(
        CHECKER_PLUGIN_NAME,
        "Check for (and raise an error upon) banned pre-processor tokens being found (e.g. an "
        "error-prone macro)",
        "https://github.com/bright-tools/clang-plugins", false);
}