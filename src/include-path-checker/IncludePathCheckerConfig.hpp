#if !defined(INCLUDE_PATH_CHECKER_CONFIG_HPP)
#define INCLUDE_PATH_CHECKER_CONFIG_HPP

#include "BanStringConfig.hpp"
#include "ConfigBase.hpp"

namespace brighttools {

class IncludePathCheckerConfig {
  public:
    static llvm::Optional<IncludePathCheckerConfig> readConfig(llvm::StringRef file);

    bool disallowParentDirIncludeReferences;
    bool disallowChildDirIncludeReferences;
    bool allowChildDirSystemHeaderIncludeReferences;
    BanStringConfig bannedFiles;
};

} // namespace brighttools

#endif // INCLUDE_PATH_CHECKER_CONFIG_HPP