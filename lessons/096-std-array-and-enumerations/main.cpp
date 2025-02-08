/* Using static assert to ensure the proper number of array initializers

- That way, if you add a new enumerator later but forget to add a 
  corresponding initializer to testScores, the program will fail to compile.
*/

#include <array>
#include <iostream>
#include <string_view>

namespace Color
{
    enum Type
    {
        black,
        red,
        blue,
        max_colors
    };

    using namespace std::string_view_literals; // for sv suffix
    constexpr std::array colorName { "black"sv, "red"sv, "blue"sv };

    // Make sure we've defined strings for all our colors
    static_assert(std::size(colorName) == max_colors);
};


/* References

- https://www.learncpp.com/cpp-tutorial/stdarray-and-enumerations/
*/