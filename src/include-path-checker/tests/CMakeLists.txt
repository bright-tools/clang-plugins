add_test(NAME IncludePathChecker_Positive
         COMMAND ${BATS_EXE} check_violation_is_detected.bats
         WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/src/include-path-checker/tests)

add_test(NAME IncludePathChecker_NotEnabled
         COMMAND ${BATS_EXE} check_violation_is_not_detected_when_not_enabled.bats
         WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/src/include-path-checker/tests)

add_test(NAME IncludePathChecker_Negative
         COMMAND ${BATS_EXE} check_violation_is_not_detected_when_not_present.bats
         WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/src/include-path-checker/tests)

set_tests_properties(IncludePathChecker_Positive IncludePathChecker_NotEnabled IncludePathChecker_Negative PROPERTIES ENVIRONMENT "CLANG_EXE=${CLANG_EXE};PLUGIN_TARGET=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<TARGET_FILE_NAME:include-path-checker-plugin>")
