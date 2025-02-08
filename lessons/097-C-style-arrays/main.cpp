/* Declaring a C-style array

- Syntax: use square brackets ([]) to tell the compiler that a declared object is a C-style array.
- Inside the square brackets, we can optionally provide the length of the array, which is an 
  integral value of type std::size_t.
- The length of a C-style array must be at least 1.

- The array length of a c-style array "must" be a constant expression (Just like std::array).
- Unlike the standard library container classes (which use unsigned indices of type std::size_t only), 
  the index of a C-style array can be a value of any integral type (signed or unsigned) or an unscoped enumeration.
*/


/* Aggregate initialization of C-style arrays

- One downside of using a C-style array is that the element’s type must be explicitly specified. 
  CTAD doesn’t work because C-style arrays aren’t class templates.
*/


/* When we initialize a C-style array with an initializer list, we can omit the length (in the array definition) 
*/


/* C-style arrays can be const or constexpr
*/


/* Getting the length of a C-style array

- (C++17) can use std::size() or std::ssize().
- Prior to C++17, there was no standard library function to get the length of a C-style array.
  So we can use this function instead:
*/

#include <cstddef> // for std::size_t

template <typename T, std::size_t N>
constexpr std::size_t length(const T(&)[N]) noexcept
{
	return N;
}


/* C-style arrays don’t support assignment
*/

#include <iostream>

int main()
{
    int arr[5]; // define an array of 5 int values
    arr[1] = 7; // use subscript operator to index array element 1


    // Aggregate initialization of C-style arrays
    int arr1[5]; // member default initialization are left uninitialized
    int arr2[5] {}; // member value initialization (zero-initialized) (preferred)

    int arr3[5] { 1, 2, 3, 4, 5 }; // list initialization (preferred)
    int arr4[5] = { 1, 2, 3, 4, 5 }; // copy-list initialization

    int arr5[5] { 1, 2, 3, 4, 5, 6 }; // error: too many initializers for 'int [5]'
    int arr6[5] { 1, 2 }; // [1 2 0 0 0] (the rest are value-initialized)

    auto arr7[5] { 1, 2, 3, 4, 5 }; // compile error: can't use type deduction on C-style 


    // When we initialize a C-style array with an initializer list, we can omit the length (in the array definition)
    int arr8[] { 1, 2, 3, 4, 5 }; // the length is deduced


    // Getting the length of a C-style array
    std::cout << length(arr) << '\n'; // prior to C++17
    std::cout << std::size(arr) << '\n'; // C++17, returns unsigned integral
    std::cout << std::ssize(arr) << '\n'; // C++20, returns signed integral


    // C-style arrays don’t support assignment
    int arr9[3] { 1, 2, 3 };
    arr9[0] = 4; // ok
    arr9 = { 4, 5, 6 }; // compile error

    return 0;
}

/* References

- https://www.learncpp.com/cpp-tutorial/introduction-to-c-style-arrays/
*/