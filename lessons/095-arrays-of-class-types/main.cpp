/*
- the elements of a std::array can be any object type.
- We’ll use structs to illustrate our points in this lesson. The material applies equally well to classes.
*/



/* Why the inialization
```
    constexpr std::array<House, 3> houses3 { 
        { 13, 1, 7 }, // initialize for C-style array member implementation_defined_name
        { 14, 2, 5 },
        { 15, 2, 4 }
    };
```
doesn't work?

A std::array is defined as a struct like this:
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


#include <array>
#include <iostream>

struct House
{
    int number{};
    int stories{};
    int roomsPerStory{};
};

int main()
{
    // the elements of a std::array can be any object type.
    std::array<House, 3> houses{};
    houses[0] = { 13, 1, 7 };
    houses[1] = { 14, 2, 5 };
    houses[2] = { 15, 2, 4 };

    constexpr std::array houses2 { // use CTAD to deduce template arguments <House, 3>
        House{ 13, 1, 7 },
        House{ 14, 2, 5 },
        House{ 15, 2, 4 }
    };

    // doesn't work
    constexpr std::array<House, 3> houses3 { 
        { 13, 1, 7 }, // initialize for C-style array member implementation_defined_name
        { 14, 2, 5 },
        { 15, 2, 4 }
    };

    // but this works
    constexpr std::array<House, 3> houses4 {
        { // extra set of braces 
            { 13, 4, 30 }, 
            { 14, 3, 10 }, 
            { 15, 3, 40 }, 
        }
    };


    // Brace elision for aggregates
    constexpr std::array students{ // single braces
        Student{0, "Alex"}, 
        Student{ 1, "Joe" }, 
        Student{ 2, "Bob" } 
    };


    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/stdarray-of-class-types-and-brace-elision/
*/