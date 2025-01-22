/* Side note

- Constexpr functions are implicitly inline, but constexpr variables are not implicitly inline. 
  If you want an inline constexpr variable, you must explicitly mark it as inline.
- Inline variables have external linkage by default, so that they are visible to the linker.
  This is necessary so the linker can "de-duplicate" the "definitions".

Reminder:
- For non-extern constant global variables, the point of declaration is until the end of the "file" in which they are declared.
*/


/* Solution 1: Global constants as internal variables

Common steps:
- Create a header file
- Define a namespace
- Add all your constants inside the namespace, make sure they are constexpr
- #include the header file wherever you need it

Advantages:
- Simple, fine for small projects

Downsides:
- Changing anything in the header requires recompiling all files that include it => lead to lengthy rebuild times for larger projects.
- Each translation unit get its own copy of the constants => use a lot of memory if the constants are large.
*/

/* Solution 2: Global constants as external variables

Common steps:
- Create a .cpp file, define a namespace, and define all your constants (with `extern constexpr`) inside the namespace.
- Create a corresponding header file and forward declare the constants.
- #include the header file wherever you need it.

Advantages:
- The symbolic constants are defined only once (in the .cpp file), any changes to the constants only require recompiling the .cpp file.

Downsides:
- Because forward declarations can’t be constexpr, this means outside of the .cpp file where the constants are defined, the constants cannot be used in constant expressions.
*/


/* Solution 3: Global constants as inline variables (C++17)

Common steps:
- Create a header file
- Define a namespace
- Define all your constants (with `inline constexpr`) inside the namespace
- #include the header file wherever you need it.

Advantages:
- The constants will only be instantiated once and shared across all code files (linker will de-duplicate definition) (solve from Solution 1).
- Can be used in constant expressions in any translation unit (solve from Solution 2).

Downsides:
- Changing anything in the header requires recompiling all files that include it (not solve from Solution 1).
- Only works in C++17 and later.
*/

// => use Solution 3 if C++17 or later is available:

#include "constants.h"

#include <iostream>

int main()
{
    double radius{ 5 };

    std::cout << "The circumference is: " << 2 * radius * constants::pi << '\n';

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/sharing-global-constants-across-multiple-files-using-inline-variables/
*/