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

BanTokenUsageASTVisitor::BanTokenUsageASTVisitor(BugReporter &B) : BR(B) {
}

bool BanTokenUsageASTVisitor::VisitDecl(clang::Decl *D) {
    llvm::outs() << "Decl:\n";
    D->print(llvm::outs(), 0, false);
    llvm::outs() << "\n---\n";
    return true;
}

bool BanTokenUsageASTVisitor::VisitType(clang::Type *T) {
    //    T->print(llvm::outs(), 0, false);
    llvm::outs() << "Type " << T->getTypeClassName() << "\n";
    return true;
}

bool BanTokenUsageASTVisitor::VisitStmt(clang::Stmt *S) {
    //    S->print(llvm::outs(), 0, false);
    llvm::outs() << "Stmt " << S->getStmtClassName() << "\n";
    SourceLocation sl = S->getBeginLoc();
    const SourceManager &sm = BR.getSourceManager();
    Preprocessor &pp = BR.getPreprocessor();
    llvm::outs() << "Stmt " << sl.printToString(sm) << "\n";
    SourceRange sr = S->getSourceRange();
    llvm::outs() << "Stmt " << sr.printToString(sm) << "\n";
    const LangOptions &LO = BR.getContext().getLangOpts();

    auto CharRange = Lexer::getAsCharRange(sr, sm, LO);

    auto StringRep = Lexer::getSourceText(CharRange, sm, LO);
    llvm::errs() << "StmtX:" << StringRep << "\n";
    Token result;
    if (!pp.getRawToken(sl, result)) {
        llvm::outs() << "Got a token!\n";
    }

    if (sl.isMacroID()) {
        llvm::outs() << "Is a macro!\n";
    }
    llvm::outs() << "------< END STMT\n";
    return true;
}

bool BanTokenUsageASTVisitor::VisitAttr(clang::Attr *A) {
    //    A->print(llvm::outs(), 0, false);
    llvm::outs() << "Attr\n";
    return true;
}
bool BanTokenUsageASTVisitor::VisitTypeLoc(clang::TypeLoc TL) {
    //   TL->print(llvm::outs(), 0, false);
    llvm::outs() << "TypeLoc\n";
    return true;
}
bool BanTokenUsageASTVisitor::VisitQualifiedTypeLoc(clang::QualifiedTypeLoc TL) {
    //    TL->print(llvm::outs(), 0, false);
    llvm::outs() << "QalTypeLoc\n";
    return true;
}
bool BanTokenUsageASTVisitor::VisitUnqualTypeLoc(clang::UnqualTypeLoc TL) {
    //   TL->print(llvm::outs(), 0, false);
    llvm::outs() << "UnqalTypeLoc\n";
    return true;
}
