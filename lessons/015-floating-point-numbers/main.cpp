
#include <iomanip> // for output manipulator std::setprecision()
#include <iostream>

int main()
{
    double b { 5.0 }; // no suffix means double type by default
    float c { 5.0f }; // f suffix means float type

    std::cout << 9.87654321f << '\n'; // truncating to 6 digits: 9.87654

    std::cout << std::setprecision(17); // show 17 digits of precision
    std::cout << 3.33333333333333333333333333333333333333f <<'\n'; // f suffix means float: 3.3333332538604736
    std::cout << 123456789.0f <<'\n'; // Precision issues don’t just impact fractional numbers, they impact any number with too many significant digits: 123456792
    // float values typically have 7 digits of precision

    // Rounding errors:
    std::cout << 1.0 << '\n';
    std::cout << 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 << '\n'; // 0.9999999999999999

    std::cout << -1/0.0 << '\n';
    std::cout << 0/0.0 << '\n';
}


/* C++ floating point types
- float is almost always implemented using the 4-byte IEEE 754 single-precision format.
double is almost always implemented using the 8-byte IEEE 754 double-precision format.
- long double is a strange type. On different platforms, its size can vary between 8 and 16 bytes, 
  and it may or may not use an IEEE 754 compliant format. 
  We recommend avoiding long double.

- by default, floating point literals default to type double. An f suffix is used to denote a literal of type float.
*/

/* Precision issues

- std::cout has a default precision of 6, it will truncate anything after that.
- We can override the default precision that std::cout shows by using the std::setprecision() manipulator.
- Precision issues don’t just impact fractional numbers, they impact any number with too many significant digits.
*/

/* NaN, Inf, signed zero

IEEE 754 compatible formats additionally support some special values:
- Inf: infinity
- NaN: not a number
- signed zero: -0.0 and 0.0

*/

/* References

- https://www.learncpp.com/cpp-tutorial/floating-point-numbers/
*/