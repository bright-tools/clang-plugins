add_test(NAME TokensPresentNotUsed
         COMMAND ${PROJECT_SOURCE_DIR}/submodules/bats-core/bin/bats no_errors_if_banned_tokens_not_used.bats
         WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/src/ban-pp-tokens/tests/has_config)

add_test(NAME TokensPresentUsedDirectly
         COMMAND ${PROJECT_SOURCE_DIR}/submodules/bats-core/bin/bats error_if_banned_tokens_used_directly.bats
         WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/src/ban-pp-tokens/tests/has_config)

set_tests_properties(TokensPresentNotUsed TokensPresentUsedDirectly PROPERTIES ENVIRONMENT "CLANG_EXE=${CLANG_EXE};PLUGIN_TARGET=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<TARGET_FILE_NAME:ban-pp-tokens-plugin>")
