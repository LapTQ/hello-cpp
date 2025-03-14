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

std::string getName()
{
    std::string s { "Alex" };
    return s;
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
    // printString(s2); // error
    std::string_view sv{ "Hello, world!" };
    std::string s3{ sv }; // okay: we can create std::string using std::string_view initializer
    printString(s3);      // and call the function with the std::string
    printString(static_cast<std::string>(sv)); // okay: we can explicitly cast a std::string_view to a std::string

    // Literals for std::string_view
    using namespace std::string_view_literals; // access the sv suffix
    std::cout << "moo\n"sv; // sv suffix is a std::string_view literal

    // std::string_view has full support for constexpr
    constexpr std::string_view s4{ "Hello, world!" };
    std::cout << s4 << '\n'; // s4 will be replaced with "Hello, world!" at compile-time

    // View modification functions
    std::string_view str{ "Peach" };
    std::cout << str << '\n';
    str.remove_prefix(2);
    std::cout << str << '\n'; // prints "ach"
    str.remove_suffix(1);
    std::cout << str << '\n'; // prints "ac"
    // the only way to reset the view is by reassigning the source string to it again:
    str = "Peach";

    return 0;
}

/* std::string_view will not implicitly convert to std::string

- if this is desired, we have two options:
  ++ create a std::string with a std::string_view initializer
  ++ explicitly cast the std::string_view to a std::string
*/

/* Unlike std::string, std::string_view has full support for constexpr:
*/

/* std::string is a (sole) owner, std::string_view is a viewer

- You might be wondering why std::string makes an expensive copy of its initializer?
  Imagine the initialization process as a function call that initializes the object.
  When the initialization statement is complete, one of two things will typically happen:
  ++ If the initializer was a temporary, that temporary will be destroyed immediately.
  ++ If the initializer was a variable, the caller still has access to that object. 
     The caller can then do whatever it wants with the object, including modify or destroy it.

- std::string_view remains dependent on the initializer through its lifetime. 
  If the string being viewed is modified or destroyed, unexpected or undefined behavior will result.
- Do not initialize a std::string_view with a std::string literal.
  ```
  std::string_view name { "Alex"s }; // "Alex"s creates a temporary std::string
  std::cout << name << '\n'; // undefined behavior
  ```
- If the std::string reallocates memory in order to accommodate the new string data, it will return the old memory to the OS.
  => the std::string_view is pointing to a now-invalid object.
- It is okay to initialize a std::string_view with a C-style string literal or a std::string_view literal.
- Be careful returning a std::string_view. Because std::string_view is viewing a local variable, which will be destroyed.

- std::string_view is best used as a read-only function parameter.
- 2 main cases where a std::string_view can be returned safely:
  ++ return C-style string "literals" from a function that has a return type of std::string_view.
        std::string_view getBoolName(bool b)
        {
            return "false";
        }
     because C-style string literals exist for the entire program.
  ++ return a function "parameter" of type std::string_view
        std::string_view firstAlphabetical(std::string_view s1, std::string_view s2)
        {
            if (s1 < s2)
                return s1;
            return s2;
        }
     There is one important subtlety here. If the argument is a temporary object 
     that will be destroyed at the end of the full expression containing the function call, 
     the std::string_view return value "must" be used in the "same" expression. 
*/

/* View modification functions

- does not modify the string being viewed in any way, just the view itself.
=>
  ++ std::string_view can view a substring
  ++ std::string_view may or may not be null-terminated
*/


/* References

- https://www.learncpp.com/cpp-tutorial/introduction-to-stdstring_view/
- https://www.learncpp.com/cpp-tutorial/stdstring_view-part-2/
*/