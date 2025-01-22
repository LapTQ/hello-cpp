/* function overhead

For example,
int min(int x, int y)
{
    return (x < y) ? x : y;
}

- When a call to min() is encountered, the CPU must store the address of the current instruction it is executing
  along with the values of various CPU registers. Then parameters x and y must be instantiated and then initialized. 
- Then the execution path has to jump to the code in the min() function. When the function ends, the program has to 
  jump back to the location of the function call, and the return value has to be copied so it can be output.
- All of the extra work that must happen to setup, facilitate, and/or cleanup after some task is called overhead.
- for small functions (such as min() above), the overhead costs can be larger than the time needed to actually execute the function’s code!
- If a small function is called often, it can result in a significant performance penalty over writing the same code in-place.
*/

/* Inline expansion

- Inline expansion is a process where a function call is replaced by the code from the called function’s definition.

For example, if the compiler expanded the min() calls
std::cout << ((5 < 6) ? 5 : 6) << '\n';
=> calls to function min() have been replaced by the code in the body of the min() function. This allows us to avoid the overhead.

- Inline expansion is best suited to "simple, short functions" (so that the overhead is insignificant to the function's running time) that are called frequently.
*/

/* inline keyword

inline int min(int x, int y) // inline keyword means this function is an inline function
{
    return (x < y) ? x : y;
}

- Historically, compilers were not very good at determining whether inline expansion would be beneficial, so the inline keyword was introduced
  as a hint to the compiler.
- However, modern C++ compilers are better than human in most cases, and will likely ignore the inline keyword => Don't use inline keyword for this purpose.
*/

/* Modern `inline` keyword - multiple definitions are allowed

- Reminder: multiple definitions of the same function are not allowed in C++.
- In modern C++, an inline function is one that is allowed to be defined in multiple translation units (without violating the ODR).

Inline functions have two primary requirements:
- The compiler needs to be able to see the full definition of an inline function in each translation unit where the function is used (a forward declaration will not suffice).
- Every definition for an inline function (with external linkage, which functions have by default) must be identical, otherwise undefined behavior will result.
*/

#include <iostream>

double circumference(double radius); // forward declaration

inline double pi() { return 3.14159; } // also defined in math.cpp
// both files have a definition for function pi() -- however, because this function has been marked as inline, this is acceptable
// and the linker will de-duplicate them. If you remove the inline keyword from both definitions of pi(), you’ll get an ODR violation.

int main()
{
    std::cout << pi() << '\n';

    return 0;
}

/* (Optional reading) the historic and modern use of inline may seem a bit unrelated, but they are highly interconnected.

- In order to actually perform inline expansion of a function call, the compiler must be able to see the full definition of this function 
  in each translation unit where the function is used -- otherwise it wouldn’t know what to replace each function call with. 
  A function defined in another translation unit can’t be inline expanded in the current translation unit being compiled.
=> it's common to "copy" the function definition into each translation unit => violates the ODR.
=> Modernly, we use inline for the ODR-exemption.

=> Inline functions are typically defined in "header" files, where they can be #included into the top of any code file 
   that needs to see the full definition of the identifier. This ensures that all inline definitions for an identifier are "identical".
   This is particularly useful for "header-only libraries" (no .cpp files are included).
*/

/* Header-only libraries

- Header-only libraries are popular because there are no source files that need to be added to a project to use them and nothing that needs to be linked. 
  You simply #include the header-only library and then can use it.

- Avoid the use of the inline keyword unless you have a specific, compelling reason to do so (e.g. you’re defining those functions or variables in a header file).
*/

/* Why not make all functions inline and defined in a header file?

- Mainly because doing so can increase your compile times significantly.
*/

/* References

- https://www.learncpp.com/cpp-tutorial/inline-functions-and-variables/
*/