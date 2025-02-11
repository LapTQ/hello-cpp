/*
- Unlike nested blocks, where any identifier accessible in the outer block is accessible in the nested block, 
  lambdas can only access certain kinds of objects that have been defined outside the lambda:
    + Objects with static (or thread local) storage duration 
      (this includes global variables and static locals).
    + Objects that are constexpr (explicitly or implicitly).
- To access other objects that outside the lambda, you need a capture clause.
*/


/* The capture clause

- Multiple variables can be captured by separating them with a comma.
*/


/* Captures are treated as const by default

- When a lambda is called, operator() is invoked. By default, this operator() treats captures as const.
*/


/* Mutable captures

- ... to allow modifications of variables that were captured.
*/


/* Capture by reference
*/


/* Default captures

- ... captures all variables that are mentioned in the lambda.

- To capture all used variables by value, use a capture value of =.
- To capture all used variables by reference, use a capture value of &.

- Default captures can be mixed with normal captures.
  (the default capture has to be the first element in the capture group.)
*/


/* Defining new variables in the lambda-capture

- The newly defined variable is the same for every call. But if a lambda is "mutable" and modifies a variable 
  that was defined in the capture, the original value will be overridden.
*/


/* Dangling captured variables
*/

#include <iostream>
#include <string>

// returns a lambda
auto makeWalrus(const std::string& name)
{
  // Capture name by reference and return the lambda.
  return [&]() {
    std::cout << "I am a walrus, my name is " << name << '\n'; // Undefined behavior
  };
}

auto makeWalrus2(const std::string& name)
{
  // Capture name by reference and return the lambda.
  return [=]() {
    std::cout << "I am a walrus, my name is " << name << '\n';
  };
}


/* Unintended copies of mutable lambdas 

- Try to avoid mutable lambdas. They are hard to debug.

Read: https://www.learncpp.com/cpp-tutorial/lambda-captures/#:~:text=Unintended%20copies%20of%20mutable%20lambdas
*/


int main()
{
    // The capture clause
    int x{ 4 };
    int y{ 5 };
    auto z{ [y](int x) { return x + y; } (x)};  // y is cloned, and lambda now can access this copy of y.
    std::cout << z << '\n'; // 9


    // Captures are treated as const by default
    [y]() {  ++y } (); // error, inside the lambda, y is const.


    // Mutable captures
    [y]() mutable
    {
        ++y;
        std::cout << y << '\n'; // 6, y is modified inside the lambda.
    } ();
    std::cout << y << '\n'; // 5, y is not modified outside the lambda.


    // Capture by reference
    [&y]() { ++y; } ();
    std::cout << y << '\n'; // 6, y is modified.


    // Default captures
    int a{ 1 }, b{ 2 }, c{ 3 };
    auto d{ [=]() { return a + b + c; } () };   // a, b, c are captured by value.
    std::cout << d << '\n'; // 6
    auto e{ [&, a, b]() { return a + b + c; } () };   // a, b are captured by value, c is captured by reference.


    // Defining new variables in the lambda-capture
    [new_var{ x * y }]() { std::cout << new_var << '\n'; } ();


    // Dangling captured variables
    auto walrus{ makeWalrus("Willy") };
    walrus(); // Undefined behavior
    auto walrus2{ makeWalrus2("Willy") };
    walrus2(); // okay
}


/* References

- https://www.learncpp.com/cpp-tutorial/lambda-captures/
*/