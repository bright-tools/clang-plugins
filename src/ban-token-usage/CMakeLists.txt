add_library(ban-token-usage-plugin-${CLANG_VERSION_MAJOR} MODULE
  BanTokenUsageChecker.cpp
  BanTokenUsageASTVisitor.cpp
)

target_link_libraries(ban-token-usage-plugin-${CLANG_VERSION_MAJOR} PRIVATE brighttools-clang-plugin-util)

install(TARGETS ban-token-usage-plugin-${CLANG_VERSION_MAJOR} DESTINATION lib)

add_subdirectory(tests)