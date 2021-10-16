#if !defined(BAN_STRING_CONFIG_HPP)
#define BAN_STRING_CONFIG_HPP

#include "BannedString.hpp"
#include "ConfigBase.hpp"

#include <llvm/Support/YAMLTraits.h>

namespace brighttools {

class BanStringConfig {
  public:
    static llvm::Optional<BanStringConfig> readConfig(llvm::StringRef file);

    bool isStringBanned(const llvm::StringRef stringToCheck, const std::string fileName, std::string* const reason = NULL);

    std::vector<BannedString> bannedStrings;
   private:
    bool isRegexCacheBuilt = false;
    void populateRegexCache();
};

} // namespace brighttools

using namespace llvm;
using namespace yaml;

#include "llvm/Support/raw_ostream.h"

namespace llvm {
namespace yaml {

template <> struct MappingTraits<brighttools::BanStringConfig> {
    static void mapping(IO &io, brighttools::BanStringConfig &info) {
        brighttools::BannedStringContext * const context = reinterpret_cast<brighttools::BannedStringContext *>(io.getContext());
        const std::string fieldName = "Banned" + std::string(context->stringAlias.data()) + "s";
        io.mapOptionalWithContext(fieldName.c_str(), info.bannedStrings, *context);
    }
};

} // namespace yaml
} // namespace llvm

#endif // BAN_STRING_CONFIG_HPP
