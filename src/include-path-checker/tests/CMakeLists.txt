add_test(NAME IncludePathChecker_Positive
         COMMAND ${BATS_EXE} check_violation_is_detected.bats
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_test(NAME IncludePathChecker_NotEnabled
         COMMAND ${BATS_EXE} check_violation_is_not_detected_when_not_enabled.bats
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_test(NAME IncludePathChecker_Negative
         COMMAND ${BATS_EXE} check_violation_is_not_detected_when_not_present.bats
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set_tests_properties(IncludePathChecker_Positive IncludePathChecker_NotEnabled IncludePathChecker_Negative PROPERTIES ENVIRONMENT "${TEST_ENVIRONMENT};PLUGIN_TARGET=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<TARGET_FILE_NAME:include-path-checker-plugin-${CLANG_VERSION}>")
