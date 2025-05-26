cmake_minimum_required(VERSION 3.13)
project(WarpOptDriver)

find_package(LLVM REQUIRED CONFIG)
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
set(CMAKE_CXX_STANDARD 17)

add_executable(warp_opt_driver
  driver.cpp
  warp_optimization.cpp
)

llvm_map_components_to_libnames(llvm_libs
  Core
  IRReader
  BitWriter
  Support
  Passes
)

target_link_libraries(warp_opt_driver PRIVATE ${llvm_libs})

