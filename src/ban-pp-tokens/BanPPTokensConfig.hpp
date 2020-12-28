#if !defined(BAN_PP_TOKENS_CONFIG_HPP)
#define BAN_PP_TOKENS_CONFIG_HPP

#include <llvm/Support/YAMLParser.h>

namespace brighttools {

class BanPPTokensConfig {
  public:
    static std::shared_ptr<BanPPTokensConfig> readConfig();

    std::vector<std::string> bannedTokens;
};

} // namespace brighttools

#endif // BAN_PP_TOKENS_CONFIG_HPP