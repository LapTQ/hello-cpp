/* Defining C-style strings

- simply declare a C-style array variable of char
*/


/* Outputting a C-style string

- When outputting a C-style string, std::cout outputs characters until it encounters the null terminator.

the output streams (e.g. std::cout) make some assumptions about your intent:
+ If you pass it a non-char pointer, it will simply print the contents of that pointer.
+ if you pass it an object of type char* or const char*, it will assume you’re intending to print a string.
*/


/* Inputting C-style strings

- C-style strings are fixed-size arrays, we should declare an array larger than the maximum size of the string we expect to read.
- Prior to C++20, std::cin would extract as many charaters as possible (stopping at the first non-leading whitespace)
  => user's input might overflow the array.
- In C++20, operator>> was changes so that it only work for inputing non-decayed C-style strings.
  => allow operator>> to extract only as many characters as the C-style string length will allow.

See the recommended way to read C-style strings below.
*/


/* C-style strings don’t support assignment
*/


/* Getting the length of an C-style string

- std::size() or std::ssize() returns the actual length of the C-style array, not the length of the string.
  => use the strlen() function
- However, std::strlen() is slow, as it has to traverse through the whole array, 
  counting characters until it hits the null terminator.
*/


/* Avoid non-const C-style string objects 

- ... in favor of std::string.
*/


/* C-style string symbolic constants

- C++ supports two different ways to create C-style string symbolic constants:
```
const char name[] { "Alex" };     // case 1: const C-style string initialized with C-style string literal
const char* const color{ "Orange" };    // case 2: const pointer to C-style string literal
```
C++ deals with the memory allocation for these slightly differently.
- In case 1:
    + “Alex” is put into (probably read-only) memory somewhere. 
    + program allocates memory for a C-style array of length 5.
    + initializes that memory with the string “Alex”
    => end up with 2 copies of “Alex”.
- In case 2:
    + places the string “Orange” into read-only memory somewhere.
    + initializes the pointer with the address of the string.

- Favor std::string_view over C-style string symbolic constants
*/


/* Type deduction with const C-style strings
*/


#include <iostream>
#include <cstring> // for strlen()

int main()
{
    // Defining C-style strings
    char str1[8]{};                    // an array of 8 char, including hidden null-terminator character
    const char str2[]{ "string" };     // an array of 7 char, including hidden null-terminator character
    

    // Outputting a C-style string
    std::cout << str2 << '\n'; // string

    int narr[]{ 9, 7, 5, 3, 1 };
    std::cout << narr << '\n'; // 0x7ffeeb1b3b40

    char c{ 'Q' };
    std::cout << &c << '\n'; // undefined behavior


    // Inputting C-style strings
    char rolls[255] {}; // declare array large enough to hold 254 characters + null terminator
    std::cout << "Enter your rolls: ";
    std::cin >> rolls;
    std::cout << "You entered: " << rolls << '\n';

    // the recommended way to read C-style strings
    std::cout << "Enter your rolls: ";
    std::cin.getline(rolls, std::size(rolls));
    std::cout << "You entered: " << rolls << '\n';
    // cin.getline() will read up to 254 characters. Any excess characters will be discarded.


    // C-style strings don’t support assignment
    char str[]{ "string" }; // ok
    // str = "rope";           // not ok!
    str[1] = 'p';           // ok


    // Getting the length of an C-style string
    std::cout << strlen(str) << '\n'; // 6


    // Type deduction with const C-style strings
    auto s1{ "Alex" };  // type deduced as const char*
    auto* s2{ "Alex" }; // type deduced as const char*
    auto& s3{ "Alex" }; // type deduced as const char(&)[5]

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/c-style-strings/
- https://www.learncpp.com/cpp-tutorial/c-style-string-symbolic-constants/
*/