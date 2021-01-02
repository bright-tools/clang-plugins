source ../../../../submodules/bats-support/load.bash
source ../../../../submodules/bats-assert/load.bash

@test "Check that no error is reported when no config is present" {
    run ${CLANG_EXE} -c -fplugin=${PLUGIN_TARGET} test.c
    assert_success
}