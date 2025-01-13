/*
- We discussed how forward declarations are used to allow the code in one file to access something defined in another file.
- However, as programs grow larger, having to manually add a large number of forward declarations to the top of each file becomes extremely tedious.

- Header files allow us to put declarations in one place and then import them wherever we need them.
- When you #include a file, the content of the included file is inserted at the point of inclusion.
- Unlike source files, header files should not be added to your compile command (they are implicitly included by #include statements and compiled as part of your source files).
*/

#include "add.h"
#include <iostream>

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n';

    return 0;
}

/*
- Avoid #including .cpp files.
*/


/* References
- https://www.learncpp.com/cpp-tutorial/header-files/
*/