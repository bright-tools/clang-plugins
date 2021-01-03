#if !defined BAN_PP_TOKENS_AST_VISITOR_HPP
#define BAN_PP_TOKENS_AST_VISITOR_HPP

#include <clang/AST/DeclBase.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/StaticAnalyzer/Core/BugReporter/BugReporter.h>
#include <clang/StaticAnalyzer/Core/PathSensitive/AnalysisManager.h>

#include "BanTokenUsageConfig.hpp"

namespace brighttools {

class BanTokenUsageASTVisitor : public clang::RecursiveASTVisitor<BanTokenUsageASTVisitor> {
  
  private:
    const clang::ento::CheckerBase &CB;
    const BanTokenUsageConfig config;

  public:
    explicit BanTokenUsageASTVisitor(const clang::ento::CheckerBase &CB,
                                     BanTokenUsageConfig config);
    bool AnalyseDecl(const clang::Decl *const D, clang::ento::AnalysisManager &AM,
                     clang::ento::BugReporter &BR);
};
} // namespace brighttools

#endif // BAN_PP_TOKENS_AST_VISITOR_HPP