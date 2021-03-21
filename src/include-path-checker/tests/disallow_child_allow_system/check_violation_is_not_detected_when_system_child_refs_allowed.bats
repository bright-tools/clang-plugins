source ${SUBMODULES_ROOT}/bats-support/load.bash
source ${SUBMODULES_ROOT}/bats-assert/load.bash

@test "Check that a violation of the check is not detected when the check is not enabled" {
    run ${CLANG_EXE} -isystem ../include_dir -c -fplugin=${PLUGIN_TARGET} ../includes_child_system_header_file.c
    assert_success
}