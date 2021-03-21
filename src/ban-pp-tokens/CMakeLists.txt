add_library(ban-pp-tokens-plugin-${CLANG_VERSION_MAJOR} MODULE
  BanPPTokensAction.cpp
)

target_link_libraries(ban-pp-tokens-plugin-${CLANG_VERSION_MAJOR} PRIVATE brighttools-clang-plugin-util)

install(TARGETS ban-pp-tokens-plugin-${CLANG_VERSION_MAJOR} DESTINATION lib)

add_subdirectory(tests)