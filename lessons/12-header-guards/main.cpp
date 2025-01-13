/* 
- We know that a variable or function identifier can only have one definition (not declaration). Defining them more than once will cause a compile error. 
- This can easily happens when a header file #includes another header file:

square.h:

int getSquareSides() // definition
{
    return 4;
}

wave.h:

#include "square.h"

main.cpp:

#include "square.h"
#include "wave.h"

After resolving all the #include, `main.cpp` ends up like this:

int getSquareSides()  // from square.h
{
    return 4;
}

int getSquareSides() // from wave.h (via square.h)
{
    return 4;
}

=> Compile error.
*/

/* Header guards
- we can avoid the above problem via a mechanism called a header guard (also called an include guard)

#ifndef SOME_UNIQUE_NAME_HERE
#define SOME_UNIQUE_NAME_HERE

// your declarations (and certain types of definitions) here

#endif

*/

#include "square.h"
#include "wave.h"

int main()
{
    return 0;
}

/* Header guards do not prevent a header from being included once into different code files
See: https://www.learncpp.com/cpp-tutorial/header-guards/#:~:text=Header%20guards%20do%20not%20prevent%20a%20header%20from%20being%20included%20once%20into%20different%20code%20files
(remind that Directives are only valid from the point of definition to the end of the file in which they are defined.)

=> header files should just contain forward declaration and not definition.

- Can’t we just avoid definitions in header files?
  You may be wondering why you should include header guards if they protect you from something you shouldn’t do???

  ++ See: https://www.learncpp.com/cpp-tutorial/header-guards/#:~:text=Can%E2%80%99t%20we%20just%20avoid%20definitions%20in%20header%20files%3F

- Duplicate declarations are fine -- but even if your header file is composed of all declarations (no definitions) it’s still a best practice to include header guards.
*/


/* References
- https://www.learncpp.com/cpp-tutorial/header-guards/
*/