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

#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Path.h>
#include <llvm/Support/YAMLTraits.h>

#include "BanTokenUsageConfig.hpp"

using namespace llvm;
using namespace yaml;

namespace llvm {
namespace yaml {

template <> struct MappingTraits<brighttools::BanTokenUsageConfig> {
    static void mapping(IO &io, brighttools::BanTokenUsageConfig &info) {
        io.mapRequired("BannedTokens", info.bannedTokens);
    }
};

} // namespace yaml
} // namespace llvm

namespace brighttools {

llvm::Optional<BanTokenUsageConfig> BanTokenUsageConfig::readConfig(llvm::StringRef file) {
    auto document = llvm::MemoryBuffer::getFile(file);

    if (!document.getError()) {
        BanTokenUsageConfig *config = new BanTokenUsageConfig();

        llvm::yaml::Input yin((*document)->getBuffer());
        yin >> *config;

        if (!yin.error()) {
            return llvm::Optional<BanTokenUsageConfig>::create(config);
        }
        delete (config);
    }

    return llvm::None;
}

} // namespace brighttools

LLVM_YAML_IS_SEQUENCE_VECTOR(brighttools::BanTokenUsageConfig)
LLVM_YAML_IS_SEQUENCE_VECTOR(std::vector<std::string>)
