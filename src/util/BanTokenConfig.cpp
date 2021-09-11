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
#include <llvm/Support/Regex.h>

#include "BanTokenConfig.hpp"

using namespace llvm;
using namespace yaml;

namespace llvm {
namespace yaml {

template <> struct MappingTraits<brighttools::BanTokenConfig::BannedToken> {
    static void mapping(IO &io, brighttools::BanTokenConfig::BannedToken &info) {
        io.mapRequired("Token", info.token);
        io.mapOptional("Reason", info.reason);
        io.mapOptional("WhiteListRegex", info.whitelistRegexString);
        io.mapOptional("BlackListRegex", info.blacklistRegexString);
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

void BanTokenConfig::populateRegexCache(BanTokenConfig* const config) {
    for (std::vector<BannedToken>::iterator it = config->bannedTokens.begin();
         it != config->bannedTokens.end();
         it++) {
        if (!(it->blacklistRegexString.empty())) {
            it->blacklistRegex = std::shared_ptr<llvm::Regex>(new llvm::Regex(it->blacklistRegexString));
        }
        if (!(it->whitelistRegexString.empty())) {
            it->whitelistRegex = std::shared_ptr<llvm::Regex>(new llvm::Regex(it->whitelistRegexString));
        }
    }
}

llvm::Optional<BanTokenConfig> BanTokenConfig::readConfig(llvm::StringRef file) {
    auto document = llvm::MemoryBuffer::getFile(file);

    if (!document.getError()) {
        BanTokenConfig *config = new BanTokenConfig();

        llvm::yaml::Input yin((*document)->getBuffer());
        yin >> *config;

        if (!yin.error()) {
            populateRegexCache(config);
            return llvm::Optional<BanTokenConfig>::create(config);
        }
        delete (config);
    }

    return llvm::None;
}

bool BanTokenConfig::isTokenBanned(const llvm::StringRef tokenToCheck, const std::string fileName, std::string* const reason) const {
    for (auto bannedToken = bannedTokens.begin(); bannedToken != bannedTokens.end(); bannedToken++) {

        if (tokenToCheck == bannedToken->token) {

            /* All files are blacklisted by default, unless the blacklist regex is specified
               in which case only files matched by that expression are blacklisted */
            bool isBlacklisted = true;
            if (bannedToken->blacklistRegex) {
                isBlacklisted = bannedToken->blacklistRegex->match(fileName);
            }

            bool isWhitelisted = false;
            if (bannedToken->whitelistRegex) {
                isWhitelisted = bannedToken->whitelistRegex->match(fileName);
            }

            if (isBlacklisted && !isWhitelisted) {
                if (reason != NULL) {
                    *reason = bannedToken->reason;
                }
                return true;
            }
        }
    }
    return false;
}

} // namespace brighttools

LLVM_YAML_IS_SEQUENCE_VECTOR(brighttools::BanTokenConfig)
LLVM_YAML_IS_SEQUENCE_VECTOR(brighttools::BanTokenConfig::BannedToken)
