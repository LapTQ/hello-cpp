

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


/* Solution 1: use signed integral type for index

There are questions to answer:
- What signed type should we use?
- Converting the signed loop variable to an unsigned index
*/


/* What signed type should we use?

- Unless you are working with a very large array, using int should be fine.
- If you are dealing with very large arrays, you can use the strangely named std::ptrdiff_t. 
  This typedef is often used as the signed counterpart to std::size_t.
- (C++20) íntroduces std::ssize(), as it returns a signed integral type.
*/

template <typename T>
void printReverse2(const std::vector<T>& arr)
{
    int length{ static_cast<int>(arr.size()) }; // cast to int
    for (int index{ length - 1}; index >= 0; --index) // index is signed
    {
        std::cout << arr[static_cast<std::size_t>(index)] << ' ';   // cast to std::size_t
    }

    std::cout << '\n';
}


using Index = std::ptrdiff_t;
template <typename T>
void printReverse3(const std::vector<T>& arr)
{
    auto length{ static_cast<Index>(arr.size()) }; // cast to Index
    for (auto index{ length - 1}; index >= 0; --index) // index is signed
    {
        std::cout << arr[static_cast<std::size_t>(index)] << ' ';   // cast to std::size_t
    }

    std::cout << '\n';
}

// C++20
template <typename T>
void printReverse4(const std::vector<T>& arr)
{
    auto length{ std::ssize(arr) }; // cast to Index
    for (auto index{ length - 1 }; index >= 0; --index) // index is signed
    {
        std::cout << arr[static_cast<std::size_t>(index)] << ' ';   // cast to std::size_t
    }

    std::cout << '\n';
}


/* Converting the signed loop variable to an unsigned index

There are different ways:
- static_cast every time you use the index => hard to read
- Use a conversion function with a short name
- Use a custom view.
    Similar to std::string_view is a view into a string.
*/

/* Use a conversion function with a short name
*/

template <typename T>
constexpr std::size_t toUZ(T value)
{
    // make sure T is an integral type
    static_assert(std::is_integral<T>() || std::is_enum<T>());

    return static_cast<std::size_t>(value);
}

template <typename T>
void printReverse5(const std::vector<T>& arr)
{
    auto length { static_cast<Index>(arr.size()) };
    for (auto index{ length - 1 }; index >= 0; --index) // index is signed
    {
        std::cout << arr[toUZ(index)] << ' ';
    }

    std::cout << '\n';
}

/* Use a custom view

- We'll use overloading to implement operator[] 
*/

#include "SignedArrayView.h"

template <typename T>
void printReverse6(const std::vector<T>& arr)
{
    SignedArrayView sarr{ arr };
    auto length { sarr.ssize() };
    for (auto index{ length - 1 }; index >= 0; --index) // index is signed
    {
        std::cout << sarr[index] << ' ';
    }

    std::cout << '\n';
}


/* Solution 2: Index the underlying C-style array instead

(Discussed in lessons/086-std-vector/main.cpp)
We believe that this method is the best of the indexing options.
*/

template <typename T>
void printReverse7(const std::vector<T>& arr)
{
    auto length { static_cast<Index>(arr.size()) };
    for (auto index{ length - 1 }; index >= 0; --index) // index is signed
    {
        std::cout << arr.data()[index] << ' ';
    }

    std::cout << '\n';
}


int main()
{
    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/arrays-and-loops/
- https://www.learncpp.com/cpp-tutorial/arrays-loops-and-sign-challenge-solutions/
*/