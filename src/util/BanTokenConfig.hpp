#if !defined(BAN_TOKEN_CONFIG_HPP)
#define BAN_TOKEN_CONFIG_HPP

#include "ConfigBase.hpp"

namespace brighttools {

class BanTokenConfig {
  public:
    typedef struct {
      std::string token;
      std::string reason;
      std::string whitelistRegex;
    } BannedToken;

    static llvm::Optional<BanTokenConfig> readConfig(llvm::StringRef file);

    bool isTokenBanned(const llvm::StringRef tokenToCheck, const std::string fileName, std::string* const reason = NULL) const;

    std::vector<BannedToken> bannedTokens;
};

} // namespace brighttools

#endif // BAN_TOKEN_USAGE_CONFIG_HPP