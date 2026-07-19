cmake_minimum_required(VERSION 3.14)

project(uuid
    VERSION 0.1.0
    DESCRIPTION "Production-grade UUID library for C/C++ (RFC 9562)"
    HOMEPAGE_URL "https://github.com/muhammad-fiaz/uuid"
    LANGUAGES C
)

# ── Options ──────────────────────────────────────────────────────────────

option(UUID_BUILD_SHARED      "Build shared library"          ON)
option(UUID_BUILD_STATIC      "Build static library"          ON)
option(UUID_BUILD_TESTS       "Build unit tests"              OFF)
option(UUID_BUILD_EXAMPLES    "Build examples"                OFF)
option(UUID_BUILD_BENCHMARKS  "Build benchmarks"              OFF)
option(UUID_WERROR            "Treat warnings as errors"      OFF)

# ── C Standard ───────────────────────────────────────────────────────────

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# ── Platform Detection ───────────────────────────────────────────────────

if(WIN32)
    add_definitions(-DUUID_PLATFORM_WINDOWS)
elseif(APPLE)
    add_definitions(-DUUID_PLATFORM_APPLE)
elseif(UNIX)
    add_definitions(-DUUID_PLATFORM_LINUX)
endif()

# ── Compiler Warnings ────────────────────────────────────────────────────

if(MSVC)
    add_compile_options(/W4)
    if(UUID_WERROR)
        add_compile_options(/WX)
    endif()
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wno-sign-conversion)
    if(UUID_WERROR)
        add_compile_options(-Werror)
    endif()
    if(CMAKE_C_COMPILER_ID MATCHES "Clang")
        add_compile_options(-Wno-unsafe-buffer-usage)
    endif()
endif()

# ── Source Files ─────────────────────────────────────────────────────────

set(UUID_SOURCES
    src/uuid.c
)

set(UUID_HEADERS
    include/uuid/uuid.h
)

# ── Include Directories ──────────────────────────────────────────────────

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# ── Platform Libraries ───────────────────────────────────────────────────

if(WIN32)
    set(UUID_PLATFORM_LIBS bcrypt)
else()
    set(UUID_PLATFORM_LIBS "")
endif()

# ── Static Library ───────────────────────────────────────────────────────

if(UUID_BUILD_STATIC)
    add_library(uuid-static STATIC ${UUID_SOURCES} ${UUID_HEADERS})
    target_include_directories(uuid-static
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
    )
    set_target_properties(uuid-static PROPERTIES
        OUTPUT_NAME uuid
        POSITION_INDEPENDENT_CODE ON
    )
    target_compile_definitions(uuid-static PRIVATE UUID_BUILDING_STATIC)
    target_link_libraries(uuid-static PRIVATE ${UUID_PLATFORM_LIBS})
    add_library(uuid::static ALIAS uuid-static)
endif()

# ── Shared Library ───────────────────────────────────────────────────────

if(UUID_BUILD_SHARED)
    add_library(uuid-shared SHARED ${UUID_SOURCES} ${UUID_HEADERS})
    target_include_directories(uuid-shared
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
    )
    set_target_properties(uuid-shared PROPERTIES
        OUTPUT_NAME uuid
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        POSITION_INDEPENDENT_CODE ON
        DEFINE_SYMBOL UUID_BUILDING_SHARED
    )
    target_compile_definitions(uuid-shared PRIVATE UUID_BUILDING_SHARED)
    target_link_libraries(uuid-shared PRIVATE ${UUID_PLATFORM_LIBS})
    add_library(uuid::shared ALIAS uuid-shared)
endif()

# ── Default Target ───────────────────────────────────────────────────────

if(UUID_BUILD_STATIC)
    add_library(uuid ALIAS uuid-static)
elseif(UUID_BUILD_SHARED)
    add_library(uuid ALIAS uuid-shared)
endif()

# ── Tests ────────────────────────────────────────────────────────────────

if(UUID_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# ── Examples ─────────────────────────────────────────────────────────────

if(UUID_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# ── Benchmarks ───────────────────────────────────────────────────────────

if(UUID_BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()

# ── Install ──────────────────────────────────────────────────────────────

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(FILES include/uuid/uuid.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/uuid
)

if(UUID_BUILD_STATIC)
    install(TARGETS uuid-static
        EXPORT uuid-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
endif()

if(UUID_BUILD_SHARED)
    install(TARGETS uuid-shared
        EXPORT uuid-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif()

install(EXPORT uuid-targets
    FILE uuid-targets.cmake
    NAMESPACE uuid::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/uuid
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/uuid-config-version.cmake"
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/uuid-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/uuid-config.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/uuid
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/uuid-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/uuid-config-version.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/uuid
)

# ── pkg-config ───────────────────────────────────────────────────────────

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/uuid.pc.in"
    "${CMAKE_CURRENT_BINARY_DIR}/uuid.pc"
    @ONLY
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/uuid.pc"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)
