/* Reminders

- unscoped enumerations will implicitly convert to a std::size_t.
- enum classes don’t have an implicit conversion to integral types.
*/

/*
- Because enumerators are implicitly constexpr, conversion of an enumerator to an unsigned integral type is not considered a narrowing conversion
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


int main()
{
    std::vector testScores { 78, 94, 66, 77, 14 };
    Students::Names name { Students::stan }; // non-constexpr
    testScores[name] = 76; // may trigger a sign conversion warning if Student::Names defaults to a signed underlying type


    std::vector<int> testScores2(+StudentNames2::max_students);
    testScores2[+StudentNames2::stan] = 76;
    std::cout << "The class has " << +StudentNames2::max_students << " students\n";

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/array-indexing-and-length-using-enumerators/
*/