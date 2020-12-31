source ../../../../submodules/bats-support/load.bash
source ../../../../submodules/bats-assert/load.bash

@test "Check that when banned tokens are present but not referenced, errors are raised" {
    run ${CLANG_EXE} -c -fplugin=${PLUGIN_TARGET} banned_tokens_unused.c
    assert_failure
    assert_output --partial "banned_tokens_unused.c:3:12: error: Found use of banned token 'EVIL'"
    assert_output --partial "banned_tokens_unused.c:5:20: error: Found use of banned token 'BAD'"
}