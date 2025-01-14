#include <iostream>

int main() {
    bool b1 { true };
    bool b2 { false };

    bool b3 {}; // default value is false

    std::cout << b1 << '\n'; // 1
    std::cout << !b2 << '\n'; // 1
    std::cout << b3 << '\n'; // 0

    std::cout << std::boolalpha; // print bools as true or false
    std::cout << b1 << '\n'; // true
    std::cout << std::noboolalpha; // turn off boolalpha

    std::cout << "Enter a boolean value: ";
    std::cin >> b1; // 0 is false, 1 is true
    std::cout << b1 << '\n';

    std::cout << "Enter a boolean value: ";
    std::cin >> std::boolalpha;
	std::cin >> b1; // false or true, case insensitive (so True, FALSE will not work)
    std::cout << b1 << '\n';
    // However, when std::boolalpha is enabled for input, numeric values will no longer be accepted 

    if ("true")
        std::cout << "5 == 6 => " << (5 == 6) << '\n'; // 0

    return 0;
}

/*
- Boolean values are not actually stored in as the words “true” or “false”. 
- They are stored as integral values: true is stored as integer 1, and false is stored as integer 0. 
- Similarly, when Boolean values are evaluated, they evaluate to the integers 0 (false) or 1 (true).
*/

/* Inputting Boolean values

- By default, std::cin only accepts numeric input for Boolean variables: 0 is false, and 1 is true.
- Any other numeric value will be interpreted as true, and will cause std::cin to enter failure mode. 
- Any non-numeric value will be interpreted as false and will cause std::cin to enter failure mode.

- To allow std::cin to accept the words false and true as inputs, you must first input to std::boolalpha.
*/


/* References

- https://www.learncpp.com/cpp-tutorial/boolean-values/

*/