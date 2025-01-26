/* Fundamental data types (or basic types, primitive types, built-in types)

- Surprisingly, the C++ standard does not define the exact size (in bits) of any of the fundamental types.
  Instead, the standard says the following:
  ++ An object must occupy at least 1 byte (so that each object has a distinct memory address).
  ++ A byte must be at least 8 bits.
  ++ The integral types char, short, int, long, and long long have a minimum size of 8, 16, 16, 32, and 64 bits respectively.
  ++ char and char8_t are exactly 1 byte.
*/

/* Fixed-width integers

- C++ only guarantees that integer variables will have a minimum size -- but they could be larger, depending on the target system.
  This can be a problem if you expect a variable to be 32-bit int but it’s actually 16-bit int.
- C++11 provides an alternate set of integer types that are guaranteed to be the same size on any architecture.
- The fixed-width integers are defined in the <cstdint>\ header.

WARNING: std::int8_t and std::uint8_t typically behave like chars
- Due to an oversight in the C++ specification, modern compilers typically treat 
  std::int8_t and std::uint8_t the same as signed char and unsigned char.
- For advanced readers:
  ++ The fixed-width integers actually don’t define new types -- they are just aliases for existing integral types.
  ++ For example, on a system where int is 16-bits (and long is 32-bits), std::int32_t will be an alias for long.
*/

#include <iomanip> // for std::setw (which sets the width of the subsequent output)
#include <iostream>
#include <climits> // for CHAR_BIT
#include <cstdint> // for fixed-width integers

int main()
{
    // display size
    std::cout << "A byte is " << CHAR_BIT << " bits\n\n";
    std::cout << std::left; // left justify output
    std::cout << std::setw(16) << "bool:" << sizeof(bool) << " bytes\n";

    // signed integers
    short s;      // prefer "short" instead of "short int"
    int i;
    long l;       // prefer "long" instead of "long int"
    long long ll; // prefer "long long" instead of "long long int"

    // unsigned integers
    unsigned short us;
    unsigned int ui;
    unsigned long ul;
    unsigned long long ull;

    // fixed-width integers
    std::int32_t x { 32767 }; // x is always a 32-bit integer
    std::cout << x << '\n';

    std::int8_t y { 65 };   // behave like chars
    std::cout << y << '\n'; // prints A

    std::cout << "least 16:  " << sizeof(std::int_least16_t)  * 8 << " bits\n";
    std::cout << "fast 16:  "  << sizeof(std::int_fast16_t)   * 8 << " bits\n";

    return 0;
}

/* Fundamental data type performance

- You might assume that types that use less memory would be faster than types that use more memory. 
  This is not always true. CPUs are often optimized to process data of a certain size (e.g. 32 bits), 
  and types that match that size may be processed quicker. On such a machine, a 32-bit int could be faster 
  than a 16-bit short or an 8-bit char.

- Fixed-width integers may be slower. You might want to use std::int32_t, but your CPU might be optimized for 64-bit int.
  However, it does not means your program will run slower: larger memory footprint may slow down your program more
  than the CPU’s optimization speeds it up.
*/

/* “integer” vs “integral”

- “integer”: most often used to refer to the int data type, but sometimes used to refer to the broader set including short, int, long, long long.
- “integral”: means “like an integer”, includes the broader set of types that are stored in memory as integers including bool, char. 

*/

/* Some attention:

- Overflow
- Integer division

*/

/* Should we avoid using unsigned types?

- Many developers (including Google) recommend avoiding unsigned types. Because:
  ++ with signed value, the max and min values are far from 0, but with unsigned value, the bottom is 0, which is close to where the majority of our values are.
  ++ (more insidiously) when you mix signed and unsigned integers in a mathematical expression, the signed integer is usually converted to unsigned. And the result is unsigned.

#include <iostream>

// assume int is 4 bytes
int main()
{
    signed int s { -1 };
    unsigned int u { 1 };

    if (s < u) // -1 is implicitly converted to 4294967295, and 4294967295 < 1 is false
        std::cout << "-1 is less than 1\n";
    else
        std::cout << "1 is less than -1\n"; // this statement executes

    return 0;
}

*/

/* Fast and least integral types

- To help address the above downsides of fixed-width integers, C++ defines alternative sets of integers that are guaranteed to exist:
++ std::int_fast#_t: e.g., std::int_fast32_t will give you the fastest (i.e., most quickly by the CPU) signed integer type that’s at least 32-bits.
++ std::int_least#_t: e.g., std::int_least32_t will give you the smallest (i.e., least memory) signed integer type that’s at least 32-bits.

*/

/* sizeof returns a value of type std::size_t

- We can infer that operator sizeof returns an integer value -- but what integral type is that return value?
- std::size_t is an alias for an implementation-defined unsigned integral type.
*/

/* Best practice

- Prefer `int` when the size of the integer doesn’t matter.

Avoid:
- `short`, `long`, fast/least integral types (prefer a fixed-width integer type instead).
- Unsigned types (prefer signed types instead).
- The 8-bit fixed-width integer types (prefer a 16-bit fixed-width integer type instead).
*/


/* References

- https://www.learncpp.com/cpp-tutorial/signed-integers/
- https://www.learncpp.com/cpp-tutorial/fixed-width-integers-and-size-t/
*/

