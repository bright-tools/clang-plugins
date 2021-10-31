source ${SUBMODULES_ROOT}/bats-support/load.bash
source ${SUBMODULES_ROOT}/bats-assert/load.bash

@test "Check banned filed described using regular expressions are detected" {
    run ${CLANG_EXE} -c -fplugin=${PLUGIN_TARGET} ../includes_regex_banned_headers.c -Xclang -plugin-arg-include-path-checker
    assert_failure
    assert_output --partial "../includes_regex_banned_headers.c:1:1: error: Found use of banned include 'stdio.h', ban reason: There is no reason"
    assert_output --partial "../includes_regex_banned_headers.c:2:1: error: Found use of banned include 'stdlib.h', ban reason: There is no reason"
    assert_output --partial "../includes_regex_banned_headers.c:3:1: error: Found use of banned include 'string.h'"
    assert_output --partial "../includes_regex_banned_headers.c:4:1: error: Found use of banned include 'include_file.h'"
    assert_output --partial "../includes_regex_banned_headers.c:5:1: error: Found use of banned include 'include_dir/include_file.h'"
}