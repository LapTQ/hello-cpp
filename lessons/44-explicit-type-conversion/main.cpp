

/*

- C++ supports 5 different types of casts: C-style casts, static casts, const casts, dynamic casts, and reinterpret casts.

- C-style casts, although appears to be a single cast, it can actually perform any of the other casts depending on the context.
  => should be avoided.
- static_cast should be used to cast most values.
- Avoid const casts and reinterpret casts unless you have a very good reason to use them.
*/

#include <iostream>

int main()
{
    double d = 10 / 4; // does integer division, initializes d with value 2.0
    std::cout << d << '\n';

    // replacing one or both of the integer literals with double literals
    double d2 = 10.0 / 4.0; // does floating point division, initializes d2 with value 2.5
    std::cout << d2 << '\n';

    int x { 10 };
    int y { 4 };
    double d3 = x / y; // does integer division, initializes d with value 2.0
    std::cout << d3 << '\n';

    // C-style cast
    d3 = (double)x / y;
    std::cout << d3 << '\n';
    // C++ also supports a function-style cast_, which is a C-style cast that uses a more function-call:
    d3 = double(x) / y;
    std::cout << d3 << '\n';

    // static_cast
    d3 = static_cast<double>(x) / y;
    std::cout << d3 << '\n';

    return 0;
}

/* References

- https://www.learncpp.com/cpp-tutorial/explicit-type-conversion-casting-and-static-cast/
*/