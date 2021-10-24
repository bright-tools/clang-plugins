source ${SUBMODULES_ROOT}/bats-support/load.bash
source ${SUBMODULES_ROOT}/bats-assert/load.bash

@test "Check that banned include files are detected (direct & indirect)" {
    run ${CLANG_EXE} -c -fplugin=${PLUGIN_TARGET} ../includes_banned_headers.c -Xclang -plugin-arg-include-path-checker
    assert_failure
    assert_output --partial "../includes_banned_headers.c:1:1: error: Found use of banned include 'include_file.h'"
    assert_output --partial "../includes_banned_headers.c:3:1: error: Found use of banned include 'include_dir/include_file.h'"
    assert_output --partial "../includes_banned_headers.c:5:1: error: Found use of banned include 'include_file_which_includes_another_include.h', ban reason: It's a test"
}