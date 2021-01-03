#if !defined(BAN_TOKEN_USAGE_CONFIG_HPP)
#define BAN_TOKEN_USAGE_CONFIG_HPP

#include "ConfigBase.hpp"

namespace brighttools {

class BanTokenUsageConfig {
  public:
    static llvm::Optional<BanTokenUsageConfig> readConfig(llvm::StringRef file);

    std::vector<std::string> bannedTokens;
};

} // namespace brighttools

#endif // BAN_TOKEN_USAGE_CONFIG_HPP