source ${SUBMODULES_ROOT}/bats-support/load.bash
source ${SUBMODULES_ROOT}/bats-assert/load.bash
source ${SUBMODULES_ROOT}/bats-file/load.bash

COMPILER_OUTPUT=includes_via_parent_path.o

function setup() {
    rm -f ${COMPILER_OUTPUT}
}

function teardown() {
    rm -f ${COMPILER_OUTPUT}
}

@test "Check that a violation of the check is not detected when the check is not enabled" {
    run ${CLANG_EXE} -c -fplugin=${PLUGIN_TARGET} includes_via_parent_path.c -o ${COMPILER_OUTPUT}
    assert_success
    # Check that the file actually got compiled
    assert_file_exist ${COMPILER_OUTPUT}
}