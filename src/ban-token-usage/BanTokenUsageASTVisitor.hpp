#if !defined BAN_PP_TOKENS_AST_VISITOR_HPP
#define BAN_PP_TOKENS_AST_VISITOR_HPP

#include <clang/AST/DeclBase.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/StaticAnalyzer/Core/BugReporter/BugReporter.h>

namespace brighttools {
class BanTokenUsageASTVisitor : public clang::RecursiveASTVisitor<BanTokenUsageASTVisitor> {
    clang::ento::BugReporter &BR;

  public:
    explicit BanTokenUsageASTVisitor(clang::ento::BugReporter &B);
    bool VisitDecl(clang::Decl *D);
    bool VisitType(clang::Type *T);
    bool VisitAttr(clang::Attr *A);
    bool VisitStmt(clang::Stmt *S);
    bool VisitTypeLoc(clang::TypeLoc TL);
    bool VisitQualifiedTypeLoc(clang::QualifiedTypeLoc TL);
    bool VisitUnqualTypeLoc(clang::UnqualTypeLoc TL);
};
} // namespace brighttools

#endif // BAN_PP_TOKENS_AST_VISITOR_HPP