#if !defined BAN_PP_TOKENS_AST_VISITOR_HPP
#define BAN_PP_TOKENS_AST_VISITOR_HPP

#include <clang/StaticAnalyzer/Core/BugReporter/BugReporter.h>
#include <clang/StaticAnalyzer/Core/PathSensitive/AnalysisManager.h>

#include "BanStringConfig.hpp"

namespace brighttools {

class BanTokenUsageASTVisitor {

  private:
    const clang::ento::CheckerBase &CB;
    BanStringConfig config;

  public:
    explicit BanTokenUsageASTVisitor(const clang::ento::CheckerBase &CB, BanStringConfig config);
    bool AnalyseDecl(const clang::Decl *const D, clang::ento::AnalysisManager &AM,
                     clang::ento::BugReporter &BR);
};
} // namespace brighttools

#endif // BAN_PP_TOKENS_AST_VISITOR_HPP