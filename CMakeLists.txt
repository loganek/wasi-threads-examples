cmake_minimum_required(VERSION 3.16)

project(wasi_threads_examples)

set(CMAKE_EXECUTABLE_SUFFIX ".wasm")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_subdirectory(hello_world)
add_subdirectory(merge_sort)