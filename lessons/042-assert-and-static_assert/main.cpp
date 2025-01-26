/*
- when assertion fails, the program will terminate via std::abort().
*/

/* NDEBUG

- The assert macro comes with a small performance cost.
- Furthermore, asserts should (ideally) never be encountered in production code (because your code should already be thoroughly tested).

- C++ comes with a built-in way to turn off asserts in production code: 
  if the preprocessor macro NDEBUG is defined, the assert macro gets disabled.
*/

/* static_assert

- A static_assert is an assertion that is checked at compile-time rather than at runtime.
  => the condition must be a constant expression.
- Because the compiler does the evaluation, there is no runtime cost to a static_assert 
  => Favor static_assert over assert() whenever possible.

- Unlike assert, which is declared in the <cassert> header, static_assert is a keyword, 
  so no header needs to be included to use it.
*/

#undef NDEBUG // enable asserts (must be placed before any #includes)

#include <cassert> // for assert()
#include <iostream>


int main()
{
    double x{ 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 };
    double y{ 1.0 };

    assert((x == y) && "Oops, x does not equal y");
    // A string literal always evaluates to Boolean true. So if found is false, false && true is false

    static_assert(sizeof(int) >= 4, "integers are too small on this system");

    return 0;
}

/* References

- https://www.learncpp.com/cpp-tutorial/assert-and-static_assert/
*/