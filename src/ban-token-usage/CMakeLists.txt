add_library(ban-token-usage-plugin MODULE
  BanTokenUsageChecker.cpp
  BanTokenUsageASTVisitor.cpp
  BanTokenUsageConfig.cpp
)

target_link_libraries(ban-token-usage-plugin PRIVATE brighttools-clang-plugin-util)

install(TARGETS ban-token-usage-plugin DESTINATION lib)

add_subdirectory(tests)