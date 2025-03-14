

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


## `#include` and header files

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


## Debugging

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


### Input text

* To read whitespace characters (type `char`):
    * ❌ can't use `std::cin >>`
    * ✅ use `std::cin.get(ch)`
* To read a line (including whitespace):
    * ❌ don't use `std::cin >>`
    * ✅ use `std::getline()`


## Compile-time optimization

* ✅ Most compilers default to no optimization, so if you’re using a command-line 
  compiler, you’ll need to enable optimization yourself.


## Using `std:string` and `std::string_view`

* ⚠️ Don't pass a `std::string` to a function by value. Because, it will make an expensive copy.
* ✅ Use `std::string_view` when passing a string to a function by value for read-only access purpose to avoid expensive copy.
* ✅ To view a substring of a string, use `std::string_view` with `.remove_prefix()` and `.remove_suffix()`.
* Initialize a `std::string_view`:
    * ❌ Don't initialize with a `std::string` **literal**. Because, the temporary `std::string` literal will be destroyed at the end of the statement:

        ```C++
        std::string_view name { "Alex"s }; // "Alex"s creates a temporary std::string
        std::cout << name << '\n'; // undefined behavior
        ```
    * 👍 It's okay to initialize with a C-style string **literal** or a `std::string_view` **literal**. Because, C-style string literals exist for the entire program.
* ⚠️ Returning a string in a function that has return type `std::string_view`: 2 main cases when this can be done safely:
    * 👍 when the returned object is a C-style string literals:

        ```C++
        std::string_view getBoolName(bool b)
        {
            return "false";
        }
        ```
    * 👍 when the returned object is a function parameter of type `std::string_view`:

        ```C++
        std::string_view firstAlphabetical(std::string_view s1, std::string_view s2)
        {
            if (s1 < s2)
                return s1;
            return s2;
        }
        ```


## Comparing floating point values

* ❌ It's very dangerous to compare floating point values directly using relational operators (<, >, <=, >=, ==, !=).
    * 👍 One exception: compare a floating point **literal** with a **variable of the same type** that has been initialized with a **literal of the same type**.
* ❌ It's generally not safe to compare floating point values of **different** types.


## Namespaces

* ✅ Naming convention: Company or org :: project or library :: module (e.g. `Foosoft::Foologger::Lang`)
    