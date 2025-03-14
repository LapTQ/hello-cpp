

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

* Naming your header guard:

