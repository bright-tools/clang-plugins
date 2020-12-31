#if !defined(BAN_PP_TOKENS_CONFIG_HPP)
#define BAN_PP_TOKENS_CONFIG_HPP

#include "ConfigBase.hpp"

namespace brighttools {

class BanPPTokensConfig {
  public:
    static llvm::Optional<BanPPTokensConfig> readConfig(llvm::StringRef file);

    std::vector<std::string> bannedTokens;
};

} // namespace brighttools

#endif // BAN_PP_TOKENS_CONFIG_HPP