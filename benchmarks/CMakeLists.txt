add_executable(bench_uuid bench_uuid.c)
target_link_libraries(bench_uuid PRIVATE uuid-static)
target_compile_definitions(bench_uuid PRIVATE UUID_STATIC)
