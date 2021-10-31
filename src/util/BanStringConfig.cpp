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
#include <llvm/Support/Regex.h>

#include "BanStringConfig.hpp"


namespace brighttools {

void BanStringConfig::populateRegexCache() {
    for (std::vector<BannedString>::iterator it = bannedStrings.begin();
         it != bannedStrings.end();
         it++) {
        if (it->enableRegex) {
            it->stringRegex = std::shared_ptr<llvm::Regex>(new llvm::Regex(it->string));
        }
        if (!(it->blacklistRegexString.empty())) {
            it->blacklistRegex = std::shared_ptr<llvm::Regex>(new llvm::Regex(it->blacklistRegexString));
        }
        if (!(it->whitelistRegexString.empty())) {
            it->whitelistRegex = std::shared_ptr<llvm::Regex>(new llvm::Regex(it->whitelistRegexString));
        }
    }
    isRegexCacheBuilt = true;
}

llvm::Optional<BanStringConfig> BanStringConfig::readConfig(llvm::StringRef file) {
    auto document = llvm::MemoryBuffer::getFile(file);

    if (!document.getError()) {
        BanStringConfig *config = new BanStringConfig();

        BannedStringContext context = {.stringAlias = "Token"};
        llvm::yaml::Input yin((*document)->getBuffer(), &context);
        yin >> *config;

        if (!yin.error()) {
            return llvm::Optional<BanStringConfig>::create(config);
        }
        delete (config);
    }

    return llvm::None;
}

static bool stringsEqual(llvm::StringRef s1, const std::string& s2, std::shared_ptr<llvm::Regex> s2regEx) {
    if (s2regEx) {
        return s2regEx->match(s1);
    } else {
        return (s1 == s2);
    }
}

bool BanStringConfig::isStringBanned(const llvm::StringRef stringToCheck, const std::string fileName, std::string* const reason,
    bool (*matcher)(llvm::StringRef, const std::string&, std::shared_ptr<llvm::Regex>)) {

    if (!isRegexCacheBuilt) {
        populateRegexCache();
    }

    for (auto bannedString = bannedStrings.begin(); bannedString != bannedStrings.end(); bannedString++) {

        if (matcher(stringToCheck, bannedString->string, bannedString->stringRegex)) {

            /* All files are blacklisted by default, unless the blacklist regex is specified
               in which case only files matched by that expression are blacklisted */
            bool isBlacklisted = true;
            if (bannedString->blacklistRegex) {
                isBlacklisted = bannedString->blacklistRegex->match(fileName);
            }

            bool isWhitelisted = false;
            if (bannedString->whitelistRegex) {
                isWhitelisted = bannedString->whitelistRegex->match(fileName);
            }

            if (isBlacklisted && !isWhitelisted) {
                if (reason != NULL) {
                    *reason = bannedString->reason;
                }
                return true;
            }
        }
    }
    return false;
}

bool BanStringConfig::isStringBanned(const llvm::StringRef stringToCheck, const std::string fileName, std::string* const reason) {
    return isStringBanned(stringToCheck, fileName, reason, stringsEqual);
}

} // namespace brighttools
