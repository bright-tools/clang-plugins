source ${SUBMODULES_ROOT}/bats-support/load.bash
source ${SUBMODULES_ROOT}/bats-assert/load.bash
source ${SUBMODULES_ROOT}/bats-file/load.bash

@test "Check that when banned tokens are present but not referenced, no warnings are raised" {
    run ${CLANG_EXE} -fsyntax-only -fplugin=${PLUGIN_TARGET} banned_tokens_unused.c -Xclang -analyze -Xclang -analyzer-checker=brighttools.ban-token-usage
    refute_output --partial "warning:"
    assert_success
}