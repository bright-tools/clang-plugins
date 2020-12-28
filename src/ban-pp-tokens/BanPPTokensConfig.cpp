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

#include <llvm/Support/YAMLTraits.h>

#include "BanPPTokensConfig.hpp"

using namespace llvm;
using namespace yaml;

namespace llvm {
namespace yaml {

template <> struct MappingTraits<brighttools::BanPPTokensConfig> {
    static void mapping(IO &io, brighttools::BanPPTokensConfig &info) {
        io.mapRequired("BannedTokens", info.bannedTokens);
    }
};

} // namespace yaml
} // namespace llvm

namespace brighttools {

std::shared_ptr<BanPPTokensConfig> BanPPTokensConfig::readConfig() {
    auto config = std::make_shared<BanPPTokensConfig>();

    auto document = llvm::MemoryBuffer::getFile(".ban-pp-tokens.yml");

    llvm::yaml::Input yin((*document)->getBuffer());
    yin >> *config;
    // TODO: Add error checking

    return config;
}

} // namespace brighttools

LLVM_YAML_IS_SEQUENCE_VECTOR(brighttools::BanPPTokensConfig)
LLVM_YAML_IS_SEQUENCE_VECTOR(std::vector<std::string>)
