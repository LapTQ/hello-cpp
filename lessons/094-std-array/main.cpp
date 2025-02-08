/* So why not use dynamic arrays for everything?

- std::vector is slightly less performant than the fixed-size arrays.
- std::vector only supports constexpr in very limited contexts.
    In modern C++, it is really this latter point that’s significant.

=> Use std::array for constexpr arrays, and std::vector for non-constexpr arrays.
*/


/* the length of a std::array "must" be a constant expression
*/


/* Aggregate initialization of a std::array

- std::array is an aggregate. To initialize it, we provide an initializer list.

- If a std::array is defined without an initializer, the elements will be default initialized.
  In most cases, this will result in elements being left uninitialized.
*/


/* Const and constexpr std::array

- Define your std::array as constexpr whenever possible. 
*/


/* std::array length and indexing

- ... similar to std::vector. But since only std::array has full support for constexpr, 
  we’ll focus a little more on that.

- Because the length of a std::array is constexpr, each of the `.size()`, `std::size()`, `.ssize()` (C++20) 
  will return the length as a constexpr value (even when called on a non-constexpr std::array object)!
*/


/* std::get() does compile-time bounds checking for constexpr indices

- operator[] does no bounds checking by definition, and the at() member function 
  only does runtime bounds checking (remind that function parameters can’t be constexpr).
- if our index is also a constexpr value, then the compiler should be able to 
  validate at compile-time => use the std::get() function template.
*/


/* pass std::array by (const) reference

- Note that the type of the non-type template parameter for std::array 
  should be std::size_t, not int! This is because std::array is defined as 
  `template<class T, std::size_t N> struct array;`. If you use int, 
  the compiler will be unable to match the argument.
*/

#include <array>  // for std::array
#include <vector> // for std::vector
#include <iostream> // for std::cout

void passByRef(const std::array<int, 5>& arr) // we must explicitly specify <int, 5> here
{
    std::cout << arr[0] << '\n';
}

template <typename T, std::size_t N> // note that this template parameter declaration matches the one for std::array
void passByRef2(const std::array<T, N>& arr)
{
    static_assert(N != 0); // fail if this is a zero-length std::array

    std::cout << arr[0] << '\n';
}


/* Returning a std::array

- Unlike std::vector, std::array is not move-capable, 
  so returning a std::array by value will make a copy of the array.
- We can alternatively return a std::array via an out parameter.
- Alternatively, consider returning a std::vector instead if you don't need constexpr,
  because std::vector is move-capable.
*/


int main()
{
    std::array<int, 5> arr {};  // a std::array of 5 ints
    std::vector<int> b(5);    // a std::vector of 5 ints (for comparison)


    // the length of a std::array "must" be a constant expression
    std::array<int, 7> arr2 {};  // using literal constant

    constexpr int len3 { 7 };
    std::array<int, len3> arr3 {};  // using constexpr variable

    enum Color
    {
        red,
        green,
        blue,
        num_colors
    };
    std::array<int, num_colors> arr4 {};  // using enum constant


    // Aggregate initialization of a std::array
    std::array<int, 5> arr5 { 1, 2, 3, 4, 5 };  // list initialization
    std::array<int, 5> arr6 = { 1, 2, 3, 4, 5 }; // copy-list initialization

    std::array<int, 5> arr7; // member default initialization (in most case left uninitialized)    
    std::array<int, 5> arr8 {}; // member value initialization (zero-initialized)

    std::array<int, 5> arr9 { 1, 2 }; // [1 2 0 0 0]


    // Const and constexpr std::array
    const std::array<int, 5> arr10 { 1, 2, 3, 4, 5 };  
    constexpr std::array<int, 5> arr11 { 1, 2, 3, 4, 5 };


    // CTAD (C++17)
    constexpr std::array arr12 { 1, 2, 3}; // type is deduced to std::array<int, 3>


    // std::array length and indexing
    std::array<int, 5> arr13 { 1, 2, 3, 4, 5 }; // not constexpr
    constexpr int len13 { arr13.size() };  // ok, return value is constexpr std::size_t and can be converted to int, not a narrowing conversion


    // std::get() does compile-time bounds checking for constexpr indices
    constexpr std::array<int, 5> arr14 { 1, 2, 3, 4, 5 };
    std::cout << std::get<2>(arr14) << '\n';  // 3
    std::cout << std::get<10>(arr14) << '\n';  // compile-time error

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/introduction-to-stdarray/
- https://www.learncpp.com/cpp-tutorial/stdarray-length-and-indexing/
*/