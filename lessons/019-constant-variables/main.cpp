/* Named constants

- Named constants != Literal constants (constant values that are not associated with an identifier).

- 3 types of named constants:
  ++ constant variables
  ++ Object-like macros with substitution text
  ++ Enumerated constants
*/

#include <iostream>

void printInt(const int x) // Function parameters can be made constants, but it is not necessary
{
    std::cout << x << '\n';
}

int main() {
    const double gravity { 9.8 };  // preferred use of const before type

    return 0;
}

/* constant variables

- must be initialized
- values can not be changed

- If a variable can be made constant, it generally should be made constant:
  ++ more opportunity for the compiler to optimize programs.
  ++ we don’t have to worry about a section of code when debugging.
*/

/*
- In modern C++ we don’t make value parameters const because we generally don’t care if the 
  function changes the value of the parameter (since it’s just a copy that will be destroyed 
  at the end of the function anyway). The const keyword also adds a small amount of unnecessary 
  clutter to the function prototype.
*/

/* Prefer constant variables to preprocessor macros

- 3 problems with preprocessor macros:
  ++ macros don’t follow normal C++ scoping rules:
  #define gravity 9.8
  ...
  void printGravity(double gravity) // compilation error

  ++ harder to debug: compiler and debugger never see the macro because it has already been replaced before they run.
  ++ behaves differently than everything else in C++. Inadvertent mistakes can be easily made as a result.
*/

/* type qualifiers

- `const` is an example of a type qualifier. Type qualifiers is a keyword that is applied to a type to
  modify how that type behaves.
*/