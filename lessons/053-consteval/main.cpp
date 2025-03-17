/* Introduction

- in a non-constant expression that uses a constexpr function, there is no guarantee that the
  constexpr function will be evaluated at compile-time.

- We can force a constexpr function that is eligible to be evaluated at compile-time to
  actually be evaluated at compile-time by storing its return value in a constexpr variable.
- However, this introduces a new variable, which is ugly.
*/


/* (C++20) consteval

- consteval keyword indicates that a function must be evaluated at compile-time.
- Such functions are called immediate functions.
*/

#include <iostream>

consteval int greater(int x, int y) // function is consteval
{
    return (x > y ? x : y);
}

void func1()
{
    constexpr int g { greater(5, 6) };  // ok: will evaluate at compile-time
    greater(5, 6);                      // ok: will evaluate at compile-time
    int x{ 5 }; // not constexpr
    greater(x, 6);                      // error: consteval functions must evaluate at compile-time    
}


/* To have both compile-time or run-time evaluation when we want

- The downside of consteval functions is that such functions can’t evaluate at runtime, 
  making them less flexible than constexpr functions.

- To be able to evaluate a function at compile-time or runtime when we want,
  we can use a helper function:
*/

consteval auto compileTimeEval(auto value)
{
    return value;
}

constexpr int greater2(int x, int y) // function is constexpr
{
    return (x > y ? x : y);
}

void func2()
{   
    int x{ 5 }; // not constexpr
    
    greater2(5, 6); // may or may not evaluate at compile-time
    compileTimeEval(greater2(5, 6)); // will evaluate at compile-time
    greater2(x, 6); // can still call the function at runtime
}


int main()
{   
    // consteval
    func1();


    // To have both compile-time or run-time evaluation when we want
    func2();

    return 0;
}


/* Determining if a constexpr function call is evaluating at compile-time or runtime

- C++ does not currently provide any reliable mechanisms to do this.

- Neither `std::is_constant_evaluated` nor `if consteval` helps. They just tell us
  "if the compiler is being forced to evaluate this at compile-time",
  not "this is evaluating at compile-time".
*/


/* References

- https://www.learncpp.com/cpp-tutorial/constexpr-functions-part-3-and-consteval/
*/