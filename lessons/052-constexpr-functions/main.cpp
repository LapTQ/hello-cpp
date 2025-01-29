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

Reminder: 
- in contexts that do not require a constant expression, the compiler 
  may choose whether to evaluate a constant expression at either compile-time or at runtime. 
*/

constexpr double calcCircumference2(double radius) // now a constexpr function
{
    constexpr double pi { 3.14159265359 };
    return 2.0 * pi * radius;
}


/* Constexpr/consteval function parameters are not constexpr

- The parameters of a constexpr function cannot be declared as `constexpr` (nor implicitly `constexpr`).
- Because such parameters are not constexpr, they cannot be used in constant expressions within the function.
*/

constexpr int foo(int b)    // b is not constexpr, and cannot be used in constant expressions
{
    constexpr int b2 { b }; // compile error: constexpr variable requires constant expression initializer
}


/* Constexpr functions are implicitly inline

- a constexpr function called in multiple files needs to have its definition 
  included into each translation unit. A forward declaration will not suffice because
  at compile-time, the compiler must be able to see the full definition of the constexpr function prior to such function calls.
 
- So, constexpr functions are implicitly inline.

Best practice
- Constexpr/consteval functions used in a single source file (.cpp) should be 
  defined in the source file above where they are used.
- Constexpr/consteval functions used in multiple source files should be defined in a header file.
*/


/*
another example
*/

constexpr int greater(int x, int y)
{
    return (x > y ? x : y);
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


    // Constexpr/consteval function parameters are not constexpr
    constexpr int a { 5 };
    std::cout << foo(a); // okay: constant expression a can be used as argument to constexpr function foo()

    
    // another example
    constexpr int g { greater(5, 6) };              // case 1: always evaluated at compile-time
    greater(5, 6); // case 2: all arguments are constant expressions => may be evaluated at either runtime or compile-time
    int x{ 5 }; // not constexpr but value is known at compile-time
    greater(x, 6); // case 3: likely evaluated at runtime
    std::cin >> x;
    greater(x, 6); // case 4: always evaluated at runtime

    return 0;
}

/* References

- https://www.learncpp.com/cpp-tutorial/constexpr-functions/
- https://www.learncpp.com/cpp-tutorial/constexpr-functions-part-2/
*/