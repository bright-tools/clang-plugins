add_library(brighttools-clang-plugin-util STATIC
  ConfigBase.cpp
  BanStringConfig.cpp
)

set_property(TARGET brighttools-clang-plugin-util PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(brighttools-clang-plugin-util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})