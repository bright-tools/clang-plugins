source ${SUBMODULES_ROOT}/bats-support/load.bash
source ${SUBMODULES_ROOT}/bats-assert/load.bash

@test "Check that when a banned token is a file which is both blacklisted and whitelisted, no error is raised" {
    run ${CLANG_EXE} -c -fplugin=${PLUGIN_TARGET} has_banned_token_is_blacklisted_and_whitelisted.c
    assert_success
    refute_output --partial "Found use of banned token"
}