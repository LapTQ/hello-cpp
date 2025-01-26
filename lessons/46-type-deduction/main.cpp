/* Type deduction

- In C++, we are required to provide an explicit type for all objects:
double d{ 5.0 };

but the literal value 5.0 used to initialize d also has type double.

- type deduction can be invoked by using the `auto` keyword.
- Type deduction drops const/constexpr from the deduced type
*/

/* Type deduction for functions

- Functions that use an auto return type must be fully defined 
  before they can be used (a forward declaration is not sufficient).

*/

/* Trailing return type syntax

- The auto keyword can also be used to declare functions where
  the return type is specified after the rest of the function prototype:

- It helps making the function easier to read, especially when the
  return type is complex or when we want to align function's declaration vertically.
- It's also useful when the return type must be deduced based on the type of the function parameters:
    #include <type_traits> // note: decltype(x) evaluates to the type of x
    
    std::common_type_t<decltype(x), decltype(y)> add(int x, double y);         // Compile error: compiler hasn't seen definitions of x and y yet
    auto add(int x, double y) -> std::common_type_t<decltype(x), decltype(y)>; // ok
*/

#include <string>
#include <string_view>

int add(int x, int y)
{
    return x + y;
}

auto add2(int x, int y)
{
    return x + y;
}

auto foo();

// Trailing return type syntax
auto add3(int x, int y) -> int // equivalent to `int add(int x, int y)`
{
  return (x + y);
}

int main()
{
    auto d { 5.0 }; // 5.0 is a double literal, so d will be deduced as a double
    auto sum { add(5, 6) };
    constexpr auto c { 5u }; // c is a constexpr unsigned int

    // const dropped
    const int a { 5 };
    auto b { a };      // b has type int, not const int
    const auto e { a }; // if you want b to be const, you must explicitly specify it

    // for string literals
    auto s { "Hello, world" }; // s will be type const char*, not std::string
    using namespace std::string_literals;
    auto s1 { "goo"s };  // "goo"s is a std::string literal, so s1 will be deduced as a std::string
    using namespace std::string_view_literals;
    auto s2 { "moo"sv }; // "moo"sv is a std::string_view literal, so s2 will be deduced as a 


    foo(); // compile error

    return 0;
}

auto foo()
{
    return 5;
}

/* References

- https://www.learncpp.com/cpp-tutorial/type-deduction-for-objects-using-the-auto-keyword/
- https://www.learncpp.com/cpp-tutorial/type-deduction-for-functions/
*/