add_library(include-path-checker-plugin MODULE
  IncludePathChecker.cpp
)

install(TARGETS include-path-checker-plugin DESTINATION lib)

add_subdirectory(tests)