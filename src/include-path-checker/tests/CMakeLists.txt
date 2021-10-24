add_test(NAME IncludePathChecker_PositiveParent
         COMMAND ${BATS_EXE} check_parent_path_violation_is_detected.bats
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/disallow_parent)

add_test(NAME IncludePathChecker_PositiveParentIndirect
         COMMAND ${BATS_EXE} check_indirect_parent_path_violation_is_detected.bats
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/disallow_parent)

add_test(NAME IncludePathChecker_PositiveChild
         COMMAND ${BATS_EXE} check_child_path_violation_is_detected.bats
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/disallow_child)

add_test(NAME IncludePathChecker_PositiveSystemChild
         COMMAND ${BATS_EXE} check_child_system_path_violation_is_detected.bats
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/disallow_child)

add_test(NAME IncludePathChecker_PositiveChildAndParent
         COMMAND ${BATS_EXE} check_child_and_parent_path_violations_are_detected.bats
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/disallow_child_and_parent)

add_test(NAME IncludePathChecker_NotEnabled
         COMMAND ${BATS_EXE} check_violation_is_not_detected_when_not_enabled.bats
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_test(NAME IncludePathChecker_Negative
         COMMAND ${BATS_EXE} check_violation_is_not_detected_when_not_present.bats
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/disallow_child_and_parent)

add_test(NAME IncludePathChecker_SystemHeaderExclusion
         COMMAND ${BATS_EXE} check_violation_is_not_detected_in_system_headers.bats
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/disallow_child_and_parent)

add_test(NAME IncludePathChecker_ChildSystemHeaderAllowed
         COMMAND ${BATS_EXE} check_violation_is_not_detected_when_system_child_refs_allowed.bats
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/disallow_child_allow_system)

add_test(NAME IncludePathChecker_BannedIncludes
         COMMAND ${BATS_EXE} check_banned_includes.bats
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/banned_includes)

add_test(NAME IncludePathChecker_Whitelisted
         COMMAND ${BATS_EXE} check_whitelisted_includes.bats
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/banned_includes)

add_test(NAME IncludePathChecker_Blacklisted
         COMMAND ${BATS_EXE} check_blacklisted_includes.bats
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/banned_includes)

set_tests_properties(IncludePathChecker_BannedIncludes
                     IncludePathChecker_ChildSystemHeaderAllowed
                     IncludePathChecker_PositiveSystemChild
                     IncludePathChecker_SystemHeaderExclusion
                     IncludePathChecker_PositiveParentIndirect
                     IncludePathChecker_PositiveChildAndParent
                     IncludePathChecker_PositiveChild
                     IncludePathChecker_PositiveParent
                     IncludePathChecker_NotEnabled
                     IncludePathChecker_Negative
                     IncludePathChecker_Whitelisted
                     IncludePathChecker_Blacklisted
                     PROPERTIES ENVIRONMENT "${TEST_ENVIRONMENT};PLUGIN_TARGET=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<TARGET_FILE_NAME:include-path-checker-plugin-${CLANG_VERSION_MAJOR}>")
