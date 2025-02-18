/* Order of construction of derived classes

- When C++ constructs derived objects, it does so in phases:
    + First, the most-base class is constructed. 
    + Then each child class is constructed in order, until the most-child class is constructed last.

Here’s what actually happens when derived is instantiated:
    + Memory for derived is set aside (enough for both the Base and Derived portions)
    + The appropriate Derived constructor is called
    + The Base object is constructed first using the appropriate Base constructor. 
      If no base constructor is specified, the default constructor will be used.
    + The member initializer list initializes variables
    + The body of the constructor executes
    + Control is returned to the caller
*/

#include <iostream>

class Base
{
public:
    int m_id {};

    Base(int id=1)
        : m_id { id }
    {
        std::cout << "Base\n";
    }

    int getId() const { return m_id; }
};

class Derived1: public Base
{
public:
    double m_cost {};

    Derived1(double cost=2)
        : m_cost { cost }
    {
        std::cout << "Derived\n";
    }

    double getCost() const { return m_cost; }
};

void func1()
{
    std::cout << "Instantiating Base\n";
    Base base;

    std::cout << "Instantiating Derived\n";
    Derived1 derived;

    std::cout << "Derived1 id: " << derived.getId() << " cost: " << derived.getCost() << '\n';  // 1 2
}

/*
this print:
    Instantiating Base
    Base
    Instantiating Derived
    Base
    Derived
*/


/* Initializing base class members

- C++ prevents classes from initializing inherited member variables in the member initializer list of a constructor.
  This means this doesn’t work:
    ```
    Derived::Derived(int id, double cost)
        : m_id { id }
        , m_cost { cost }
    {
    }
    ```
  Why? Read: https://www.learncpp.com/cpp-tutorial/constructors-and-initialization-of-derived-classes/#:~:text=Why%20does%20C%2B%2B%20do%20this%3F

- To explicitly choose which Base class constructor will be called:
*/

class Derived2: public Base
{
public:
    double m_cost {};

    Derived2(double cost=0.0, int id=0)
        : Base{ id } // Call Base(int) constructor with value id!
        , m_cost{ cost }
    {
    }

    double getCost() const { return m_cost; }
};

void func2()
{
    Derived2 derived { 1.3, 5 };
    std::cout << "Derived2 id: " << derived.getId() << " cost: " << derived.getCost() << '\n';  // 5 1.3
}


int main()
{
    // Order of construction of derived classes
    func1();


    // Initializing base class members
    func2();

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/basic-inheritance-in-c/
- https://www.learncpp.com/cpp-tutorial/order-of-construction-of-derived-classes/
- https://www.learncpp.com/cpp-tutorial/constructors-and-initialization-of-derived-classes/
*/