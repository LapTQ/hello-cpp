/* Overloaded operator[] for const objects

- we can define a non-const and a const version of operator[] separately. 
  The non-const version will be used with non-const objects, and the const version with const-objects.
*/

#include <iostream>

class IntList
{
private:
    int m_list[10]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // give this class some initial state for this example

public:
    // For non-const objects: can be used for assignment
    // Must return by reference, because the any value on the left hand side of an assignment statement must be an l-value
    int& operator[] (int index)
    {
        return m_list[index];
    }

    // For const objects: can only be used for access
    // This function could also return by value if the type is cheap to copy
    const int& operator[] (int index) const
    {
        return m_list[index];
    }
};

void func1()
{
    IntList list{};
    list[2] = 3; // okay: calls non-const version of operator[]
    std::cout << list[2] << '\n';

    const IntList clist{};
    // clist[2] = 3; // compile error: clist[2] returns const reference, which we can't assign to
    std::cout << clist[2] << '\n';
}


/* Removing duplicate code between const and non-const overloads

- the non-const version of the function can call the const version of the function,
  and we need to remove the const using const_cast.
*/

#include <utility> // for std::as_const

class IntList2
{
private:
    int m_list[10]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; 

public:
    int& operator[] (int index)
    {
        // use std::as_const to get a const version of `this` (as a reference)
        // then const_cast to discard the const on the returned reference
        return const_cast<int&>(std::as_const(*this)[index]);
    }

    const int& operator[] (int index) const
    {
        return m_list[index];
    }
};


int main()
{
    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/overloading-the-subscript-operator/
*/