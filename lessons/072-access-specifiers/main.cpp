/*
- C++ has three different access levels: public, private, and protected.
*/

/* The members of a struct are public by default
*/

#include <iostream>

struct SDate
{
    int year {};       // public by default
    int month {};      // public by default
    int day {};        // public by default

    void print() const // public by default
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

/* The members of a class are private by default
*/

class CDate // now a class instead of a struct
{
    int m_year {};     // private by default
    int m_month {};    // private by default
    int m_day {};      // private by default

    void print() const // private by default
    {
        // private members can only be accessed by other members
        std::cout << m_year << '/' << m_month << '/' << m_day;
    }
};

/* Reminder:

- an "aggregate" can have “no private or protected non-static data members.”
  => our CDate class does not qualify as an aggregate because it has private members.
*/

void func1()
{
    CDate today { 2020, 10, 14 }; // compile error: can no longer use aggregate initialization
                                  // because CDate does not qualify as an aggregate

    // private members can not be accessed by the public
    today.m_day = 16; // compile error: the m_day member is private
    today.print();    // compile error: the print() member function is private
}


/* Naming your private member variables

- starting with an “m_” prefix. This is done to easily differentiate data members from function parameters.
    ```
    void setAge(int age) { m_age = age; }
    ```

    This is the same reason we recommend using “s_” prefixes for local static variables, and “g_” prefixes for globals.
    
*/


/* Setting access levels via access specifiers

- An access specifier sets the access level of "all members" that follow the specifier.
*/

class CDate2
{
// Any members defined here would default to private

public: // here's our public access specifier

    void print() const
    {
        std::cout << m_year << '/' << m_month << '/' << m_day << '\n';
    }

private: // here's our private access specifier

    int m_year { 2020 };
    int m_month { 14 };
    int m_day { 10 };
};

void func2()
{
    CDate2 today2 {};   // using default member initialization
    today2.print(); // okay, main() allowed to access public members
}


/* (Often misunderstood) C++ access levels work on a per-class basis, not per-object

- a member function can also directly access the private members of 
  ANY other object of the same class type that is in scope.
*/

#include <string>
#include <string_view>

class Person
{
private:
    std::string m_name{};   // private member

public:
    void kisses(const Person& p) const
    {
        std::cout << m_name << " kisses " << p.m_name << '\n'; // okay, because p is the same type as the implicit object
    }

    void setName(std::string_view name)
    {
        m_name = name;
    }
};

void func3()
{
    Person joe;
    joe.setName("Joe");
    Person kate;
    kate.setName("Kate");

    joe.kisses(kate);
}


int main()
{
    func1();


    // Setting access levels via access specifiers
    func2();


    // C++ access levels work on a per-class basis, not per-object
    func3();


    return 0;
}


/* The technical and practical difference between structs and classes

- A class defaults its members to private, whereas a struct defaults its members to public.

- As a rule of thumb, use a struct when all of the following are true:
    + You have a simple collection of data that doesn’t benefit from restricting access.
    + Aggregate initialization is sufficient.
    + You have no class invariants, setup needs, or cleanup needs.
*/


/* References

- https://www.learncpp.com/cpp-tutorial/public-and-private-members-and-access-specifiers/
*/