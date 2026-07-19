# Version Info

Functions for getting library version information.

## uuid_version_string

```c
const char *uuid_version_string(void);
```

Get the library version as a string.

```c
printf("uuid version: %s\n", uuid_version_string());
// "uuid version: 0.1.0"
```

## uuid_version_info

```c
void uuid_version_info(int *major, int *minor, int *patch);
```

Get the library version as integers.

```c
int major, minor, patch;
uuid_version_info(&major, &minor, &patch);
printf("Version: %d.%d.%d\n", major, minor, patch);
// "Version: 0.1.0"
```

## Constants

```c
#define UUID_VERSION_MAJOR  0
#define UUID_VERSION_MINOR  1
#define UUID_VERSION_PATCH  0
#define UUID_VERSION_STRING "0.1.0"
```
