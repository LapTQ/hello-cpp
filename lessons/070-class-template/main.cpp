/* 
- In previous lessons, we discussed challenge of having to create a separate (overloaded) function for each different set of types.
- Aggregate types have similar challenges:
    + there is a lot of redundancy here.
    + Unlike functions, type definitions can’t be overloaded. 
*/

/* Class templates

A “class type” is a struct, class, or union type. Although we’ll be demonstrating 
“class templates” on structs for simplicity, everything here applies equally well to classes.
*/

#include <iostream>

template <typename T, typename U>
struct Pair
{
    T first{};
    U second{};
};


template <typename T, typename U>
constexpr auto max(Pair<T, U> p) 
{
    return (p.first < p.second ? p.second : p.first);
}


/* std::pair

- Because working with pairs of data is common, the C++ standard library contains 
  a class template named std::pair.
- you should favor std::pair over writing your own.
*/

template <typename T, typename U>
void print(std::pair<T, U> p)
{
    // the members of std::pair have predefined names `first` and `second`
    std::cout << '[' << p.first << ", " << p.second << ']';
}


/* Template argument deduction guides

- You may be surprised to find that the following program doesn’t compile in C++17:
```
template <typename T, typename U>
struct Pair
{
    T first{};
    U second{};
};

...
Pair<int, int> p1{ 1, 2 }; // ok
Pair p4{ 1, 2 };  // compile error in C++17 (okay in C++20)
```
This is because in C++17, CTAD doesn’t know how to deduce the template arguments 
for aggregate class templates.

- std::pair (and other standard library template types) come with pre-defined deduction guides.
*/

// deduction guide for our Pair (needed in C++17 only)
template <typename T, typename U>
Pair(T, U) -> Pair<T, U>; // should deduce to Pair<T, U>


/* Type template parameters with default values
*/

template <typename T=int, typename U=int> // default T and U to type int
struct Pair2
{
    T first{};
    U second{};
};

template <typename T, typename U>
Pair2(T, U) -> Pair2<T, U>;


int main()
{
    Pair<int, int> p1{ 5, 6 };        // instantiates Pair<int> and creates object p1
    std::cout << p1.first << ' ' << p1.second << '\n';

    Pair<double, double> p2{ 1.2, 3.4 }; // instantiates Pair<double> and creates object p2
    std::cout << p2.first << ' ' << p2.second << '\n';

    std::cout << max<int>(p1) << " is larger\n"; // explicit call to max<int>
    std::cout << max(p2) << " is larger\n";      // call to max<double> using template argument deduction


    // std::pair
    std::pair<int, double> p3{ 5, 6.7 };
    print(p3); // [5, 6.7]


    // Template argument deduction guides
    Pair p4{ 1, 2 };  // compile error in C++17 (okay in C++20) without deduction guide


    // Type template parameters with default values
    Pair2 p5; // use default Pair2<int, int>

    return 0;
}

/* Using class templates in multiple files

- Just like function templates, class templates are typically defined in header files.
*/

/* References

- https://www.learncpp.com/cpp-tutorial/class-templates/
- https://www.learncpp.com/cpp-tutorial/class-template-argument-deduction-ctad-and-deduction-guides/
*/