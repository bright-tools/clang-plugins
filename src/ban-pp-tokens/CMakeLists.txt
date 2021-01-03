add_library(ban-pp-tokens-plugin-${CLANG_VERSION} MODULE
  BanPPTokensAction.cpp
)

target_link_libraries(ban-pp-tokens-plugin-${CLANG_VERSION} PRIVATE brighttools-clang-plugin-util)

install(TARGETS ban-pp-tokens-plugin-${CLANG_VERSION} DESTINATION lib)

add_subdirectory(tests)