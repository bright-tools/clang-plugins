source ${SUBMODULES_ROOT}/bats-support/load.bash
source ${SUBMODULES_ROOT}/bats-assert/load.bash

@test "Check that a violation of the child path check is detected when include target is system header file" {
    run ${CLANG_EXE} -isystem ../include_dir -c -fplugin=${PLUGIN_TARGET} ../includes_child_system_header_file.c -Xclang -plugin-arg-include-path-checker
    assert_failure
    assert_output --partial "../includes_child_system_header_file.c:1:1: error: Found use of relative path to include 'sys/types.h'"
    assert_output --partial "../includes_child_system_header_file.c:2:1: error: Found use of relative path to include 'subdir/sub_include.h'"
}