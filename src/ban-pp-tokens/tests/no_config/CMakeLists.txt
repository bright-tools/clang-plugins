set(TEST_DIR ${PROJECT_SOURCE_DIR}/src/ban-pp-tokens/tests/no_config)

add_test(NAME BanPPTokens_NoConfig
         COMMAND ${BATS_EXE} no_error_if_no_config.bats
         WORKING_DIRECTORY ${TEST_DIR})

set_tests_properties(BanPPTokens_NoConfig PROPERTIES ENVIRONMENT "${TEST_ENVIRONMENT}")
