source ../../../submodules/bats-support/load.bash
source ../../../submodules/bats-assert/load.bash

@test "Check that a violation of the check is detected" {
    run clang-10 -c -fplugin=${PLUGIN_TARGET} includes_via_parent_path.c -Xclang -plugin-arg-include-path-checker -Xclang -disallow-parent-dir-include-references
    assert_failure
    assert_output --partial "includes_via_parent_path.c:3:1: error: Found use of relative path to include '../tests/include_file.h'"
}