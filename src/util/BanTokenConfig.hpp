#if !defined(BAN_TOKEN_CONFIG_HPP)
#define BAN_TOKEN_CONFIG_HPP

#include "ConfigBase.hpp"

namespace brighttools {

class BanTokenConfig {
  public:
    static llvm::Optional<BanTokenConfig> readConfig(llvm::StringRef file);

    bool isTokenBanned(const llvm::StringRef tokenToCheck) const;

    std::vector<std::string> bannedTokens;
};

} // namespace brighttools

#endif // BAN_TOKEN_USAGE_CONFIG_HPP