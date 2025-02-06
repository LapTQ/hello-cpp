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

#include <iostream>
#include <vector>

int main()
{
	// Value initialization
	std::vector<int> empty{}; // vector containing 0 int elements, default constructor


    // list constructor
	std::vector<int> primes{ 2, 3, 5, 7 };          // vector containing 4 int elements with values 2, 3, 5, and 7
	std::vector vowels { 'a', 'e', 'i', 'o', 'u' }; // vector containing 5 char elements with values 'a', 'e', 'i', 'o', and 'u'.  Uses CTAD (C++17) to deduce element type char (preferred).


    // Accessing array elements using the subscript operator (operator[])
    std::cout << primes[0] << '\n'; // 2


    // Constructing a std::vector of a specific length
    std::vector<int> v1 = 10;     // copy initialization, but compile error because 10 won't match explicit constructor
    std::vector<int> v2(10);      // 10 not an initializer list => won't match list constructor, so it matches `explicit std::vector<T>(std::size_t)` constructor
    std::vector<int> v3{ 10 };    // { 10 } interpreted as initializer list, matches list constructor
    std::vector<int> v4 = { 10 }; // copy, { 10 } interpreted as initializer list, matches list constructor
    std::vector<int> v5({ 10 });  // same as v4, but it's copy construction, not direct initialization
    std::vector<int> v6 {};       // {} is empty initializer list, matches default constructor
    std::vector<int> v7 = {};     // {} is empty initializer list, matches default constructor


	return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/introduction-to-stdvector-and-list-constructors/
*/