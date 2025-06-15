
**easystd** is a lightweight C library providing easy-to-use standard data structures, mathematical utilities, and error handling for C projects. It aims to simplify common programming tasks by offering convenient abstractions and container types, while keeping the interface minimal and the implementation efficient.

*This project was created as a training project and does not pretend to be anything serious.*
## Features

- **Structs of different type of containers**: Array, grow(same as std::vector)
- **Error Handling**: Unified error codes and helper macros for robust C code.
- **Mathematics Utilities**: Complex number arithmetic, constants, and integer math helpers like GCD/LCM.
- **Consistent API**: All modules follow clear idioms for initialization, cleanup, and error reporting.
- **Header-Only Interfaces**: Most functionality is accessible via `#include`-able headers.
- **Simple Build System**: Makefile for static and dynamic library generation, installation, and cleaning.

## Getting Started

### 1. Build the Library

To build the static library (`libestd.a`):

```sh
make
```

To build the dynamic library (`libestd.so`):

```sh
make dynamic
```

You can also build with optimizations for release(compile with `-O3` flag):

```sh
make release=1
```

### 2. Install (Optional)

To install headers and libraries system-wide (requires `sudo`). *This will install both, static and dynamic library*:

```sh
sudo make install
```

Or explicit tell `make` what to install:

```sh
sudo make install_static
sudo make install_dynamic
```

This installs to `/usr/local/lib` and `/usr/local/include`.

To specife path, use:

```sh
sudo make install INSTALL_DIR="custom/path"
```

### 3. Usage

Include the main header in your C source:

```c
#include <estd.h>
```

Or individual headers:
```c
#include <estd/array.h>
```

Link your program with the static or dynamic library:

```sh
gcc your_program.c -o your_program -lestd
```

Or:

```sh
gcc -I/path-to-headers -L/path-to-lib your_program.c -o your_program -lestd
```

## Example: Using the String struct

```C
#include <estd.h>
#include <stdio.h>

int main() {
 string* str = string_create("Foo");
 printf("%s\n",string_cstr(str));
 // Output: Foo

 string_append(str,", Bar");
 printf("%s\n",string_cstr(str));
 // Output: Foo, Bar

 string_free(str);
 return 0;
}
```

## Example: Using the Array Container

```c
#include <estd.h>
#include <stdio.h>

int main() {
  array *arr = array_init(10);
  int value = 42;
  array_set(arr, 0, &value); // Note: pointer to stack object will die when program reach end of the scope  
  int result = array_get_as(int, arr, 0, NULL);
    
  printf("Value: %d\n", result);
  // Output: 42
    
  array_free(arr, NULL);
  return 0;
}
```

## Modules Overview

### String (`estd/estring.h`)

Struct for simple usage of C-string type 

### Array (`estd/array.h`)

Dynamic, fix-sized `generic`(use void* to store elements) container

### Grow (`estd/grow.h`)

Dynamic size container for `generic` elements

### Error Handling (`estd/eerror.h`)

- Unified `easy_error` codes (OK, NULL_POINTER, etc.)
- Macros: `CHECK_NULL_PTR`, `CHECK_ALLOCATION`, `SET_CODE_ERROR`
- `easy_error_message(easy_error)`: Get readable error string.

### Math (`estd/emath.h`)

- Complex number struct and operators (`complex_plus`, etc.)
- Math constants (`_PI`, `_E`, etc.)
- `gcd`, `lcm` for integer math.

## Development

- All code is written in portable C23.
- Contributions, bug reports, and feature requests are welcome!

## Cleaning Up

To remove all build artifacts:

```sh
make clean
```

To uninstall:

```sh
sudo make uninstall
```

## Road map

- `Containers`: list, deque, stack, queue
- Iterators and macros `foreach`
- Hash table

## License

[MIT](LICENSE)

---

**easystd** – Easy, modern, and robust C standard utilities for everyone!
