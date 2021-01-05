source ${SUBMODULES_ROOT}/bats-support/load.bash
source ${SUBMODULES_ROOT}/bats-assert/load.bash

@test "Check that an indirect violation of the parent path check is detected" {
    run ${CLANG_EXE} -c -fplugin=${PLUGIN_TARGET} includes_via_parent_path_indirectly.c -Xclang -plugin-arg-include-path-checker -Xclang -disallow-parent-dir-include-references
    assert_failure
    assert_output --partial "./include_file_which_includes_via_parent_path.h:1:1: error: Found use of relative path to include '../tests/include_file.h'"
}