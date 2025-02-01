/* unscoped enumerations are not safe

... and in some cases will allow you to do things that don’t make sense
*/


/* Scoped enumerations (enum classes)

- Scoped enumerations work similarly to unscoped enumerations,
  but have two primary differences:
    + They won’t implicitly convert to integers.
    + the enumerators are only placed into the scope region of the enumeration.
=> Favor scoped enumerations over unscoped enumerations.

- Although scoped enumerations use the class keyword, they aren’t considered to be a “class type”.
*/


/* explicitly convert a scoped enumerator to/from an integer

- using a static_cast
- (C++17) use list initialization with integral value without a cast
*/


/* Convert scoped enumeration to integer (a hack)

- a useful hack is to overload the unary operator+
*/

#include <type_traits> // for std::underlying_type_t

enum class Animals
{
    chicken, // 0
    dog, // 1
};

constexpr auto operator+(Animals a) noexcept
{
    return static_cast<std::underlying_type_t<Animals>>(a);
}


/* using enum statements (C++20)

- Introduced in C++20, a using enum statement imports all of the enumerators 
  from an enum into the current scope.
*/

#include <string_view>

constexpr std::string_view getAnimal(Animals animal)
{
    using enum Animals; // bring all Animals enumerators into current scope (C++20)

    switch (animal)
    {
    case chicken: return "chicken";  // no need to qualify with Animals::
    case dog:     return "dog";
    default:    return "???";
    }
}

#include <iostream>

int main()
{   
    // unscoped enumerations are not safe
    enum Color
    {
        red,
    };
    enum Fruit
    {
        banana,
    };
    Color color { red };
    Fruit fruit { banana };
    std::cout << std::boolalpha << (color == fruit) << '\n'; // true, compare as integers


    // Scoped enumerations (enum classes)
    enum class Color2
    {
        red,
        blue,
    };

    enum class Fruit2
    {
        banana,
        apple,
    };

    Color2 color2 { Color2::red };
    Fruit2 fruit2 { Fruit2::banana };
    // std::cout << color2 << '\n'; // compile error, std::cout doesn't know how to print
    // std::cout << (color2 == fruit2) << '\n'; // compile error, can't compare different types
    std::cout << (color2 == Color2::red) << '\n'; // true, can compare same types


    // explicitly convert a scoped enumerator to/from an integer
    std::cout << static_cast<int>(color2) << '\n'; // 0, convert to integer
    Fruit2 fruit3 {  static_cast<Fruit2>(1) }; // apple, convert from integer
    Fruit2 fruit4 { 1 }; // apple, convert from integer (C++17)


    // Convert scoped enumeration to integer (a hack)
    std::cout << +Animals::dog << '\n'; // 1

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/scoped-enumerations-enum-classes/
*/