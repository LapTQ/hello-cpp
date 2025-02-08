/* std::find 

- searches for the first occurrence of a value in a container.

- See: https://en.cppreference.com/w/cpp/algorithm/find
*/

/* std::find_if 
*/

#include <string_view>

bool containsNut(std::string_view str)
{
    return str.find("nut") != std::string_view::npos;
}


/* std::count and std::count_if
*/


/* std::sort
*/


/* std::for_each
*/

void doubleNumber(int& i)
{
    i *= 2;
}


#include <algorithm>
#include <array>
#include <iostream>

int main()
{
    std::array arr{ 13, 90, 99, 5, 40, 80 };


    // std::find
    int search{ 5 };
    int replace{ 234 };
    auto found{ std::find(arr.begin(), arr.end(), search) };
    if (found == arr.end())
    {
        std::cout << "Could not find " << search << '\n';
    }
    else
    {
        // Override the found element.
        *found = replace;
    }


    // std::find_if
    std::array<std::string_view, 4> arr2{ "apple", "banana", "walnut", "lemon" };
    auto found2{ std::find_if(arr2.begin(), arr2.end(), containsNut) };
    if (found2 == arr2.end())
    {
        std::cout << "No nuts\n";
    }
    else
    {
        std::cout << "Found " << *found2 << '\n';
    }


    // std::count and std::count_if
    auto nuts{ std::count_if(arr2.begin(), arr2.end(), containsNut) };
	std::cout << "Counted " << nuts << " nut(s)\n";


    // std::for_each
    std::for_each(std::next(arr.begin()), arr.end(), doubleNumber);  // skip elements at the beginning

    return 0;
}

/* References

- https://www.learncpp.com/cpp-tutorial/introduction-to-standard-library-algorithms/
*/