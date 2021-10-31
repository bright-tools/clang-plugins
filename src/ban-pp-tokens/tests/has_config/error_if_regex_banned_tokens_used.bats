source ${SUBMODULES_ROOT}/bats-support/load.bash
source ${SUBMODULES_ROOT}/bats-assert/load.bash
source ${SUBMODULES_ROOT}/bats-file/load.bash

@test "Check that when regex banned tokens are present, errors are raised" {
    run ${CLANG_EXE} -c -fplugin=${PLUGIN_TARGET} regex_positive_testing.c
    assert_failure
    assert_output --partial "regex_positive_testing.c:1:10: error: Found use of banned token 'BLACKLISTED_REGEX_BUT_EXACT_MATCH'"
    assert_output --partial "regex_positive_testing.c:2:10: error: Found use of banned token 'REGEX_1'"
    assert_output --partial "Ban reason: Spurious reasoning"
    assert_output --partial "regex_positive_testing.c:3:10: error: Found use of banned token '_NO_START_NO_END_'"
}