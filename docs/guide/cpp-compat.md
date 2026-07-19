# C++ Compatibility

The uuid library compiles correctly with C++ compilers.

## Usage in C++

The headers include proper `extern "C"` guards:

```cpp
#include <uuid/uuid.h>
#include <iostream>

int main() {
    uuid_t uuid;
    char buf[UUID_STRING_LEN];

    uuid_v4(&uuid);
    uuid_format(&uuid, buf, sizeof(buf));
    std::cout << "UUID: " << buf << std::endl;

    return 0;
}
```

## Supported C++ Standards

- C++98
- C++03
- C++11
- C++14
- C++17
- C++20
- C++23

## Compilation

```bash
g++ -std=c++17 -I include example.cpp -L build -luuid -o example
```

## Notes

- No C++ headers or namespaces are required
- All C API functions are available from C++
- Avoids C++ reserved keywords in API names
- No exceptions thrown from C API (error codes returned instead)
