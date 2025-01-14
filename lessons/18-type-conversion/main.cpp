#include <iostream>

int main() {
    double d { 5 }; // implicit conversions, safe
    // int x { 5.5 }; // implicit conversions, unsafe, raises error due to brace initialization
    int x = 5.5; // implicit conversions, unsafe, raise warning

    std::cout << d << "\n";
    std::cout << x << "\n";

    int y { static_cast<int>(5.5) }; // explicit conversions, no warning
    std::cout << y << "\n";

    char ch {97};
    std::cout << static_cast<int>(ch) << "\n"; // 97, not 'a'
    // The variable ch itself is not affected by casting its value to a new type, it's still a char.

    std::int8_t myInt{65};
    std::cout << myInt << '\n'; // you're probably expecting this to print 65, but it prints 'A'
    // even worse:
    std::cout << "Enter a number between 0 and 127: ";
    std::cin >> myInt; // when we enter 35, we’re actually entering two chars, '3' and '5'
    std::cout << "You entered: " << static_cast<int>(myInt) << '\n'; // this will print 51 (~'3')

    return 0;
}

/* `std::int8_t` and `std::uint8_t` likely behave like `signed char` and `unsigned char` instead of integers

*/