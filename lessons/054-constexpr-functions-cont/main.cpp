/* Constexpr/consteval functions can use function parameters and local variables 
   as arguments in constexpr function calls

Reminder:
- When a constexpr (or consteval) function is being evaluated at compile-time, 
  any other functions it calls are required to be evaluated at compile-time.

- Perhaps surprisingly, a constexpr or consteval function can use its 
  function parameters (which aren’t constexpr) or even local variables (which may not be const at all) 
  as arguments in a constexpr function call.
- This is because, at compile-time, the value of all function parameters and local variables 
  must be known to the compiler.
*/

#include <iostream>

constexpr int goo(int c) // goo() is now constexpr
{
    return c;
}

constexpr int foo(int b) // b is not a constant expression within foo()
{
    return goo(b);       // if foo() is resolved at compile-time, then `goo(b)` can also be resolved at compile-time
}


int main()
{
    constexpr int a { foo(5) };     // foo(5) must evaluate at compile-time
    std::cout << a << '\n';

    return 0;
}


/* When should I constexpr a function?

+ When it's part of a required constant expression.
+ The function always returns the same return result when given the same arguments.
+ The function has no side effects (e.g. it doesn’t change the value of static local or global variables, doesn’t do input or output, etc…).
*/


/* Why not constexpr every function?

- Once a function is made constexpr, it can be called by other constexpr functions 
  or used in contexts that require constant expressions. Removing the constexpr later will break such code.
- harder to debug because you can’t inspect them at runtime.
*/

/* References

- https://www.learncpp.com/cpp-tutorial/constexpr-functions-part-4/
*/