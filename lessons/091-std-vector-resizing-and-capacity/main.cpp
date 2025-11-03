/* Fixed-size arrays vs dynamic arrays

- std::array and C-style arrays are fixed-size array types.
- std::vector is a dynamic array.
*/


/* Resizing a std::vector at runtime
*/

#include <iostream>
#include <vector>

template <typename T>
void resizeBigger() {
    std::vector v{ 0, 1, 2 }; // create vector with 3 elements
    std::cout << "The length is: " << v.size() << '\n';

    v.resize(5);              // resize to 5 elements
    std::cout << "The length is: " << v.size() << '\n';

    for (auto i : v)
        std::cout << i << ' ';

    std::cout << '\n';
}

template <typename T>
void resizeSmaller() {
    std::vector v{ 0, 1, 2, 3, 4 };
    std::cout << "The length is: " << v.size() << '\n';

    v.resize(3);
    std::cout << "The length is: " << v.size() << '\n';

    for (auto i : v)
        std::cout << i << ' ';

    std::cout << '\n';
}

void func1()
{
    // Resize a std::vector at runtime
    resizeBigger<int>();   // 0 1 2 0 0
    resizeSmaller<int>();  // 0 1 2
}

/* length vs capacity of a std::vector

- capacity is how many elements the std::vector has allocated storage for
- length is how many elements are currently being used.

- A std::vector with a capacity of 5 has allocated space for 5 elements. 
  If the vector contains 2 elements in active use, the length (size) of the vector is 2. 
  The 3 remaining elements have memory allocated for them, but they are not 
  considered to be in active use. They can be used later without overflowing the vector.
*/

void func2()
{
    // Capacity of a std::vector
    std::vector<int> v{ 1, 2, 3, 4, 5 };
    v.resize(3);
    std::cout << "The length is: " << v.size() << '\n';     // 3
    std::cout << "The capacity is: " << v.capacity() << '\n'; // 5
}

/* Shrinking a std::vector

- std::vector has a member function called shrink_to_fit() that requests that the vector 
  shrink its capacity to match its length.
  Note that This request is non-binding, meaning the implementation is free to ignore it.
*/

void func3()
{ 
    std::vector<int> v{ 1, 2, 3, 4, 5 };
    v.shrink_to_fit();
    std::cout << "The length is: " << v.size() << '\n';     // 3
    std::cout << "The capacity is: " << v.capacity() << '\n'; // 3

}


int main()
{
    return 0;
}


/* Reallocation of storage, and why it is expensive

Reallocation process:
- The std::vector acquires new memory with capacity for the desired number of elements.
  These elements are value-initialized.
- The elements in the old memory are copied (or moved, if possible) into the new memory.
  The old memory is then returned to the system.
- The capacity and length of the std::vector are set to the new values.

Reallocation is an expensive process.
*/


/* References

- https://www.learncpp.com/cpp-tutorial/stdvector-resizing-and-capacity/
*/