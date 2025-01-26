/*
- If the default type of a literal is not as desired, you can change the type of a literal by adding a suffix
- In most cases, suffixes aren’t needed (except for f).
*/

#include <iostream>

int main() {
    float f { 4.1 }; // warning: 4.1 is a double literal, not a float literal

    double protonCharge { 1.6e-19 }; // e to represent the exponent

    std::cout << "Hello, world!"; // string literal

    return 0;
}

/* strings are not a fundamental type in C++.

- they have a strange, complicated type that is hard to work with.
  they are often called C strings or C-style strings, as they are inherited from the C-language.

- things worth knowing about C-style string literals:
  ++ All C-style string literals have an implicit null terminator `\0` at the end.
     (This is the reason the string "Hello, world!" has type const char[14] rather than const char[13])
  ++ Unlike most other literals, C-style string literals are const objects that are created at the start 
     of the program and are guaranteed to exist for the entirety of the program. 
     This fact will become important in a few lessons, when we discuss std::string_view.
*/

/* Magic numbers

- Avoid magic numbers in your code (use constexpr variables instead).
*/