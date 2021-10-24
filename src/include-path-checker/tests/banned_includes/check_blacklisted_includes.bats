source ${SUBMODULES_ROOT}/bats-support/load.bash
source ${SUBMODULES_ROOT}/bats-assert/load.bash

@test "Check that banned include files are flagged when including file is blacklisted" {
    run ${CLANG_EXE} -c -fplugin=${PLUGIN_TARGET} ../includes_banned_header_and_is_blacklisted.c -Xclang -plugin-arg-include-path-checker
    assert_failure
    assert_output --partial "../includes_banned_header_and_is_blacklisted.c:1:1: error: Found use of banned include 'blacklisted.h', ban reason: Blacklisted"
}