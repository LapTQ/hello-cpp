/* Enumerations (or enumerated type, or enum)

- ... whose values are restricted to a set of named symbolic constants (called enumerators).

- C++ supports two kinds of enumerations: 
    + unscoped enumerations
    + scoped enumerations
*/

/* Unscoped enumerations

- Enumerators are implicitly constexpr.
- Its enumerators are in the same scope as the enumeration itself.
- an enumerator name can’t be used in multiple enumerations within the same scope.
- enumerations are small and inexpensive to copy, it is fine to pass (and return) them by value.
*/

#include <iostream>

enum Color
{
    red,
    green,
    blue,

    // these enumerators are in the same scope as the enumeration itself
};
// defined in global scope, so its enumerators are in the global scope

void func1()
{
    Color apple { red };
    Color shirt { Color::green }; // okay, using with scope resolution operator, but not necessary
    std::cout << std::boolalpha << (apple == red) << '\n'; // true
}


/* Avoiding enumerator naming collisions

Solution 1: Use a prefix for each enumerator name
    For example: red -> color_red

    However, this still pollutes the namespace

Solution 2: (Better) put the enumerated type inside a namespace (below)

Alternatively, if an enumeration is only used within the body of a single function, 
the enumeration should be defined inside the function.
*/

namespace Color2
{
    // The names Color, red, blue, and green are defined inside namespace Color
    enum Color2
    {
        red,
        green,
        blue,
    };
}

namespace State
{
    enum State
    {
        green,  // does not collide with Color2::green
        fine,
    };
}

void func2()
{
    Color2::Color2 apple2 { Color2::red };
}


/* Unscoped enumerator integral conversions

- When we define an enumeration, each enumerator is automatically associated with an integer value based on its position. 
- By default, the first enumerator is given the integral value 0, and each subsequent enumerator 
  has a value one greater than the previous enumerator.
- It is possible to explicitly define the value of enumerators, but you should avoid doing so unless you have a good reason.
- Unscoped enumerations will implicitly convert to integral values.
  Even though enumerations store integral values, they are not considered 
  to be an integral type (they are a compound type).
*/

enum Animal
{
    cat = -3,    // values can be negative
    dog,         // -2
    pig,         // -1
    horse = 5,
    giraffe = 5, // shares same value as horse
    chicken,     // 6
};
// no enumerator with value 0 in this list

void func3()
{
    std::cout << red << green << blue << '\n'; // 012
}


/* Value-initializing an enumeration

- If an enumeration is zero-initialized, the enumeration will be given value 0, 
  even if there is no corresponding enumerator with that value.

- This has two semantic consequences:
    + If there is an enumerator with value 0, value-initialization will default the enumeration 
      to the meaning of that enumerator. => the enumerator with value 0 should best represent the default value.
      For example:
        ```
        enum UniverseResult
        {
            destroyUniverse, // default value (0)
            saveUniverse
        };
        ```
    + If there is no enumerator with value 0, value-initialization will create a semantically invalid enumeration.
      We recommend adding an "invalid" or "unknown" enumerator with value 0.
        For example:
        ```
        enum Animal
        {
            unknown = 0, // default value (0)
            cat,
            dog,
        };
        ```
*/

void func4()
{
    Animal a {}; // a is initialized to 0
    std::cout << a << '\n'; // 0
}


/* Enumeration size and underlying type (base)

- the C++ standard does not specify which specific integral type should be used as the underlying type.
- Most compilers will use int as the underlying type.
- It is possible to explicitly specify an underlying type for an enumeration. 
  The underlying type must be an integral type.
  => useful if you are working in some bandwidth-sensitive context.
*/

#include <cstdint>
enum Foo : std::int8_t
{
    goo,
    boo,
    moo,
};


/* Integer to unscoped enumerator conversion

- The compiler will not implicitly convert an integer to an unscoped enumeration.
- There are two ways:
    + using static_cast
    + (C++17) using list initialization if an unscoped enumeration has an explicitly specified base.
*/

