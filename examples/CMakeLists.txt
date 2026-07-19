add_executable(example_basic basic.c)
target_link_libraries(example_basic PRIVATE uuid-static)
target_compile_definitions(example_basic PRIVATE UUID_STATIC)

add_executable(example_v1 v1.c)
target_link_libraries(example_v1 PRIVATE uuid-static)
target_compile_definitions(example_v1 PRIVATE UUID_STATIC)

add_executable(example_v3 v3.c)
target_link_libraries(example_v3 PRIVATE uuid-static)
target_compile_definitions(example_v3 PRIVATE UUID_STATIC)

add_executable(example_v4 v4.c)
target_link_libraries(example_v4 PRIVATE uuid-static)
target_compile_definitions(example_v4 PRIVATE UUID_STATIC)

add_executable(example_v5 v5.c)
target_link_libraries(example_v5 PRIVATE uuid-static)
target_compile_definitions(example_v5 PRIVATE UUID_STATIC)

add_executable(example_v6 v6.c)
target_link_libraries(example_v6 PRIVATE uuid-static)
target_compile_definitions(example_v6 PRIVATE UUID_STATIC)

add_executable(example_v7 v7.c)
target_link_libraries(example_v7 PRIVATE uuid-static)
target_compile_definitions(example_v7 PRIVATE UUID_STATIC)

add_executable(example_v8 v8.c)
target_link_libraries(example_v8 PRIVATE uuid-static)
target_compile_definitions(example_v8 PRIVATE UUID_STATIC)

add_executable(example_parsing parsing.c)
target_link_libraries(example_parsing PRIVATE uuid-static)
target_compile_definitions(example_parsing PRIVATE UUID_STATIC)

add_executable(example_formatting formatting.c)
target_link_libraries(example_formatting PRIVATE uuid-static)
target_compile_definitions(example_formatting PRIVATE UUID_STATIC)

add_executable(example_validation validation.c)
target_link_libraries(example_validation PRIVATE uuid-static)
target_compile_definitions(example_validation PRIVATE UUID_STATIC)

add_executable(example_comparison comparison.c)
target_link_libraries(example_comparison PRIVATE uuid-static)
target_compile_definitions(example_comparison PRIVATE UUID_STATIC)

add_executable(example_serialization serialization.c)
target_link_libraries(example_serialization PRIVATE uuid-static)
target_compile_definitions(example_serialization PRIVATE UUID_STATIC)

add_executable(example_threading threading.c)
target_link_libraries(example_threading PRIVATE uuid-static)
target_compile_definitions(example_threading PRIVATE UUID_STATIC)

add_executable(example_error_handling error_handling.c)
target_link_libraries(example_error_handling PRIVATE uuid-static)
target_compile_definitions(example_error_handling PRIVATE UUID_STATIC)

add_executable(example_custom_uuid custom_uuid.c)
target_link_libraries(example_custom_uuid PRIVATE uuid-static)
target_compile_definitions(example_custom_uuid PRIVATE UUID_STATIC)

add_executable(example_binary_conversion binary_conversion.c)
target_link_libraries(example_binary_conversion PRIVATE uuid-static)
target_compile_definitions(example_binary_conversion PRIVATE UUID_STATIC)
