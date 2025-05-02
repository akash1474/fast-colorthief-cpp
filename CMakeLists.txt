cmake_minimum_required(VERSION 3.10)
project(FastColorThief)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Optional: enable CUDA support
# enable_language(CUDA)
# add_library(cuda_fast_colorthief STATIC include/kernel.cu)
# set_target_properties(cuda_fast_colorthief PROPERTIES LINKER_LANGUAGE CUDA)
# set_target_properties(cuda_fast_colorthief PROPERTIES CUDA_ARCHITECTURES "50;72")

# Library source
add_library(FastColorThief STATIC
    src/fast_colorthief_backend.cpp
)

target_include_directories(FastColorThief PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# If using CUDA:
# target_link_libraries(FastColorThief PRIVATE cuda_fast_colorthief)

# Example usage: Add an executable
# add_executable(example src/example.cpp)
# target_link_libraries(example PRIVATE FastColorThief)