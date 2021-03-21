add_library(include-path-checker-plugin-${CLANG_VERSION_MAJOR} MODULE
  IncludePathChecker.cpp IncludePathCheckerConfig.cpp
)

target_link_libraries(include-path-checker-plugin-${CLANG_VERSION_MAJOR} PRIVATE brighttools-clang-plugin-util)

install(TARGETS include-path-checker-plugin-${CLANG_VERSION_MAJOR} DESTINATION lib)

add_subdirectory(tests)