source ${SUBMODULES_ROOT}/bats-support/load.bash
source ${SUBMODULES_ROOT}/bats-assert/load.bash

@test "Check that when banned tokens are directly referenced, errors are raised" {
    run ${CLANG_EXE} -c -fplugin=${PLUGIN_TARGET} has_whitelisted_tokens.c
    assert_success
    refute_output --partial "Found use of banned token"
}