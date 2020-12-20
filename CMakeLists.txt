project(brighttools-clang-plugins)
cmake_minimum_required(VERSION 2.8)
enable_testing()

set(PACKAGE_NAME brighttools-clang-plugins)
set(PACKAGE_VERSION 0.1.1)
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
set(PACKAGE_BUGREPORT "dev@brightsilence.org")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_DOCUMENT_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

# LLVM

find_package(LLVM 10 REQUIRED CONFIG HINTS ${LLVM_DIR})
message(STATUS "LLVM version: ${LLVM_PACKAGE_VERSION}")
message(STATUS "LLVMConfig.cmake found in: ${LLVM_DIR}")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

# clang

find_package(Clang REQUIRED CONFIG HINTS ${LLVM_INSTALL_PREFIX}/lib/cmake/clang)
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS} ${CLANG_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
message(STATUS "clang found in: ${CLANG_INSTALL_PREFIX}")

add_subdirectory(src)
add_subdirectory(doc)

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER ${PACKAGE_BUGREPORT})
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/bright-tools/clang-plugins")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Additional plugins & checkers for clang")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "clang-10")
set(CPACK_DEBIAN_PACKAGE_VERSION ${PACKAGE_VERSION})
include(CPack)