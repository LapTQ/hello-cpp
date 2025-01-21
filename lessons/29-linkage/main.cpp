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

/* Functions with internal linkage

- function identifiers also have linkage. Functions default to external linkage, but can be set to internal linkage via the static keyword.
*/

#include <iostream>

// internal linkage
static int g_x{}; // non-constant globals have external linkage by default, but can be given internal linkage via the static keyword
const int g_y{ 1 }; // const globals have internal linkage by default
constexpr int g_z{ 2 }; // constexpr globals have internal linkage by default
// only accessible within this main.cpp

// external linkage
int g_x { 2 }; // non-constant globals are external by default (no need to use extern)
extern const int g_y { 3 }; // const globals can be defined as extern, making them external
extern constexpr int g_z { 3 }; // constexpr globals can be defined as extern, making them external

// This program won’t link, because function add is not accessible outside of add.cpp.
int add(int x, int y);

int main()
{
    std::cout << g_x << ' ' << g_y << ' ' << g_z << '\n';
    return 0;
}

/* When to use internal linkage

- want to make sure isn’t accessible to other files. E.g., helper functions that are only used in one file.
*/

/* References

https://www.learncpp.com/cpp-tutorial/internal-linkage/
*/