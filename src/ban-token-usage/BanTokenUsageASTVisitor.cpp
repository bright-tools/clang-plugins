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

#include "clang/Lex/Lexer.h"

#include "BanTokenUsageASTVisitor.hpp"

using namespace clang;
using namespace ento;
using namespace brighttools;

BanTokenUsageASTVisitor::BanTokenUsageASTVisitor(const CheckerBase &CB, BanTokenConfig config)
    : CB(CB), config(config) {
}

bool BanTokenUsageASTVisitor::AnalyseDecl(const clang::Decl *const D,
                                          clang::ento::AnalysisManager &AM,
                                          clang::ento::BugReporter &BR) {
    const unsigned declStartRaw = D->getBeginLoc().getRawEncoding();
    const unsigned declEndRaw = D->getEndLoc().getRawEncoding();
    const SourceManager &sm = BR.getSourceManager();
    const SourceRange sr = D->getSourceRange();
    Preprocessor &pp = BR.getPreprocessor();
    const LangOptions &LO = pp.getLangOpts();

    for (unsigned i = declStartRaw; i < declEndRaw;) {
        const SourceLocation tokenLocation = SourceLocation::getFromRawEncoding(i);
        const CharSourceRange tokenCharRange = clang::Lexer::getAsCharRange(tokenLocation, sm, LO);
        const StringRef tokenString = clang::Lexer::getSourceText(tokenCharRange, sm, LO);
        const std::string fileName = sm.getFilename(tokenLocation).str();
        std::string reason;

        if (config.isTokenBanned(tokenString, fileName, &reason)) {

            PathDiagnosticLocation diagnosticLocation(tokenLocation, BR.getSourceManager());
            SmallString<256> S;
            llvm::raw_svector_ostream os(S);
            os << "Banned token '" << tokenString << "'";
            if (reason.length()) {
                os << " (Ban reason: " << reason << ")";
            }
            BR.EmitBasicReport(D, &CB, "Banned token used in code", "Banned token used in code",
                               os.str(), diagnosticLocation, sr);
        }

        i += std::max((size_t)1, tokenString.size());
    }
    return true;
}
