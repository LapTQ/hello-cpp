/* Linkage

- An identifier’s linkage determines whether other declarations of that name refer to the same object or not.
- Global variables and function identifiers can have either "internal linkage" or "external linkage".
- An identifier with internal linkage can be seen and used within a single translation unit, 
  but it is not accessible from other translation units. 
- This means that if two source files have identically named identifiers with internal linkage, those identifiers 
  will be treated as independent.
*/


/* Global variables

- Global variables with internal linkage are sometimes called internal variables.
- Global variables with external linkage are sometimes called external variables.
*/

// internal linkage
static int g_x1{}; // non-constant globals have external linkage by default, but can be given internal linkage via the static keyword
const int g_y1{ 1 }; // const globals have internal linkage by default
constexpr int g_z1{ 2 }; // constexpr globals have internal linkage by default
// only accessible within this main.cpp

// external linkage
int g_x2 { 2 }; // non-constant globals are external by default (no need to use extern)
extern const int g_y2 { 3 }; // const globals can be defined as extern, making them external
extern constexpr int g_z2 { 3 }; // constexpr globals can be defined as extern, making them external


/* Functions with internal linkage

- function identifiers also have linkage. Functions default to external linkage, but can be set to internal linkage via the static keyword.
*/

// This program won’t link, because function add is not accessible outside of add.cpp.
int add(int x, int y);


/* Use an external global variable that has been defined in another file

- you also must place a forward declaration using the extern keyword (with no initialization value).
- Note that function forward declarations don’t need the extern keyword

WARNING:
- If you want to define an uninitialized non-const global variable, 
   do not use the extern keyword, otherwise C++ will think you’re trying to make a forward declaration for the variable.
- Although constexpr variables can be given external linkage via the extern keyword, 
  they can not be forward declared as constexpr. 
  This is because the compiler needs to know the value of the constexpr variable at compile time, while the external variable (in
  another file)'s value is known until link time.
*/

// forward declaration of a global variable defined in another file
extern int min;


#include <iostream>

int main()
{
    std::cout << min << '\n';
    return 0;
}


/* References

https://www.learncpp.com/cpp-tutorial/internal-linkage/
*/