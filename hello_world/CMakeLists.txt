set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(hello_world hello_world.c)
target_link_options(hello_world PRIVATE LINKER:--max-memory=16777216)
target_link_libraries(hello_world PRIVATE Threads::Threads)

install(TARGETS hello_world)