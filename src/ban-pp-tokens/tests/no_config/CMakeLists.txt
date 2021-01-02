set(BAN_PP_TOKENS_NO_CONFIG_TEST_DIR ${PROJECT_SOURCE_DIR}/src/ban-pp-tokens/tests/no_config)

add_test(NAME BanPPTokens_NoConfig
         COMMAND ${BATS_EXE} no_error_if_no_config.bats
         WORKING_DIRECTORY ${BAN_PP_TOKENS_NO_CONFIG_TEST_DIR})

set_tests_properties(BanPPTokens_NoConfig PROPERTIES ENVIRONMENT "${BAN_PP_TOKENS_TEST_ENVIRONMENT}")
