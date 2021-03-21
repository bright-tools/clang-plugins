source ${SUBMODULES_ROOT}/bats-support/load.bash
source ${SUBMODULES_ROOT}/bats-assert/load.bash

@test "Check that a violation of the check is not detected when the check is not violated" {
    run ${CLANG_EXE} -c -fplugin=${PLUGIN_TARGET} ../does_not_include_via_parent_path.c -Xclang -plugin-arg-include-path-checker
    assert_success
}