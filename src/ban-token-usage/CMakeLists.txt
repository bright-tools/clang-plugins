add_library(ban-token-usage-plugin-${CLANG_VERSION} MODULE
  BanTokenUsageChecker.cpp
  BanTokenUsageASTVisitor.cpp
)

target_link_libraries(ban-token-usage-plugin-${CLANG_VERSION} PRIVATE brighttools-clang-plugin-util)

install(TARGETS ban-token-usage-plugin-${CLANG_VERSION} DESTINATION lib)

add_subdirectory(tests)