

#include <iostream>
int main()
{
    double b { 5.0 }; // no suffix means double type by default
    float c { 5.0f }; // f suffix means float type
}


/* C++ floating point types
- float is almost always implemented using the 4-byte IEEE 754 single-precision format.
double is almost always implemented using the 8-byte IEEE 754 double-precision format.
- long double is a strange type. On different platforms, its size can vary between 8 and 16 bytes, 
  and it may or may not use an IEEE 754 compliant format. 
  We recommend avoiding long double.

- by default, floating point literals default to type double. An f suffix is used to denote a literal of type float.
*/

/* References

- https://www.learncpp.com/cpp-tutorial/floating-point-numbers/
*/