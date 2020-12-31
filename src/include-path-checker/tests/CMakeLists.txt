add_test(NAME Positive
         COMMAND ${PROJECT_SOURCE_DIR}/submodules/bats-core/bin/bats check_violation_is_detected.bats
         WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/src/include-path-checker/tests)

add_test(NAME NotEnabled
         COMMAND ${PROJECT_SOURCE_DIR}/submodules/bats-core/bin/bats check_violation_is_not_detected_when_not_enabled.bats
         WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/src/include-path-checker/tests)

add_test(NAME Negative
         COMMAND ${PROJECT_SOURCE_DIR}/submodules/bats-core/bin/bats check_violation_is_not_detected_when_not_present.bats
         WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/src/include-path-checker/tests)

set_tests_properties(Positive NotEnabled Negative PROPERTIES ENVIRONMENT "CLANG_EXE=${CLANG_EXE};PLUGIN_TARGET=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<TARGET_FILE_NAME:include-path-checker-plugin>")
