source ${SUBMODULES_ROOT}/bats-support/load.bash
source ${SUBMODULES_ROOT}/bats-assert/load.bash
source ${SUBMODULES_ROOT}/bats-file/load.bash

@test "Check that when banned tokens are present but not referenced, errors are raised" {
    local output_file=${CMAKE_CURRENT_BINARY_DIR}/banned_tokens_unused.o
    rm -f ${output_file}
    run ${CLANG_EXE} -c -fplugin=${PLUGIN_TARGET} banned_tokens_unused.c -o ${output_file}
    assert_failure
    assert_output --partial "banned_tokens_unused.c:3:12: error: Found use of banned token 'EVIL'"
    assert_output --partial "banned_tokens_unused.c:5:20: error: Found use of banned token 'BAD'"
    assert_file_not_exist ${output_file}
}