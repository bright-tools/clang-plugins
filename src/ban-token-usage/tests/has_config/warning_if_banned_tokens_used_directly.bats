source ${SUBMODULES_ROOT}/bats-support/load.bash
source ${SUBMODULES_ROOT}/bats-assert/load.bash
source ${SUBMODULES_ROOT}/bats-file/load.bash

@test "Check that when banned tokens are directly referenced, warnings are raised" {
    run ${CLANG_EXE} -fsyntax-only -fplugin=${PLUGIN_TARGET} banned_tokens_used_directly.c -Xclang -analyze -Xclang -analyzer-checker=brighttools.ban-token-usage
    assert_success
    assert_output --partial "banned_tokens_used_directly.c:7:5: warning: Banned token 'AVOID' [brighttools.ban-token-usage]"
    assert_output --partial "banned_tokens_used_directly.c:9:9: warning: Banned token 'EVIL' [brighttools.ban-token-usage]"
    assert_output --partial "banned_tokens_used_directly.c:13:6: warning: Banned token 'EVIL' [brighttools.ban-token-usage]"
    assert_output --partial "banned_tokens_used_directly.c:13:15: warning: Banned token 'AVOID' [brighttools.ban-token-usage]"
    assert_output --partial "banned_tokens_used_directly.c:14:11: warning: Banned token 'AVOID' [brighttools.ban-token-usage]"
    refute_output --partial "FAKE"
}