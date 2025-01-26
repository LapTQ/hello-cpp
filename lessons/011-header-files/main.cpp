/*
- We discussed how forward declarations are used to allow the code in one file to access something defined in another file.
- However, as programs grow larger, having to manually add a large number of forward declarations to the top of each file becomes extremely tedious.

- Header files allow us to put declarations in one place and then import them wherever we need them.
- When you #include a file, the "content of the included file is inserted" at the point of inclusion.
- Unlike source files, header files should not be added to your compile command (they are implicitly included by #include statements and compiled as part of your source files).
*/

#include "add.h"
#include <iostream>
#include "hello.h"

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n';

    return 0;
}

/*
- Avoid #including .cpp files.
*/

/* Angled brackets vs double quotes

- Angled brackets: 
  ++ we’re telling the preprocessor that this is a header file we didn’t write ourselves.
  ++ The preprocessor will search for the header only in the "include directories". 
  ++ The "include directories" are configured as part of your project/IDE/compiler settings, 
     and typically default to the directories containing the header files that come with your compiler and/or OS.
- Double-quotes:
  ++ we’re telling the preprocessor that this is a header file that we wrote. 
  ++ The preprocessor will first search for the header file in the current directory. 
     If it can’t find, it will then search the "include directories".
*/

/* Why doesn’t iostream have a .h extension?

See: https://www.learncpp.com/cpp-tutorial/header-files/#:~:text=Why%20doesn%E2%80%99t%20iostream%20have%20a%20.h%20extension%3F
*/

/* Including header files from other directories

- Avoid using relative path:
#include "headers/myHeader.h"
#include "../moreHeaders/myOtherHeader.h"

While this will compile,... if you ever update your directory structure, your code won’t work anymore.

- A better method is to tell your compiler that you have a bunch of header files in some other location, so that it will look there when it can’t find them in the current directory.
  This can generally be done by setting an include path or search directory: 
  "-I./lessons/11-header-files/others"
  
  There is no space after the -I. For a full path (rather than a relative path), remove the . after -I.
*/

/* I didn’t include <someheader> and my program worked anyway! Why?

See: https://www.learncpp.com/cpp-tutorial/header-files/#:~:text=Headers%20may%20include%20other%20headers
*/

/* BEST PRACTICE

- To maximize the chance that missing includes will be flagged by compiler, order your #includes as follows:
  1. the paired header file (e.g., `add.cpp` should `#include "add.h"`)
  2. other headers from same project
  3. 3rd party lib headers (e.g., `#include <boost/tuple/tuple.hpp>`)
  4. standard lib headers

  That way, if one of your user-defined headers is missing an #include for a 3rd party library 
  or standard library header, it’s more likely to cause a compile error so you can fix it.

*/

/* References

- https://www.learncpp.com/cpp-tutorial/header-files/
*/