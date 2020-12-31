source ../../../../submodules/bats-support/load.bash
source ../../../../submodules/bats-assert/load.bash

@test "Check that when banned tokens are present but not referenced, no error is raised" {
    run ${CLANG_EXE} -c -fplugin=${PLUGIN_TARGET} banned_tokens_unused.c
    assert_success
}