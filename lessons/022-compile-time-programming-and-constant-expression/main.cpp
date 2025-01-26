/* Compile-time programming

- The compiler may or may not determine what can evaluate at compile-time,
  even if there is a section of code we really want to evaluate at compile-time.
- Because the as-if rule is applied transparently, we get no feedback from the 
  compiler on what portions of code are evaluated at compile-time.

- the C++ language provides ways for us to be explicit about what parts of code 
  we want to execute at compile-time. 
*/

/* Constant expression

- "Constant expression": an expression that must be evaluatable at compile-time.
  (surprisingly, the C++ standard barely mentions “compile-time” at all.)
- An expression that is not a constant expression is often called a non-constant expression, or "runtime expression".

Most commonly, constant expressions contain the following:
- Literals (e.g., 5, 3.14, 'a')
- Most operators with constant expression operands (e.g. 3 + 4, 2 * sizeof(int)).
- Const integral variables with a constant expression initializer (e.g. const int x { 5 };). 
  This is a historical exception -- in modern C++, constexpr variables are preferred.
- Constexpr variables.
- Constexpr function calls with constant expression arguments.

the following cannot be used in a constant expression:
- Non-const variables.
- Const non-integral variables (e.g. const double d { 1.2 };).
  To use such variables in a constant expression, define them as constexpr variables instead.
- Operators with operands that are not constant expressions (e.g. x + y when x or y is not a constant expression.
- Function calls to non-constexpr functions (even when the return value is a constant expression).
- Function parameters (even when the function is constexpr).
*/

#include <iostream>

int getNumber()
{
    std::cout << "Enter a number: ";
    int y{};
    std::cin >> y; // can only execute at runtime

    return y;      // return value only known at runtime
}

int five()
{
    return 5;      // return value known at compile-time
}

int main()
{
    // Literals can be used in constant expressions
    5;                           // constant expression
    1.2;                         // constant expression
    "Hello world!";              // constant expression

    // Most operators that have constant expression operands can be used in constant expressions
    5 + 6;                       // constant expression
    1.2 * 3.4;                   // constant expression
    8 - 5.6;                     // constant expression (even though operands have different types)
    sizeof(int) + 1;             // constant expression (sizeof can be determined at compile-time)

    // Calls to non-constexpr functions can only be used in runtime expressions
    getNumber();                 // runtime expression
    five();                      // runtime expression (even though return value is constant expression)

    // Operators without constant expression operands can only be used in runtime expressions
    std::cout << 5;              // runtime expression (std::cout isn't a constant expression operand)

    // Const integral variables with a constant expression initializer can be used in constant expressions:
    const int a { 5 };           // a is usable in constant expressions
    const int b { a };           // b is usable in constant expressions (a is a constant expression per the prior statement)
    const long c { a + 2 };      // c is usable in constant expressions (operator+ has constant expression operands)

    // Other variables cannot be used in constant expressions (even when they have a constant expression initializer):
    int d { 5 };                 // d is not usable in constant expressions (d is non-const)
    const int e { d };           // e is not usable in constant expressions (initializer is not a constant expression)
    const double f { 1.2 };      // f is not usable in constant expressions (not a const integral variable)

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/constant-expressions/
*/