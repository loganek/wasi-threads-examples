add_executable(merge_sort merge_sort_mt.c merge_sort.c)
target_link_options(merge_sort PRIVATE LINKER:--max-memory=268435456)
target_link_libraries(merge_sort PRIVATE Threads::Threads)

install(TARGETS merge_sort)