#include <iostream>
#include <vector>

/* stack behavior
*/

void func1()
{
    // stack behavior
    std::vector<int> arr{};
    arr.push_back(1);  // push on top of the stack
    arr.push_back(2);
    arr.pop_back();    // pop from the top of the stack
    arr.back();        // get the top of the stack, doesn't remove it
}

/* Resizing a vector changes both capacity and length
*/

void func2()
{
    std::vector<int> arr2(3); // vector containing 3, the length is also being set to 3
    arr2.push_back(4);        // push on top of the stack
    for (auto i : arr2)
        std::cout << i << ' ';  // [0 0 0 4] instead of [4 0 0]
    std::cout << '\n';

    std::vector arr3{1, 2, 3};
    arr3.resize(5);  // also changes the length
    arr3.push_back(4);
    for (auto i : arr3)
        std::cout << i << ' ';  // [1 2 3 0 0 4]
    std::cout << '\n';
}


/* reserve() member function changes the capacity (but not the length)
*/

void func3()
{
    std::vector<int> arr4{};
    arr4.reserve(5);  // reserve 5 elements
    arr4.push_back(1);
    for (auto i : arr4)
        std::cout << i << ' ';  // [1]
    std::cout << '\n';
}


/* push_back() vs emplace_back()

- emplace_back() also push element to end of vector.

- When we already have an object to be push, push_back and emplace_back are similar in efficiency.
- in cases where we are creating a temporary object to push, emplace_back() is more efficient.
*/

#include <string>

class Foo
{
public:
    Foo(int x, std::string b) {}
};


void func4()
{
    std::vector<Foo> arr5;
    arr5.push_back({ 1, "a" }); // creates a temporary object, and then copies it into the vector
    arr5.emplace_back(1, "a");          // forwards the arguments so the object can be created directly in the vector (no copy made)
}


int main()
{
    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/stdvector-and-stack-behavior/
*/