add_library(brighttools-clang-plugin-util STATIC
  ConfigBase.cpp
)

target_include_directories(brighttools-clang-plugin-util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})