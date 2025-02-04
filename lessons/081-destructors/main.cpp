/*
- The term “clean up” is often used to refer to any set of tasks that a class 
  must perform before an object of the class is destroyed.
  For example: closing a file, releasing memory, writing to a log file, etc.

- In previous lessons, we covered constructors. Analogously, classes have another 
  special member function called a destructor that is called automatically when an 
  object of a non-aggregate class type is destroyed.
*/


/* Destructor

- Rules
    + The destructor must have the same name as the class, preceded by a tilde (~).
    + The destructor can not take arguments.
    + The destructor has no return type.
=> A class can only have a single destructor.
*/

#include <iostream>

class Simple
{
private:
    int m_id {};

public:
    Simple(int id)
        : m_id { id }
    {
        std::cout << "Constructing Simple " << m_id << '\n';
    }

    ~Simple() // here's our destructor
    {
        std::cout << "Destructing Simple " << m_id << '\n';
    }

    int getID() const { return m_id; }
};

int main()
{
    // Allocate a Simple
    Simple simple1{ 1 };
    {
        Simple simple2{ 2 };
    } // simple2 dies here

    return 0;
} // simple1 dies here


/* A warning about the std::exit() function

- std::exit() can be used to terminate your program immediately. 
  Local variables are not destroyed first, and because of this, no destructors will be called. 
=>  Be wary if you’re relying on your destructors to do necessary cleanup work in such a case.
*/

/* References

- https://www.learncpp.com/cpp-tutorial/introduction-to-destructors/
*/