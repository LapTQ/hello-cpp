/*
- the elements of a std::array can be any object type.
- We’ll use structs to illustrate our points in this lesson. The material applies equally well to classes.
*/

#include <array>
#include <iostream>

struct House
{
    int number{};
    int stories{};
    int roomsPerStory{};
};

void func1()
{
    std::array<House, 3> houses{};
    houses[0] = { 13, 1, 7 };
    houses[1] = { 14, 2, 5 };
    houses[2] = { 15, 2, 4 };

    constexpr std::array houses2 { // use CTAD to deduce template arguments <House, 3>
        House{ 13, 1, 7 },
        House{ 14, 2, 5 },
        House{ 15, 2, 4 }
    };
}


/* Why doesn't the following inialization work?
*/

void func2()
{   
    // doesn't work
    constexpr std::array<House, 3> houses3 { 
        { 13, 1, 7 },
        { 14, 2, 5 },
        { 15, 2, 4 }
    };
}

/*
A std::array is defined as a "struct" like this:
```
template<typename T, std::size_t N>
struct array
{
    T implementation_defined_name[N];
}
```
`implementation_defined_name` is a C-style array with N elements of type T.

Then, `{ 13, 1, 7 }` is used to initialize implementation_defined_name
Then the compiler will discover that we’ve provided two more initialization values ({ 14, 2, 7 } and { 15, 2, 5 })
which exceeds the number of members in the struct.

The correct way to initialize the above is to add an extra set of braces.
*/

void func3()
{
    // works
    constexpr std::array<House, 3> houses4 {
        { // extra set of braces 
            { 13, 4, 30 }, 
            { 14, 3, 10 }, 
            { 15, 3, 40 }, 
        }
    };
}


/* Brace elision for aggregates

Given the explanation above, you may be wondering why our normal aggregate initialization syntax works for std::array:
```
constexpr std::array<int, 3> arr { 1, 2, 3 }; // single braces
```

Actually, we can:
```
constexpr std::array<int, 3> arr { { 1, 2, 3 } }; // double braces
```
However, aggregates in C++ support a concept called brace elision.

- Generally, you can omit braces when initializing a std::array with scalar (single) values, 
  or with class types or arrays where the type is explicitly named with each element.
- There is no harm in always initializing std::array with double braces.
*/

#include <string_view>

struct Student
{
	int id{};
	std::string_view name{};
};

void func4()
{
    constexpr std::array students{ // single braces
        Student{0, "Alex"}, 
        Student{ 1, "Joe" }, 
        Student{ 2, "Bob" } 
    };
}


/* Arrays of references via std::reference_wrapper

- because references are not objects, you cannot make an array of references.
  The elements of an array must also be assignable, and references can’t be reseated.

- std::reference_wrapper is a standard library class template that behaves like a modifiable lvalue reference to T.

Notes about std::reference_wrapper:
- Operator= will "reseat" a std::reference_wrapper (change which object is being referenced).
- std::reference_wrapper<T> will implicitly convert to T&.
- The get() member function can be used to get a T&. This is useful when we want to 
  update the value of the object being referenced.

- In this lesson, we’ll use std::array in the examples, but this is equally applicable to all array types.
*/

#include <functional> // for std::reference_wrapper

void func5()
{
    int x { 1 };
    int y { 2 };
    std::array<int&, 2> refarr { x, y }; // compile error: cannot define array of references

    int& ref1 { x };
    int& ref2 { y };
    std::array valarr { ref1, ref2 }; // ok, but this is actually a std::array<int, 2>, not an array of references
    valarr[0] = 10;
    std::cout << valarr[0] << " " << x << '\n'; // 10 1

    std::array<std::reference_wrapper<int>, 2> arr { x, y };
    arr[0].get() = 10;
    std::cout << arr[0] << " " << x << '\n'; // 10 10
}


/* std::ref and std::cref

- Prior to C++17, CTAD didn’t exist.
- the std::ref() and std::cref() functions were provided as shortcuts to create 
  std::reference_wrapper and const std::reference_wrapper wrapped objects.
*/

void func6()
{
    int x { 1 };

    // C++11, long
    std::reference_wrapper<int> ref3 { x };
    auto ref4 { std::reference_wrapper<int>{ x }};

    // C++11, using shorter std::ref and std::cref
    auto ref { std::ref(x) };   // C++11, deduces to std::reference_wrapper<int>
    auto cref { std::cref(x) }; // C++11, deduces to std::reference_wrapper<const int>

    // C++17, using CTAD
    std::reference_wrapper ref5 { x };
    auto ref6 { std::reference_wrapper{ x }};
}


int main()
{
    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/stdarray-of-class-types-and-brace-elision/
- https://www.learncpp.com/cpp-tutorial/arrays-of-references-via-stdreference_wrapper/
*/