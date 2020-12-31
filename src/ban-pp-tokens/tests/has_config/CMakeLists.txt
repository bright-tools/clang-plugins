add_test(NAME BanPPTokens_TokensPresentNotUsed
         COMMAND ${BATS_EXE} error_if_banned_tokens_not_used.bats
         WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/src/ban-pp-tokens/tests/has_config)

add_test(NAME BanPPTokens_TokensPresentUsedDirectly
         COMMAND ${BATS_EXE} error_if_banned_tokens_used_directly.bats
         WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/src/ban-pp-tokens/tests/has_config)

set_tests_properties(BanPPTokens_TokensPresentNotUsed BanPPTokens_TokensPresentUsedDirectly PROPERTIES ENVIRONMENT "CLANG_EXE=${CLANG_EXE};PLUGIN_TARGET=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<TARGET_FILE_NAME:ban-pp-tokens-plugin>")
