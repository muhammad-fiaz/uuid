# Installation

How to install and integrate the uuid library into your project.

## Requirements

| Requirement | Version |
|-------------|---------|
| C Compiler | C99 or later (GCC 4.8+, Clang 3.0+, MSVC 2015+) |
| CMake | 3.14+ |
| Meson | 0.56+ (alternative) |

## Method 1: CMake (FetchContent)

```cmake
include(FetchContent)
FetchContent_Declare(uuid
    GIT_REPOSITORY https://github.com/muhammad-fiaz/uuid.git
    GIT_TAG v0.1.0)
FetchContent_MakeAvailable(uuid)
target_link_libraries(your_target PRIVATE uuid::static)
```

## Method 2: CMake (Subdirectory)

```bash
git clone https://github.com/muhammad-fiaz/uuid.git
```

```cmake
add_subdirectory(uuid)
target_link_libraries(your_target PRIVATE uuid::static)
```

## Method 3: Meson

```meson
uuid_dep = dependency('uuid', version: '>=0.1.0')
```

## Method 4: Build from Source

```bash
git clone https://github.com/muhammad-fiaz/uuid.git
cd uuid
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
sudo cmake --install build  # or set CMAKE_INSTALL_PREFIX
```

## Build Options

| Option | Default | Description |
|--------|---------|-------------|
| `UUID_BUILD_SHARED` | ON | Build shared library |
| `UUID_BUILD_STATIC` | ON | Build static library |
| `UUID_BUILD_TESTS` | OFF | Build unit tests |
| `UUID_BUILD_EXAMPLES` | OFF | Build examples |
| `UUID_BUILD_BENCHMARKS` | OFF | Build benchmarks |
| `UUID_WERROR` | OFF | Treat warnings as errors |

## Compiler Flags

The library requires only C99. No special compiler flags are needed:

```bash
# GCC/Clang
gcc -std=c99 -I/path/to/uuid/include myfile.c -L/path/to/uuid/lib -luuid

# MSVC
cl /I C:\path\to\uuid\include myfile.c
```

## Verifying Installation

```c
#include <uuid/uuid.h>
#include <stdio.h>

int main(void) {
    printf("uuid version: %s\n", uuid_version_string());
    return 0;
}
```
