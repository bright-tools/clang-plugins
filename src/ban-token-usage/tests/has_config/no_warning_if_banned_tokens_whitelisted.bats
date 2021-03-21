source ${SUBMODULES_ROOT}/bats-support/load.bash
source ${SUBMODULES_ROOT}/bats-assert/load.bash
source ${SUBMODULES_ROOT}/bats-file/load.bash

@test "Check that when banned tokens are present but in a whitelisted file, no warning is raised" {
    run ${CLANG_EXE} -fsyntax-only -fplugin=${PLUGIN_TARGET} has_whitelisted_tokens.c -Xclang -analyze -Xclang -analyzer-checker=brighttools.ban-token-usage
    refute_output --partial "warning:"
    assert_success
}