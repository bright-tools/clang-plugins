set(BAN_PP_TOKENS_HAS_CONFIG_TEST_DIR ${PROJECT_SOURCE_DIR}/src/ban-pp-tokens/tests/has_config)

add_test(NAME BanPPTokens_TokensPresentNotUsed
         COMMAND ${BATS_EXE} error_if_banned_tokens_not_used.bats
         WORKING_DIRECTORY ${BAN_PP_TOKENS_HAS_CONFIG_TEST_DIR})

add_test(NAME BanPPTokens_TokensPresentUsedDirectly
         COMMAND ${BATS_EXE} error_if_banned_tokens_used_directly.bats
         WORKING_DIRECTORY ${BAN_PP_TOKENS_HAS_CONFIG_TEST_DIR})

 add_test(NAME BanPPTokens_WhitelistedTokens
         COMMAND ${BATS_EXE} no_error_if_banned_tokens_whitelisted.bats
         WORKING_DIRECTORY ${BAN_PP_TOKENS_HAS_CONFIG_TEST_DIR})

add_test(NAME BanPPTokens_WhitelistedTokensUsedIndirectly
         COMMAND ${BATS_EXE} no_error_if_indirect_banned_tokens_whitelisted.bats
         WORKING_DIRECTORY ${BAN_PP_TOKENS_HAS_CONFIG_TEST_DIR})

add_test(NAME BanPPTokens_BannedTokenInBlacklistedFile
         COMMAND ${BATS_EXE} error_if_banned_token_found_in_blacklisted_file.bats
         WORKING_DIRECTORY ${BAN_PP_TOKENS_HAS_CONFIG_TEST_DIR})

add_test(NAME BanPPTokens_BannedTokenInUnBlacklistedFile
         COMMAND ${BATS_EXE} no_error_if_not_covered_by_blacklist.bats
         WORKING_DIRECTORY ${BAN_PP_TOKENS_HAS_CONFIG_TEST_DIR})

add_test(NAME BanPPTokens_BannedTokenInBlacklistedFileThatIsWhitelisted
         COMMAND ${BATS_EXE} no_error_if_banned_token_found_in_blacklisted_file_that_is_whitelisted.bats
         WORKING_DIRECTORY ${BAN_PP_TOKENS_HAS_CONFIG_TEST_DIR})

add_test(NAME BanPPTokens_BannedRegexTokens
         COMMAND ${BATS_EXE} error_if_regex_banned_tokens_used.bats
         WORKING_DIRECTORY ${BAN_PP_TOKENS_HAS_CONFIG_TEST_DIR})

add_test(NAME BanPPTokens_NonBannedRegexTokens
         COMMAND ${BATS_EXE} no_error_if_regex_banned_tokens_not_used.bats
         WORKING_DIRECTORY ${BAN_PP_TOKENS_HAS_CONFIG_TEST_DIR})

set_tests_properties(BanPPTokens_NonBannedRegexTokens BanPPTokens_BannedRegexTokens BanPPTokens_BannedTokenInBlacklistedFileThatIsWhitelisted BanPPTokens_BannedTokenInUnBlacklistedFile BanPPTokens_BannedTokenInBlacklistedFile BanPPTokens_WhitelistedTokensUsedIndirectly BanPPTokens_WhitelistedTokens BanPPTokens_TokensPresentNotUsed BanPPTokens_TokensPresentUsedDirectly PROPERTIES ENVIRONMENT "${BAN_PP_TOKENS_TEST_ENVIRONMENT}")
