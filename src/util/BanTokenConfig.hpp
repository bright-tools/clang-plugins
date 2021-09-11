#if !defined(BAN_TOKEN_CONFIG_HPP)
#define BAN_TOKEN_CONFIG_HPP

#include "ConfigBase.hpp"

#include <llvm/Support/Regex.h>

namespace brighttools {

class BanTokenConfig {
  public:
    typedef struct {
      std::string token;
      std::string reason;
      std::string whitelistRegexString;
      std::shared_ptr<llvm::Regex> whitelistRegex;
      std::string blacklistRegexString;
      std::shared_ptr<llvm::Regex> blacklistRegex;
    } BannedToken;

    static llvm::Optional<BanTokenConfig> readConfig(llvm::StringRef file);

    bool isTokenBanned(const llvm::StringRef tokenToCheck, const std::string fileName, std::string* const reason = NULL) const;

    std::vector<BannedToken> bannedTokens;
  private:
    static void populateRegexCache(BanTokenConfig* const config);
};

} // namespace brighttools

#endif // BAN_TOKEN_USAGE_CONFIG_HPP