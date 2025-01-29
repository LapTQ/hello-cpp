/*
- Function call to a normal function are not allowed in constant expressions.
*/

#include <iostream>

double calcCircumference(double radius)
{
    constexpr double pi { 3.14159265359 };
    return 2.0 * pi * radius;
}

/* Constexpr functions

- Simply put a constexpr in front of the function declaration.

- If a required constant expression contains a constexpr function call, 
  that constexpr function call must evaluate at compile-time.
- To evaluate at compile-time, two other things must also be true:
    ++ passed arguments must be constant expressions
    ++ all statements in the function must be evaluatable at compile-time

- Constexpr functions can also be evaluated at runtime.
  For example, when passed arguments are not constant expressions.
*/

constexpr double calcCircumference2(double radius) // now a constexpr function
{
    constexpr double pi { 3.14159265359 };
    return 2.0 * pi * radius;
}

int main()
{
    constexpr double radius { 3.0 };
    constexpr double pi { 3.14159265359 };

    // Function call to a normal function are not allowed in constant expressions.
    constexpr double circumference { 2.0 * radius * pi }; // compile
    constexpr double circumference2 { calcCircumference(radius) }; // compile error

    // constexpr function
    constexpr double circumference3 { calcCircumference2(radius) }; // compile

    return 0;
}

/* References

- https://www.learncpp.com/cpp-tutorial/constexpr-functions/
*/