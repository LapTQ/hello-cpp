

/* 
Problematic code:
- std::size_t is unsigned integral type, so when we decrement index when it has value 0, it will wrap around to a large positive value.
  => undefined behavior, or crash.
*/

#include <iostream>
#include <vector>

template <typename T>
void printReverse(const std::vector<T>& arr)
{
    for (std::size_t index{ arr.size() - 1 }; index >= 0; --index) // index is unsigned
    {
        std::cout << arr[index] << ' ';
    }

    std::cout << '\n';
}


/* Solution 1: use static_cast

=> hard to read
*/

template <typename T>
void printReverse2(const std::vector<T>& arr)
{
    for (int index{ static_cast<int>(arr.size()) - 1}; index >= 0; --index) // index is signed
    {
        std::cout << arr[static_cast<std::size_t>(index)] << ' ';   // cast to std::size_t
    }

    std::cout << '\n';
}


/* 
- Unless you are working with a very large array, using int should be fine.
- If you are dealing with very large arrays, you can use the strangely named std::ptrdiff_t. 
  This typedef is often used as the signed counterpart to std::size_t.
- (C++20) use std::ssize(), as it returns a signed integral type.
*/

using Index = std::ptrdiff_t;
template <typename T>
void printReverse3(const std::vector<T>& arr)
{
    for (auto index{ static_cast<Index>(arr.size()) - 1}; index >= 0; --index) // index is signed
    {
        std::cout << arr[static_cast<std::size_t>(index)] << ' ';   // cast to std::size_t
    }

    std::cout << '\n';
}

template <typename T>
void printReverse4(const std::vector<T>& arr)
{
    for (auto index{ std::ssize(arr) - 1 }; index >= 0; --index) // index is signed
    {
        std::cout << arr[static_cast<std::size_t>(index)] << ' ';   // cast to std::size_t
    }

    std::cout << '\n';
}



int main()
{
    std::vector<int> arr{ 4, 6, 7, 3, 8, 2, 1, 9 };

    printReverse3(arr);

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/arrays-and-loops/
- https://www.learncpp.com/cpp-tutorial/arrays-loops-and-sign-challenge-solutions/
*/