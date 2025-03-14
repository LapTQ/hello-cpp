

## Print newline

* ✅ Use character `"\n"`:
* ❌ Avoid using `std::endl`. It flushes the buffer, which is slower.

## Comma operator

* ❌ Avoid using **comma operator**, except in `for` loops:
```C++
std::cout << (++x, ++y) << '\n'; // evaluates left and right, then retuns the right operand
```


## Macro

* ✅ Can use `#if 0` to comment out a large block of code that contains **multi-line comments**. Change it to `#if 1` when needed.
* ❌ Avoid using **object-like macros with substitution text**, as better methods are available.


## `#include`

* ❌ Avoid `#including` .cpp files.
* Including header files from other directories:
    * ❌ Avoid using relative path (e.g, `#include "headers/myHeader.h"`).
    * ✅ Tell your compiler about other locations to search for (e.g., `-I./lessons/11-header-files/others`).
* ✅ To maximize the chance that missing includes will be flagged by compiler, order your `#includes` as follows:
    1. the paired header file (`add.cpp` and `#include "add.h"`)
    2. other headers from same project
    3. 3rd party lib headers
    4. standard lib headers
* ✅ Always have a **header guard** in a header file to avoid violating ODR from having **a** code file #include a header (which may contain **definition**) multiple time. 
    * ⚠️ However, header guards do not prevent **multiple** code file `#include` the same header.
* ❌ Don't use `#pragme once`. Use header guard instead.
* ✅ Use a complex name for your header guard (e.g., `PROJECT_PATH_FILE_H`). This is to avoid case where 2 separated header files (e.g., `A/config.h` and `B/config.h`) might have the same name of header guard (e.g., `CONFIG_H`).


# Debugging

* ✅ use `std::cerr` (not buffered) instead of `std::cout` (may be buffered).
* To enable/disable debugging mode:
    * 👍 Solution 1: Conditionalizing your debugging code with macro: `#define ENABLE_DEBUG` in a header file and `#include` it everywhere. But ensure that you're not misspell `ENABLE_DEBUG` or forgot `#include` the header file.
    * 👍 Use `plog` logger. ❌ Don't use `std::clog` logger.


## Data types

* ❌ Avoid using unsigned types.
* ❌ Avoid `short`, `long`, fast/least integral types (prefer a fixed-width integer type instead).
* ❌ Avoid 8-bit fixed-width integer types (prefer a 16-bit fixed-width integer type instead).
* ❌ Avoid `long double`.
* ⚠️ `std::int8_t` and `std::uint8_t` likely behave like `signed char` and `unsigned char` instead of integers.


# Input text

* To read whitespace characters (type `char`):
    * ❌ can't use `std::cin >>`
    * ✅ use `std::cin.get(ch)`


# Compile-time optimization

* ✅ Most compilers default to no optimization, so if you’re using a command-line 
  compiler, you’ll need to enable optimization yourself.