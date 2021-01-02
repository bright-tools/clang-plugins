set(TEST_ENVIRONMENT "CLANG_EXE=${CLANG_EXE};PLUGIN_TARGET=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<TARGET_FILE_NAME:ban-pp-tokens-plugin>")

add_subdirectory(has_config)
add_subdirectory(no_config)
