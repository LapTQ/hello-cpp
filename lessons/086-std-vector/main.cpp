/*
- std::vector is defined in the <vector> header as a class template.
*/


/* list constructor

- Containers typically have a special constructor called a list constructor that 
  allows us to construct an instance of the container using an "initializer list".
- The list constructor does three things:
    + Ensures the container has enough storage to hold all the initialization values (if needed).
    + Sets the length of the container to the number of elements in the initializer list (if needed).
    + Initializes the elements to the values in the initializer list (in sequential order).
*/


/* Constructing a std::vector of a specific length

- use direct initialization (braced initialization), instead of list initialization (with initializer list).

```
std::vector<int> data( 10 ); // vector containing 10 int elements, value-initialized to 0
```

- C++ has a special rule:
    + If the initializer list is empty, the default constructor is preferred over the list constructor.
    + If the initializer list is non-empty, a matching list constructor is preferred over other matching constructors.
*/


/* Const and constexpr std::vector

- cannot be made constexpr.
*/


/* subscript problem

- when the container classes in the C++ standard library was being designed, the length and array subscripts were decided to be unsigned.
- However, In retrospect, this is generally regarded as having been the wrong choice. Previously, we discussed the reasons 
  why we prefer to use signed values to hold quantities.

- Reminder:
    + sign conversions are narrowing conversions, except when constexpr:
        For example:
        ```
        int s { 5 };
        unsigned int u { s };       // compile error: list initialization disallows narrowing conversion

        void foo(unsigned int);
        foo(s);                     // might or might not warn, copy initialization allows narrowing conversion

        constexpr int s { 5 };      // now constexpr
        unsigned int u { s };       // ok: s is constexpr and can be converted safely, not a narrowing conversion
        ```
*/


/* The length and indices of std::vector have type size_type

- size_type is an alias for the type used for the length (and indices, if supported) of the container.
  (just similar to std::size_t is a typedef for some large unsigned integral type, usually `unsigned long` or `unsigned long long`).
- size_type is almost always an alias for std::size_t.
- When accessing the size_type member of a container class, we must scope qualify it with the fully templated name 
  of the container class. For example, `std::vector<int>::size_type`.

- To get the length of a std::vector, we can use the .size() member function or the std::size() function (C++17).
- C++20 in introduces the std::ssize() non-member function, which returns the length as a large "signed" integral type
   (usually std::ptrdiff_t).
*/


/* Accessing array elements

- using operator[] does no bounds checking.
- using the at() member function does runtime bounds checking.
  Because it does runtime bounds checking on every call, it's slower than operator[].

- Indexing with a constexpr signed int is not a narrowing conversion.
- Indexing with a non-constexpr std::size_t value is not a narrowing conversion.
- Indexing with a non-constexpr signed value is a narrowing conversion.
  Your compiler should produce a warning about this being an unsafe conversion (if it doesn’t, you should consider modifying your warnings so that it does).
- Indexing the result of the data() member function with signed values is not a narrowing conversion.
  Under the hood, std::vector holds its elements in a C-style array. The data() member function returns a pointer to this underlying C-style array.
  Since C-style arrays allow indexing with both signed and unsigned types, we don’t run into any sign conversion issues.
*/

#include <iostream>
#include <vector>

int main()
{
	// Value initialization
	std::vector<int> empty{}; // vector containing 0 int elements, default constructor


    // list constructor
	std::vector<int> primes{ 2, 3, 5, 7 };          // vector containing 4 int elements with values 2, 3, 5, and 7
	std::vector vowels { 'a', 'e', 'i', 'o', 'u' }; // vector containing 5 char elements with values 'a', 'e', 'i', 'o', and 'u'.  Uses CTAD (C++17) to deduce element type char (preferred).


    // Constructing a std::vector of a specific length
    std::vector<int> v1 = 10;     // copy initialization, but compile error because 10 won't match explicit constructor
    std::vector<int> v2(10);      // 10 not an initializer list => won't match list constructor, so it matches `explicit std::vector<T>(std::size_t)` constructor
    std::vector<int> v3{ 10 };    // { 10 } interpreted as initializer list, matches list constructor
    std::vector<int> v4 = { 10 }; // copy, { 10 } interpreted as initializer list, matches list constructor
    std::vector<int> v5({ 10 });  // same as v4, but it's copy construction, not direct initialization
    std::vector<int> v6 {};       // {} is empty initializer list, matches default constructor
    std::vector<int> v7 = {};     // {} is empty initializer list, matches default constructor


    // Accessing array elements using the subscript operator (operator[])
    std::cout << primes[0] << '\n'; // 2


    // get the length of a std::vector
    std::cout << "The length of primes is: " << primes.size() << '\n'; // using .size() member function, returns length as type `size_type` (alias for `std::size_t`)
    std::cout << "The length of primes is: " << std::size(primes) << '\n'; // (C++17) using std::size() function
    int length { static_cast<int>(primes.size()) }; // static_cast to avoid signed/unsigned conversion warning or error
    
    std::cout << "length: " << std::ssize(primes); // C++20, returns the length as a large "signed" integral type
    int length2 { static_cast<int>(std::ssize(primes)) }; // static_cast return value to int

    std::size_t length3 { primes.size() }; // okay, no conversion required


    // Accessing array elements
    std::cout << primes[9]; // undefined behavior
    std::cout << primes.at(9); // throws exception

    constexpr int index { 3 };         // constexpr
    std::cout << primes[index] << '\n'; // okay, constexpr index implicitly converted to std::size_t, not a narrowing conversion
    std::size_t index2 { 3 };           // non-constexpr of type std::size_t
    std::cout << primes[index2] << '\n'; // okay, no conversion required
    int index3 { 3 };                   // non-constexpr signed value
    std::cout << primes[index3] << '\n'; // possible warning: index implicitly converted to std::size_t, narrowing conversion
    std::cout << primes.data()[index] << '\n'; // okay: no sign conversion warnings


	return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/introduction-to-stdvector-and-list-constructors/
- https://www.learncpp.com/cpp-tutorial/stdvector-and-the-unsigned-length-and-subscript-problem/
*/