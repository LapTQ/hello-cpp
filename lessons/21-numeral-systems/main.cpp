/*
- Octal: base 8
- Hexadecimal: base 16.
*/

#include <bitset> // for std::bitset
#include <iostream>

int main()
{
    std::cout << 012 << '\n'; // 0 before the number means this is octal
    std::cout << 0xF << '\n'; // 0x before the number means this is hexadecimal

    // Using hexadecimal to represent binary
    // Prior to C++14, there is no support for binary literals. However, hexadecimal literals provide us with a useful workaround (that you may still see in existing code bases):
    int bin{};    // assume 16-bit ints
    bin = 0x0001; // assign binary 0000 0000 0000 0001 to the variable
    bin = 0x0002; // assign binary 0000 0000 0000 0010 to the variable
    bin = 0x0004; // assign binary 0000 0000 0000 0100 to the variable
    bin = 0x0008; // assign binary 0000 0000 0000 1000 to the variable
    bin = 0x0010; // assign binary 0000 0000 0001 0000 to the variable
    bin = 0x0020; // assign binary 0000 0000 0010 0000 to the variable
    bin = 0x0040; // assign binary 0000 0000 0100 0000 to the variable
    bin = 0x0080; // assign binary 0000 0000 1000 0000 to the variable
    bin = 0x00FF; // assign binary 0000 0000 1111 1111 to the variable
    bin = 0x00B3; // assign binary 0000 0000 1011 0011 to the variable
    bin = 0xF770; // assign binary 1111 0111 0111 0000 to the variable
    // In C++14 onward, we can use binary literals by using the 0b prefix:
    bin = 0b11;       // assign binary 0000 0000 0000 0011 to the variable

    // Digit separators
    bin = 0b1011'0010;
    long value { 2'132'673'462 };
    // Digit separators are purely visual and do not impact the literal value in any way.

    // By default, C++ outputs values in decimal.
    // you can change the output format via use of the std::dec, std::oct, and std::hex
    int x { 12 };
    std::cout << x << '\n'; // decimal (by default)
    std::cout << std::hex << x << '\n'; // hexadecimal
    
    // Outputting values in binary is a little harder:
    // std::bitset<8> means we want to store 8 bits
	std::bitset<8> bin1{ 28 }; // binary literal for binary 1100 0101
    std::cout << bin1 << '\n'; // will output 00011100
    std::cout << std::bitset<4>{ 0b1010 } << '\n'; // create a temporary std::bitset and print it

    return 0;
}

/* Outputting values in binary using the Format / Print Library

In C++20 and C++23, we have better options for printing binary via the new Format Library (C++20) and Print Library (C++23):

#include <format> // C++20
#include <iostream>
#include <print> // C++23

int main()
{
    std::cout << std::format("{:b}\n", 0b1010);  // C++20, {:b} formats the argument as binary digits
    std::cout << std::format("{:#b}\n", 0b1010); // C++20, {:#b} formats the argument as 0b-prefixed binary digits

    std::println("{:b} {:#b}", 0b1010, 0b1010);  // C++23, format/print two arguments (same as above) and a newline

    return 0;
}
*/

/* References

- https://www.learncpp.com/cpp-tutorial/numeral-systems-decimal-binary-hexadecimal-and-octal/
*/