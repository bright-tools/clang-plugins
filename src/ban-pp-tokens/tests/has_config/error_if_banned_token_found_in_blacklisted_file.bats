source ${SUBMODULES_ROOT}/bats-support/load.bash
source ${SUBMODULES_ROOT}/bats-assert/load.bash
source ${SUBMODULES_ROOT}/bats-file/load.bash

@test "Check that when a banned token is present in a blacklisted file, errors are raised" {
    local output_file=${CMAKE_CURRENT_BINARY_DIR}/has_banned_token_and_is_blacklisted.o
    rm -f ${output_file}
    run ${CLANG_EXE} -c -fplugin=${PLUGIN_TARGET} has_banned_token_and_is_blacklisted.c -o ${output_file}
    assert_failure
    assert_output --partial "has_banned_token_and_is_blacklisted.c:1:5: error: Found use of banned token 'BLACKLISTED'"
    assert_output --partial "It's not going to help you"
    assert_file_not_exist ${output_file}
}