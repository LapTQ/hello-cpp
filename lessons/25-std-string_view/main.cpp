/* std::string_view (C++17)

- To address the issue with std::string being expensive to initialize (or copy), C++17 introduced std::string_view
- std::string_view provides read-only access to an existing string 
  (a C-style string, a std::string, or another std::string_view) without making a copy.
*/

#include <iostream>
#include <string>
#include <string_view> // C++17

void printString(std::string str) // str makes a copy of its initializer
{
    std::cout << str << '\n';
}

// str provides read-only access to whatever argument is passed in
void printSV(std::string_view str) // now a std::string_view
{
    std::cout << str << '\n';
}

int main()
{
    [[maybe_unused]] int x { 5 }; // x makes a copy of its initializer, fast
    std::string s{ "Hello, world!" }; // s makes a copy of its initializer, slow

    std::string_view s2{ "Hello, world!" };
    // s provides read-only access to “Hello, world!” without making a copy of the string.
    printSV(s2);

    // Both a C-style string and a std::string will implicitly convert to a std::string_view
    printSV(s);

    // std::string_view will not implicitly convert to std::string
    printString(s2); // error
    std::string_view sv{ "Hello, world!" };
    std::string s{ sv }; // okay: we can create std::string using std::string_view initializer
	printString(s);      // and call the function with the std::string
	printString(static_cast<std::string>(sv)); // okay: we can explicitly cast a std::string_view to a std::string

    // Literals for std::string_view
    using namespace std::string_view_literals; // access the sv suffix
    std::cout << "moo\n"sv; // sv suffix is a std::string_view literal

    constexpr std::string_view s{ "Hello, world!" }; // s is a string symbolic constant
    std::cout << s << '\n'; // s will be replaced with "Hello, world!" at compile-time

    return 0;
}

/* std::string_view will not implicitly convert to std::string

- if this is desired, we have two options:
  ++ create a std::string with a std::string_view initializer
  ++ explicitly cast the std::string_view to a std::string
*/

/* Unlike std::string, std::string_view has full support for constexpr:
*/


/* References

- https://www.learncpp.com/cpp-tutorial/introduction-to-stdstring_view/
*/