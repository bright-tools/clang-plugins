source ${SUBMODULES_ROOT}/bats-support/load.bash
source ${SUBMODULES_ROOT}/bats-assert/load.bash
source ${SUBMODULES_ROOT}/bats-file/load.bash

@test "Check that when banned tokens are directly referenced, errors are raised" {
    run ${CLANG_EXE} -c -fplugin=${PLUGIN_TARGET} banned_tokens_used_directly.c -Xclang -analyze -Xclang -analyzer-checker=brighttools.ban-token-usage
    assert_failure
    assert_output --partial "banned_tokens_used_directly.c:1:5: error: Found use of banned token 'AVOID'"
    assert_output --partial "banned_tokens_used_directly.c:2:9: error: Found use of banned token 'EVIL'"
}