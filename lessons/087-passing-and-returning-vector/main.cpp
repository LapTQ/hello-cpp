/* passing a std::vector
*/
#include <iostream>
#include <vector>

void passByRef(const std::vector<int>& arr) // we must explicitly specify <int> here
{
    std::cout << arr[0] << '\n';
}

template <typename T>       // use a template
void passByRef2(const std::vector<T>& arr)
{
    std::cout << arr[0] << '\n';
}

void passByRef3(const auto& arr) // (C++20) can be desirable when we might want to operate on more than just a std::vector
{
    std::cout << arr[0] << '\n';
}


/* Copy semantics and Move semantics

- Copy semantics refers to how copies of objects are made.
  For class types, copy semantics are typically implemented via the copy constructor (and copy assignment operator).

    When copy semantics is not optimal:
    ```
    std::vector<int> generate() // return by value
    {
        // We're intentionally using a named object here so mandatory copy elision doesn't apply
        std::vector arr1 { 1, 2, 3, 4, 5 }; // copies { 1, 2, 3, 4, 5 } into arr1
        return arr1;
    }

    int main()
    {
        std::vector arr2 { generate() }; // the return value of generate() is a temporary object and will die at the end of the expression

        return 0;
    }
    ```
    We've made a potentially expensive copy with copy semantics. We don’t need two sets of data to exist simultaneously.

- Move semantics: determine how the data from one object is moved (transfer ownership, usually just two or three pointer assignments) to another object.
    When move semantics is invoked, any data member that can be moved is moved, and any data member that can’t be moved is copied.
    => more efficient than copy semantics: no copy of the data would need to be made, and no longer have any data to destroy.
*/


/* How move semantics is invoked

- Normally, when an object is being initialized with (or assigned) an object of the same type, copy semantics will be used (assuming the copy isn’t elided).
- However, when all of the following are true, move semantics will be invoked instead:
    + The type of the object supports move semantics.
    + The object is being initialized with (or assigned) an rvalue (temporary) object of the same type.
    + The move isn’t elided.
- And for move-capable types, move semantics is invoked automatically when returning by value.
*/


/* it is okay to return a std::vector by value!!!

- Sadly, not many types support move semantics. However, std::vector and std::string both do!
  (Such types should still be passed by const reference)
  Read more: https://www.learncpp.com/cpp-tutorial/returning-stdvector-and-an-introduction-to-move-semantics/#:~:text=Wait%2C%20wait%2C%20wait.%20Expensive%2Dto%2Dcopy%20types%20shouldn%E2%80%99t%20be%20passed%20by%20value%2C%20but%20if%20they%20are%20move%2Dcapable%20they%20can%20be%20returned%20by%20value%3F
*/

int main()
{
    // passing a std::vector
    std::vector primes{ 2, 3, 5, 7, 11 };
    passByRef(primes);

    std::vector dbl{ 1.1, 2.2, 3.3 };
    passByRef(dbl); // compile error: std::vector<double> is not convertible to std::vector<int>

    passByRef2(dbl); // okay, will instantiate passByRef(const std::vector<double>&)
    passByRef3(dbl); // okay, will instantiate passByRef(const std::vector<double>&)

    return 0;
}



/* References

- https://www.learncpp.com/cpp-tutorial/passing-stdvector/
- https://www.learncpp.com/cpp-tutorial/returning-stdvector-and-an-introduction-to-move-semantics/
*/