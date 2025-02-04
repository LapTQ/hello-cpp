#include <iostream>

class Something
{
private:
    static inline int s_value { 1 }; // static member variable

public:
    static int getValue() { return s_value; } // static member function
};


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
    std::cout << Something::getValue() << '\n';
}


/* Static member functions have no this pointer
*/


/* References

- https://www.learncpp.com/cpp-tutorial/static-member-functions/
*/