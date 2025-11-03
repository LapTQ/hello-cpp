/* Reminders

- unscoped enumerations will implicitly convert to a std::size_t.
- enum classes don’t have an implicit conversion to integral types.
*/

/*
- Because enumerators are implicitly constexpr, conversion of an enumerator to an unsigned integral type is not considered a narrowing conversion
=> we can use unscoped enumerators for indexing
*/

#include <vector>

namespace Students
{
    enum Names
    {
        kenny, // 0
        kyle, // 1
        stan, // 2
        butters, // 3
        cartman, // 4
        max_students // 5
    };
}

void func1()
{
    std::vector testScores { 78, 94, 66, 77, 14 };  // index is expected to have type std::size_t (unsigned)
    testScores[Students::stan] = 76; // enumerators are implicitly constexpr => conversion to std::size_t is not a narrowing conversion
}


/*
- However, if we define a non-constexpr variable of the enumeration type, we may get sign conversion 
  warnings on any platform that defaults unscoped enumerations to a signed type.
  This is because the underlying type of an unscoped enumeration is implementation defined 
  (and thus, could be either a signed or unsigned integral type)
*/

void func2()
{
    std::vector testScores { 78, 94, 66, 77, 14 };
    Students::Names name { Students::stan }; // non-constexpr
    testScores[name] = 76; // may trigger a sign conversion warning if Student::Names defaults to a signed underlying type
}


/*
- We can also use enum classes too index an array.
- However, because enum classes don’t have an implicit conversion to integral types, we need to do one of the following:
    + static_cast the enumerator to an integer
    + use the helper function like the below example:
*/

#include <iostream>
#include <type_traits> // for std::underlying_type_t

enum class StudentNames2
{
    kenny, // 0
    kyle, // 1
    stan, // 2
    butters, // 3
    cartman, // 4
    max_students // 5
};

// Overload the unary + operator to convert StudentNames to the underlying type
constexpr auto operator+(StudentNames2 a) noexcept
{
    return static_cast<std::underlying_type_t<StudentNames2>>(a);
}

void func3()
{
    std::vector<int> testScores2(+StudentNames2::max_students);
    testScores2[+StudentNames2::stan] = 76;
    std::cout << "The class has " << +StudentNames2::max_students << " students\n";
}


int main()
{
    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/array-indexing-and-length-using-enumerators/
*/