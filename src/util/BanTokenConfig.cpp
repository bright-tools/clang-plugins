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

#include "BanTokenConfig.hpp"

using namespace llvm;
using namespace yaml;

namespace llvm {
namespace yaml {

template <> struct MappingTraits<brighttools::BanTokenConfig::BannedToken> {
    static void mapping(IO &io, brighttools::BanTokenConfig::BannedToken &info) {
        io.mapRequired("Token", info.token);
        io.mapOptional("Reason", info.reason);
    }
};

template <> struct MappingTraits<brighttools::BanTokenConfig> {
    static void mapping(IO &io, brighttools::BanTokenConfig &info) {
        io.mapOptional("BannedTokens", info.bannedTokens);
    }
};

} // namespace yaml
} // namespace llvm

namespace brighttools {

llvm::Optional<BanTokenConfig> BanTokenConfig::readConfig(llvm::StringRef file) {
    auto document = llvm::MemoryBuffer::getFile(file);

    if (!document.getError()) {
        BanTokenConfig *config = new BanTokenConfig();

        llvm::yaml::Input yin((*document)->getBuffer());
        yin >> *config;

        if (!yin.error()) {
            return llvm::Optional<BanTokenConfig>::create(config);
        }
        delete (config);
    }

    return llvm::None;
}

bool BanTokenConfig::isTokenBanned(const llvm::StringRef tokenToCheck, std::string* reason) const {
    for (auto bannedToken : bannedTokens) {

        if (tokenToCheck == bannedToken.token) {
            if (reason != NULL) {
                *reason = bannedToken.reason;
            }
            return true;
        }
    }
    return false;
}

} // namespace brighttools

LLVM_YAML_IS_SEQUENCE_VECTOR(brighttools::BanTokenConfig)
LLVM_YAML_IS_SEQUENCE_VECTOR(brighttools::BanTokenConfig::BannedToken)
