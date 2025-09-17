/*
- you learned that static member variables are member variables that belong to the class rather than objects of the class
- But what if a static member variable is private?
- 1 solution is to access that private members via a public member functions. But it means that we’d need to instantiate an object of the class type to use the function!
=> use Static member functions instead.
*/

#include <iostream>

class Something
{
private:
    static inline int s_value { 1 }; // static member variable

public:
    static int getValue() { return s_value; } // static member function
};

void func1()
{
    std::cout << Something::getValue() << '\n';
}


/* Static members defined outside the class definition
*/

class IDGenerator
{
private:
    static inline int s_nextID { 1 };

public:
     static int getNextID(); // Here's the declaration for a static function
};

// definition of the static function outside of the class.  Note we don't use the static keyword here.
int IDGenerator::getNextID() { return s_nextID++; }


int main()
{
    func1();
}


/* Static member functions have no this pointer

- This makes sense when you think about it -- the this pointer always points to the object that the member function is working on. Static member functions do not work on an object, so the this pointer is not needed.
*/

/* static member functions cannot directly access other non-static members (variables or functions).

- This is because non-static members must belong to a class object, and static member functions have no class object to work with!

*/


/* References

- https://www.learncpp.com/cpp-tutorial/static-member-functions/
*/