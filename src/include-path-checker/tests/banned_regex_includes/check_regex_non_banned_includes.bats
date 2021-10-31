source ${SUBMODULES_ROOT}/bats-support/load.bash
source ${SUBMODULES_ROOT}/bats-assert/load.bash

@test "Check files not matching regex bans are not spuriously detected as being banned" {
    run ${CLANG_EXE} -c -fplugin=${PLUGIN_TARGET} ../does_not_include_regex_banned_headers.c -Xclang -plugin-arg-include-path-checker
    assert_success
    refute_output --partial "Found use of banned include"
}