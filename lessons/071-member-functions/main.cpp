/* Member functions

- In addition to having member variables, class types (which includes structs, classes, and unions) 
  can also have their own functions!

- Member functions defined inside the class type definition are implicitly inline, 
  so they will not cause violations of the ODR if the class type definition is 
  included into multiple code files.
*/

/* implicit object

- when we call today.print(), today is the "implicit object", and it is implicitly passed 
  to the print() member function.
*/

/* Accessing members inside a member function uses the implicit object

- Inside a member function, any member identifier that is not prefixed with 
  the member selection operator (.) is associated with the implicit object.
*/

#include <iostream>
#include <string>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print() // defines a member function named print
    {
        std::cout << year << '/' << month << '/' << day << '\n';
    }
};

struct Person
{
    std::string name{};
    int age{};

    void kisses(const Person& person)
    {
        std::cout << name << " kisses " << person.name << '\n';
        // name (without prefix (.)) is associated with the implicit object
    }
};


/* Member variables and functions can be defined in any order

- The C++ compiler normally compiles code from top to bottom.
  Non-members must be declared before they can be used, or the compiler will complain:
    ```
    int x()
    {
        return y(); // error: y not declared yet, so compiler doesn't know what it is
    }

    int y() {}
    ```
- However, inside a class definition, this restriction doesn’t apply.
*/

struct Foo
{
    int z() { return m_data; } // We can access data members before they are defined
    int x() { return y(); }    // We can can access member functions before they are defined

    int m_data { y() };        // WARNING: initialization accesses a member that is not declared => still compile but with undefined behavior.
    int y() { return 5; }
};

int main()
{
    // Member functions
    Date today { 2020, 10, 14 };
    today.print();  // also accessed using member selection operator (.)

    Person joe{ "Joe", 29 };
    Person kate{ "Kate", 27 };
    joe.kisses(kate);   // print: Joe kisses Kate

    return 0;
}


/* (For advanced readers) How compiler allow definition of members in any order

- When the compiler encounters a member function defined inside the class definition:
    + The member function is implicitly forward declared.
    + The member function definition is moved immediately after the end of the class definition.

    For example:
    ```
    struct Foo
    {
        int z() { return m_data; } // m_data not declared yet
        int x() { return y(); }    // y not declared yet
        int y() { return 5; }

        int m_data{};
    };
    ```
    
    It will compile the equivalent of this:
    ```
    struct Foo
    {
        int z(); // forward declaration of Foo::z()
        int x(); // forward declaration of Foo::x()
        int y(); // forward declaration of Foo::y()

        int m_data{};
    };

    int Foo::z() { return m_data; } // m_data already declared above
    int Foo::x() { return y(); }    // y already declared above
    int Foo::y() { return 5; }
    ```
*/

/*
- In C, structs only have data members, not member functions.
- In C++, while designing classes, Bjarne Stroustrup determined that structs should 
  be granted the ability to have member functions.

  This excludes constructors, as doing so makes structs a non-aggregate.
*/


/* References

- https://www.learncpp.com/cpp-tutorial/introduction-to-classes/
- https://www.learncpp.com/cpp-tutorial/member-functions/
*/