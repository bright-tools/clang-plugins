source ../../../submodules/bats-support/load.bash
source ../../../submodules/bats-assert/load.bash

@test "Check that a violation of the check is not detected when the check is not enabled" {
    run clang-10 -c -fplugin=${PLUGIN_TARGET} includes_via_parent_path.c
    assert_success
}