void func5()
{
    Animal a1 { -3 };       // error: 2 is not an enumerator of Animal
    Animal a2 { static_cast<Animal>(-3) }; // okay
    std::cout << (a2 == cat) << '\n'; // true
    Foo f { 2 };
    std::cout << (f == moo) << '\n'; // true
}


/* Converting an enumeration to a string

- Solution 1: Use a switch statement
    => having to remember the name of the function, also clutters the code
- Solution 2: Overloading the << operator
    Similar to function overloading, C++ also supports operator overloading.
    (We'll cover operator overloading in much more detail in a future lesson)
- Solution 3: Map enumerators to strings using an array (future lesson)
*/

// Solution 1: Use a switch statement
#include <string_view>
constexpr std::string_view getColorName(Color color)
{
    switch (color)
    {
    case red:   return "red";
    case green: return "green";
    case blue:  return "blue";
    default:    return "???";
    }
}

// Solution 2: Overloading the << operator
std::ostream& operator<<(std::ostream& out, Color color)
{
    out << getColorName(color);
    return out;                 // operator<< conventionally returns its left operand
}

void func6()
{
    std::cout << getColorName(red) << '\n'; // solution 1, red
    std::cout << red << '\n'; // solution 2, red
}


/* Getting an enumeration from a string

- Solution 1: Input an integer, then use static_cast.
  => awkward
- Solution 2: Input a string, and use a series of if-statements.
- Solution 3: Overload the >> operator
*/

// Solution 2: Input a string, and use a series of if-statements
#include <optional>
constexpr std::optional<Color> getColorFromString(std::string_view sv)
{
    if (sv == "red")   return red;
    if (sv == "green") return green;
    if (sv == "blue")  return blue;
    
    return {};
}

#include <algorithm> // for std::transform
#include <cctype>    // for std::tolower
#include <iterator>  // for std::back_inserter
#include <string>
#include <limits>
std::string toASCIILowerCase(std::string_view sv)
{
    std::string lower{};
    std::transform(sv.begin(), sv.end(), std::back_inserter(lower),
        [](char c)
        {
            return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        });
    return lower;
}

// Solution 3: Overload the >> operator
std::istream& operator>>(std::istream& in, Color& color)
{
    std::string s{};
    in >> s;

    std::optional<Color> match { getColorFromString(toASCIILowerCase(s)) };
    if (match)
    {
        color = *match; // dereference std::optional
        return in;
    }

    // set input stream to fail state
    in.setstate(std::ios_base::failbit);

    // On an extraction failure, operator>> zero-initializes fundamental types
    color = {};

    return in;
}

void func7()
{
    std::string colorName {};
    
    // solution 2
    std::cout << "Enter a color name: ";
    std::cin >> colorName;
    std::optional<Color> color { getColorFromString(toASCIILowerCase(colorName)) };
    if (color.has_value())
        std::cout << *color << '\n';
    else
        std::cout << "Unknown color\n";
    

    // solution 3: Overload the >> operator
    std::cout << "Enter a color name: ";
    Color color2 {};
    std::cin >> color2;
    if (std::cin)
        std::cout << color2 << '\n';
    else
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Unknown color\n";
    }
}


int main()
{
    // Unscoped enumerations
    func1();


    // put the enumerated type inside a namespace
    func2();


    // Value-initializing an enumeration
    func4();


    // Integer to unscoped enumerator conversion
    func5();
    

    // Converting an enumeration to a string
    func6();


    // Getting an enumeration from a string
    func7();
    

    return 0;
}


/* how operator<< works

Consider a simple expression like std::cout << 5. 
- std::cout has type std::ostream (a user-defined type)
- 5 is a literal of type int.
*/

/* References

- https://www.learncpp.com/cpp-tutorial/unscoped-enumerations/
- https://www.learncpp.com/cpp-tutorial/unscoped-enumerator-integral-conversions/
- https://www.learncpp.com/cpp-tutorial/converting-an-enumeration-to-and-from-a-string/
- https://www.learncpp.com/cpp-tutorial/introduction-to-overloading-the-i-o-operators/
*/