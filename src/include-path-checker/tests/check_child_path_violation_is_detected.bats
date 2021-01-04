source ${SUBMODULES_ROOT}/bats-support/load.bash
source ${SUBMODULES_ROOT}/bats-assert/load.bash

@test "Check that a violation of the child path check is detected" {
    run ${CLANG_EXE} -c -fplugin=${PLUGIN_TARGET} includes_via_child_path.c -Xclang -plugin-arg-include-path-checker -Xclang -disallow-child-dir-include-references
    assert_failure
    refute_output --partial "Found use of relative path to include 'include_file.h'"
    assert_output --partial "includes_via_child_path.c:3:1: error: Found use of relative path to include 'include_dir/include_file.h'"
}