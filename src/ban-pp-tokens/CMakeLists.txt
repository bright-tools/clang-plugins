add_library(ban-pp-tokens-plugin MODULE
  BanPPTokensAction.cpp
  BanPPTokensConfig.cpp
)

target_link_libraries(ban-pp-tokens-plugin PRIVATE brighttools-clang-plugin-util)

install(TARGETS ban-pp-tokens-plugin DESTINATION lib)

add_subdirectory(tests)