add_library(include-path-checker-plugin-${CLANG_VERSION} MODULE
  IncludePathChecker.cpp
)

install(TARGETS include-path-checker-plugin-${CLANG_VERSION} DESTINATION lib)

add_subdirectory(tests)