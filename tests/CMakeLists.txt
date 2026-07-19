add_executable(test_uuid test_uuid.c)
target_link_libraries(test_uuid PRIVATE uuid-static)
target_include_directories(test_uuid PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_definitions(test_uuid PRIVATE UUID_STATIC)

add_test(NAME uuid_tests COMMAND test_uuid)
