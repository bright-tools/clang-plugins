add_library(include-path-checker-plugin-${CLANG_VERSION} MODULE
  IncludePathChecker.cpp IncludePathCheckerConfig.cpp
)

target_link_libraries(include-path-checker-plugin-${CLANG_VERSION} PRIVATE brighttools-clang-plugin-util)

install(TARGETS include-path-checker-plugin-${CLANG_VERSION} DESTINATION lib)

add_subdirectory(tests)