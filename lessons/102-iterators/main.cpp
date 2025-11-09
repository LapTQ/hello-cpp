/*
Different ways to iterate through an array:
- using indexes
- using pointers and pointer arithmetic 
- Range-based for-loops: They use iterators.

An iterator is an object designed to traverse through a container.
*/


/* Standard library iterators

- all standard library containers offer direct support for iteration.
- they have member functions named `begin()` and `end()` that can be used.
- The iterator header also contains two generic functions (std::begin and std::end) that can be used.



*/

#include <iostream>
#include <array>

template <typename T>
void print(const T* begin, const T* end)
{
    for (auto p{ begin }; p != end; ++p) // ++ to move to next element.
    {
        std::cout << *p << ' '; // Indirection to get value of current element.
    }
    std::cout << '\n';
}

void func1()
{
    std::array array{ 1, 2, 3 };

    auto begin{ array.begin() };
    auto end{ array.end() };
    print(begin, end);

    auto begin2{ std::begin(array) };
    auto end2{ std::end(array) };
    print(begin2, end2);
}

/* Iterator invalidation (dangling iterators)

- Much like pointers and references, iterators can be left “dangling” 
  if the elements being iterated over change address or are destroyed.
*/


int main()
{
    return 0;
}

/* References

- https://www.learncpp.com/cpp-tutorial/introduction-to-iterators/
*/