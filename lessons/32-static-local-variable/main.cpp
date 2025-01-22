/*
- The term `static` is one of the most confusing terms in the C++, because static has different meanings in different contexts.

- In previous lessons, `static` gives internal linkage to a non-const global variable.
*/

/* Reminder:

- local variables have automatic duration by default: created at the point of definition, and destroyed when the block is exited.
*/

/* Static local variables

- A static local variable has block scope like a local variable, but its lifetime is until the end of the program like a global variable.
- it’s common to use “s_” to prefix static (static duration) local variables.

Use cases:
- ID generation.
*/

/* Static local constants

- Static local variables can be made const (or constexpr). One good use for a const static local variable is when 
  you have a function that needs to use a const value, but creating or initializing the object is expensive 
  (e.g. you need to read the value from a database). If you used a normal local variable, the variable would be 
  created and initialized every time the function was executed.
*/

#include <iostream>

void incrementAndPrint()
{
    static int s_value{ 1 }; // static duration via static keyword.  This initializer is only executed once.
    ++s_value;
    std::cout << s_value << '\n';
} // s_value is not destroyed here, but becomes inaccessible because it goes out of scope

int main()
{
    incrementAndPrint();
    incrementAndPrint();
    incrementAndPrint();

    return 0;
}

/* References

- https://www.learncpp.com/cpp-tutorial/static-local-variables/
*/