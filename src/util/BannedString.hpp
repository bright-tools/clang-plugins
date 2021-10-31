#if !defined BANNED_STRING_HPP
#define BANNED_STRING_HPP

#include <llvm/Support/Regex.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/Support/YAMLTraits.h>

#include <string>
#include <memory>
#include <stdbool.h>

namespace brighttools {

typedef struct {
  std::string string;
  std::shared_ptr<llvm::Regex> stringRegex;
  bool enableRegex;
  std::string reason;
  std::string whitelistRegexString;
  std::shared_ptr<llvm::Regex> whitelistRegex;
  std::string blacklistRegexString;
  std::shared_ptr<llvm::Regex> blacklistRegex;
} BannedString;

struct BannedStringContext {
    llvm::StringRef stringAlias;
};

} // namespace brighttools

LLVM_YAML_IS_SEQUENCE_VECTOR(brighttools::BannedString)

namespace llvm {
namespace yaml {

template <> struct MappingContextTraits<brighttools::BannedString, brighttools::BannedStringContext> {
    static void mapping(IO &io, brighttools::BannedString &info, brighttools::BannedStringContext& context) {
        io.mapRequired(context.stringAlias.data(), info.string);
        io.mapOptional("Reason", info.reason);
        io.mapOptional("WhiteListRegex", info.whitelistRegexString);
        io.mapOptional("BlackListRegex", info.blacklistRegexString);
        const std::string enableRegexFieldName = std::string("Enable") + context.stringAlias.data() + "Regex";
        io.mapOptional(enableRegexFieldName.c_str(), info.enableRegex);
    }
};

} // namespace yaml
} // namespace llvm

#endif
