source ${SUBMODULES_ROOT}/bats-support/load.bash
source ${SUBMODULES_ROOT}/bats-assert/load.bash

@test "Check that a violation of the check is not detected when the system headers use relative includes" {
    run ${CLANG_EXE} -isystem ../include_dir -c -fplugin=${PLUGIN_TARGET} ../includes_system_header.c -Xclang -plugin-arg-include-path-checker
    assert_success
}