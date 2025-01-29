/* Introduction

- In the previous lessons, we discussed how to create function templates that use type template parameters. 
- A non-type template parameter is a template parameter with a fixed type that serves as a 
  placeholder for a constexpr value.
    For example:
    ```
    std::bitset<8> bits{ 0b0000'0101 }; // The <8> is a non-type template parameter
    ```
*/

#include <iostream>

template <int N> // declare a non-type template parameter of type int named N
void print()
{
    std::cout << N << '\n';
}

/* What are non-type template parameters useful for?

- For example, with `getSqrt` function below, though `getSqrt(-5.0)` will assert out at runtime,
  we prefer it to assert out at compile time.
- However, `static_assert` requires a constant expression,
  but as of C++20 function parameters cannot be constexpr.

Solution:
- change the function parameter to a non-type template parameter (see `getSqrt2`).

=> Use case:
- Non-type template parameters are used primarily when we need to pass constexpr values 
  to functions (or class types) so they can be used in contexts that require a constant expression.
*/

#undef NDEBUG // enable asserts
#include <cassert>
#include <cmath>

double getSqrt(double d)
{
    assert(d >= 0.0);

    if (d >= 0)
        return std::sqrt(d);

    return 0.0;
}

template <double D> // requires C++20 for floating point non-type parameters
double getSqrt2()
{
    static_assert(D >= 0.0);

    if constexpr (D >= 0)
        return std::sqrt(D); // strangely, std::sqrt isn't a constexpr function (until C++26)

    return 0.0;
}

/* (C++17) Type deduction for non-type template parameters using auto
*/

template <auto N>
void print2()
{
    std::cout << N << '\n';
}

int main()
{
    print<5>(); // prints 5

    std::cout << getSqrt(-5.0) << '\n'; // still compile
    std::cout << getSqrt2<-5.0>() << '\n'; // compile error

    // deduce non-type template parameter type using auto
    print2<'c'>(); // prints 'c' rather than 99 

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/non-type-template-parameters/
*/