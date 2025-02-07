/* range-based for loop (also sometimes called a for-each loop) 

- ... allows traversal of a container without having to do explicit indexing
  => simpler, safer

- elements are copied to the loop variable => can be expensive for some types.
- the loop variable should have the same type as the array elements => prefer using `auto`
*/

#include <iostream>
#include <vector>

template <typename T>
void print(const std::vector<T>& arr)
{
    for (auto num : arr) // iterate over array arr and copy each value into `num`
    {
        std::cout << num << ' '; // print the current value of `num`
    }

    std::cout << '\n';
}


/* Avoid element copies using references

- If the reference is non-const, it can also be used to change the values in the array 
  (something not possible if our element_declaration is a copy of the value).
*/

template <typename T>
void print2(const std::vector<T>& arr)
{
    for (const auto& num : arr) // if non-const, the reference can change the values in the array
    {
        std::cout << num << ' '; // print the current value of `num`
    }

    std::cout << '\n';
}


/* Range-based for loops in reverse (C++20)
*/

#include <ranges> // C++20

template <typename T>
void print3(const std::vector<T>& arr)
{
    for (const auto& num : std::views::reverse(arr)) // if non-const, the reference can change the values in the array
    {
        std::cout << num << ' '; // print the current value of `num`
    }

    std::cout << '\n';
}


int main()
{
    // range-based for loop
    std::vector fibonacci { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };
    print(fibonacci);


    // Avoid element copies using references
    print2(fibonacci);


    // Range-based for loops in reverse (C++20)
    print3(fibonacci);

    return 0;
}


/*
- Range-based for loops work with a wide variety of array types, 
  including non-decayed C-style arrays, std::array, std::vector, linked list, trees, and maps. 
*/


/* References

- https://www.learncpp.com/cpp-tutorial/range-based-for-loops-for-each/
*/