source ${SUBMODULES_ROOT}/bats-support/load.bash
source ${SUBMODULES_ROOT}/bats-assert/load.bash
source ${SUBMODULES_ROOT}/bats-file/load.bash

@test "Check that when regex banned tokens are not present, no errors are raised" {
    run ${CLANG_EXE} -c -fplugin=${PLUGIN_TARGET} regex_negative_testing.c
    assert_success
    refute_output --partial "Found use of banned token"
}