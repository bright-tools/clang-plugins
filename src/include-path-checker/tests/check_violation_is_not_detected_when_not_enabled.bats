source ../../../submodules/bats-support/load.bash
source ../../../submodules/bats-assert/load.bash
source ../../../submodules/bats-file/load.bash

COMPILER_OUTPUT=includes_via_parent_path.o

function setup() {
    rm -f ${COMPILER_OUTPUT}
}

function teardown() {
    rm -f ${COMPILER_OUTPUT}
}

@test "Check that a violation of the check is not detected when the check is not enabled" {
    run clang-10 -c -fplugin=${PLUGIN_TARGET} includes_via_parent_path.c -o ${COMPILER_OUTPUT}
    assert_success
    # Check that the file actually got compiled
    assert_file_exist ${COMPILER_OUTPUT}
}