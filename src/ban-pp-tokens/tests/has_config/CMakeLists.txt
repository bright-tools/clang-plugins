set(BAN_PP_TOKENS_HAS_CONFIG_TEST_DIR ${PROJECT_SOURCE_DIR}/src/ban-pp-tokens/tests/has_config)

add_test(NAME BanPPTokens_TokensPresentNotUsed
         COMMAND ${BATS_EXE} error_if_banned_tokens_not_used.bats
         WORKING_DIRECTORY ${BAN_PP_TOKENS_HAS_CONFIG_TEST_DIR})

add_test(NAME BanPPTokens_TokensPresentUsedDirectly
         COMMAND ${BATS_EXE} error_if_banned_tokens_used_directly.bats
         WORKING_DIRECTORY ${BAN_PP_TOKENS_HAS_CONFIG_TEST_DIR})

set_tests_properties(BanPPTokens_TokensPresentNotUsed BanPPTokens_TokensPresentUsedDirectly PROPERTIES ENVIRONMENT "${BAN_PP_TOKENS_TEST_ENVIRONMENT}")
