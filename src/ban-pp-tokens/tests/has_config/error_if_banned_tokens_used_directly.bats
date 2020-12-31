source ../../../../submodules/bats-support/load.bash
source ../../../../submodules/bats-assert/load.bash

@test "Check that when banned tokens are directly referenced, errors are raised" {
    run ${CLANG_EXE} -c -fplugin=${PLUGIN_TARGET} banned_tokens_used_directly.c
    assert_failure
    assert_output --partial "banned_tokens_used_directly.c:1:5: error: Found use of banned token 'AVOID'"
    assert_output --partial "banned_tokens_used_directly.c:2:9: error: Found use of banned token 'EVIL'"
}