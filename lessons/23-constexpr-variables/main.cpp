/* constexpr keyword

- A constexpr variable is always a compile-time constant.
- constexpr variable must be initialized with a constant expression, otherwise a compilation error will result.
*/

/* const vs constexpr

- const means that the value of an object cannot be changed after initialization. 
  The value of the initializer may be known at compile-time or runtime.
- constexpr means that the object can be used in a constant expression. The value of the initializer 
  must be known at compile-time. The constexpr object can be evaluated at runtime or compile-time.

- Constexpr variables are implicitly const.
- Unlike const, constexpr is not part of an object’s type. Therefore a variable defined as 
  constexpr int actually has type const int (due to the implicit const that constexpr provides for objects).
*/

/* constexpr functions

- A constexpr function is a function that can be called in a constant expression.
- a constexpr function may be evaluated at either compile-time or runtime.
- To be eligible for compile-time execution, all arguments must be constant expressions.
- A constexpr function must evaluate at compile-time when the constant expression it is part of must evaluate at compile time.
*/

#include <iostream>

// The return value of a non-constexpr function is not a constant expression
int five()
{
    return 5;
}

int max(int x, int y) // this is a non-constexpr function
{
    if (x > y)
        return x;
    else
        return y;
}

constexpr int cmax(int x, int y) // this is a constexpr function
{
    if (x > y)
        return x;
    else
        return y;
}

int main()
{
    constexpr double gravity { 9.8 }; // ok: 9.8 is a constant expression
    constexpr int sum { 4 + 5 };      // ok: 4 + 5 is a constant expression
    constexpr int something { sum };  // ok: sum is a constant expression

    std::cout << "Enter your age: ";
    int age{};
    std::cin >> age;

    constexpr int myAge { age };      // compile error: age is not a constant expression
    constexpr int f { five() };       // compile error: return value of five() is not a constant expression

    // constexpr works for variables with non-integral types
    constexpr double d { 1.2 }; // d can be used in constant expressions!

    int m1 { max(5, 6) };        // ok
    const int m2 { max(5, 6) };      // ok
    constexpr int m3 { max(5, 6) };  // compile error: max(5, 6) not a constant expression

    int m1 { cmax(5, 6) };       // ok: may evaluate at compile-time or runtime
    const int m2 { cmax(5, 6) };     // ok: may evaluate at compile-time or runtime
    constexpr int m3 { cmax(5, 6) }; // okay: must evaluate at compile-time

    return 0;
}

/* Constant as array length

- In many cases, it would be preferable to use a symbolic constant as an array length.
- In C, this can be done via a preprocessor macro, or via an enumerator, but not via a const variable.
- Variables was generally assumed to be known only at runtime, which made them ineligible to be used as array lengths.

- To solve this problem, the C++ language standard added an exemption so that 
  const integral types with a constant expression initializer are usable as array lengths:
const int arrLen = 5;
int arr[arrLen]; // ok: array of 5 ints

*/

/* References

- https://www.learncpp.com/cpp-tutorial/constexpr-variables/
*/