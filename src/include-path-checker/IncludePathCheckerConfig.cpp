/* Copyright 2020 John Bailey

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "IncludePathCheckerConfig.hpp"

#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Path.h>
#include <llvm/Support/YAMLTraits.h>

using namespace llvm;
using namespace yaml;

namespace llvm {
namespace yaml {

template <> struct MappingTraits<brighttools::IncludePathCheckerConfig> {
    static void mapping(IO &io, brighttools::IncludePathCheckerConfig &info) {
        brighttools::BannedStringContext *context =
            reinterpret_cast<brighttools::BannedStringContext *>(io.getContext());

        io.mapOptional("DisallowParentDirIncludeReferences",
                       info.disallowParentDirIncludeReferences);
        io.mapOptional("DisallowChildDirIncludeReferences", info.disallowChildDirIncludeReferences);
        io.mapOptional("AllowChildDirSystemHeaderIncludeReferences",
                       info.allowChildDirSystemHeaderIncludeReferences);
        io.mapOptionalWithContext("BannedIncludes", info.bannedFiles.bannedStrings, *context);
    }
};

} // namespace yaml
} // namespace llvm

namespace brighttools {

llvm::Optional<IncludePathCheckerConfig>
IncludePathCheckerConfig::readConfig(llvm::StringRef file) {
    auto document = llvm::MemoryBuffer::getFile(file);

    if (!document.getError()) {
        IncludePathCheckerConfig *config = new IncludePathCheckerConfig();

        BannedStringContext context = {.stringAlias = "Filename"};
        llvm::yaml::Input yin((*document)->getBuffer(), &context);
        yin >> *config;

        if (!yin.error()) {
            return llvm::Optional<IncludePathCheckerConfig>::create(config);
        }
        delete (config);
    }

    return llvm::None;
}

} // namespace brighttools

LLVM_YAML_IS_SEQUENCE_VECTOR(brighttools::IncludePathCheckerConfig)
