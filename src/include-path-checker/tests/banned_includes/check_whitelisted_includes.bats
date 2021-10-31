source ${SUBMODULES_ROOT}/bats-support/load.bash
source ${SUBMODULES_ROOT}/bats-assert/load.bash

@test "Check that banned include files are not flagged when including file is whitelisted" {
    run ${CLANG_EXE} -c -fplugin=${PLUGIN_TARGET} ../includes_banned_header_but_is_whitelisted.c -Xclang -plugin-arg-include-path-checker
    assert_success
    refute_output --partial "Found use of banned include"
}