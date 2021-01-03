set(TEST_DIR ${PROJECT_SOURCE_DIR}/src/ban-token-usage/tests/has_config)

add_test(NAME BanTokenUsage_TokensPresentNotUsed
         COMMAND ${BATS_EXE} no_error_if_banned_tokens_not_used.bats
         WORKING_DIRECTORY ${TEST_DIR})

add_test(NAME BanTokenUsage_TokensPresentUsedDirectly
         COMMAND ${BATS_EXE} error_if_banned_tokens_used_directly.bats
         WORKING_DIRECTORY ${TEST_DIR})

set_tests_properties(BanTokenUsage_TokensPresentNotUsed BanTokenUsage_TokensPresentUsedDirectly PROPERTIES ENVIRONMENT "${TEST_ENVIRONMENT}")
