add_library(ban-pp-tokens-plugin MODULE
  BanPPTokensAction.cpp
  BanPPTokensConfig.cpp
)

install(TARGETS ban-pp-tokens-plugin DESTINATION lib)

#add_subdirectory(tests)