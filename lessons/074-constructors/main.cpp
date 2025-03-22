/* Constructors

- ...  is a special member function that is automatically called 
  after a non-aggregate class type object is created.

- That said, constructors do not create the objects.
  the compiler sets up the memory allocation for the object prior to the constructor call. 
  The constructor is then called on the uninitialized object.
- aggregates are not allowed to have constructors -- so if you add 
  a constructor to an aggregate, it is no longer an aggregate.
*/

/* Naming constructors

- Constructors must have the same name as the class.
- Constructors have no return type (not even void).
*/

#include <iostream>

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo(int x, int y)
    {
        std::cout << "Foo(" << x << ", " << y << ") constructed\n";
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

void func1()
{
    Foo foo{ 6, 7 }; // calls Foo(int, int) constructor
    foo.print();    // Foo(0, 0)
}


/* Member initialization via a member initialization list
*/

class Foo2
{
private:
    int m_x {};
    int m_y {};

public:
    Foo2(int x, int y)
        // member initialization list
        : m_x { x }
        , m_y { y }
    {
        std::cout << "Foo(" << x << ", " << y << ") constructed\n";
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

void func2()
{
    Foo2 foo2{ 6, 7 }; 
    foo2.print();    // Foo(6, 7)
}


/* Member initialization order

- the members in a member initializer list are always initialized 
  in the order in which they are defined inside the class, not from left to right in the list.
  So pay attention.

- statements in the body of the constructor execute after the member initializer list has executed.
*/

#include <algorithm> // for std::max

class Foo3
{
private:
    int m_x{};
    int m_y{};

public:
    Foo3(int x, int y)
        : m_y { std::max(x, y) }, m_x { m_y } // issue on this line
    {
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

void func3()
{
    Foo3 foo3{ 6, 7 };
    foo3.print();    // Foo(0, 7) on my machine
}


/* Member initializer list vs default member initializers

- If a member is listed in the member initializer list, that initialization value is used
- Otherwise, if the member has a default member initializer, that initialization value is used
- Otherwise, the member is default-initialized (which for fundamental types, means it is left uninitialized).
*/

class Foo4
{
private:
    int m_x {};    // default member initializer
    int m_y { 2 }; // default member initializer
    int m_z;      // no initializer

public:
    Foo4(int x)
        : m_x { x } // member initializer list
    {
        std::cout << "Foo constructed\n";
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ", " << m_z << ")\n";
    }
};

void func4()
{
    Foo4 foo4{ 6 };
    foo4.print();    // Foo(6, 2, 0)
}


/* Assignment inside constructors body

- New programmers sometimes use the body of the constructor to assign values to members.
  Although in this simple case this will produce the expected result, in case where members 
  are required to be initialized (such as for data members that are const or references)
  then assignment will not work.

= Prefer using the member initializer list to initialize your members 
  over assigning values in the body of the constructor.
*/

class Foo5
{
private:
    int m_x { 0 };
    int m_y { 1 };

public:
    Foo5(int x, int y)
    {
        m_x = x; // this is an assignment, not an initialization
        m_y = y;
    }
};


/* Default constructor

- A default constructor is a constructor that accepts no arguments.
*/

class Foo6
{
public:
    Foo6() // default constructor
    {
        std::cout << "Foo default constructed\n";
    }
};

void func5()
{
    Foo6 foo6{}; // No initialization values, calls Foo's default constructor
}


/* Value initialization vs default initialization for class types

- Both will call the default constructor. However, value initialization is safer.
  Since it’s difficult to tell whether a class type is an aggregate or non-aggregate.
  => just use value initialization for everything and not worry about it.
*/

void func6()
{
    Foo6 foo7; // default initialization, calls Foo() default constructor
    Foo6 foo8{}; // value initialization, calls Foo() default constructor, preferred
}


/* Overloaded constructors

- Because constructors are functions, they can be overloaded.
*/


/* An implicit default constructor

- If a non-aggregate class type object has no user-declared constructors,
  the compiler will generate a public default constructor that has no parameters, 
  no member initializer list, and no statements in the body of the constructor.

- The implicit default constructor is useful mostly when we have classes that have no data members.
*/


/* Explicitly defaulted default constructor

- ... in cases where we would write a default constructor that is equivalent 
  to the implicitly generated default constructor.
*/

class Foo7
{
private:
    int m_x {};
    int m_y {};

public:
    Foo7() = default; // generates an explicitly defaulted default constructor

    Foo7(int x, int y)
        : m_x { x }, m_y { y }
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
    }
};

void func7()
{
    Foo7 foo9{}; // calls Foo7() default constructor
}


/* Delegating constructors

- Constructors are allowed to delegate initialization to another constructor.

- Flow:
    1. initialization is delegated to another constructor:
        1.1. The member initializer list of the delegated constructor initializes the members.
        1.2. The body of the delegated constructor is executed.
    2. The body of the delegating constructor is executed.
*/

#include <string>
#include <string_view>

class Employee
{
private:
    std::string m_name { "???" };
    int m_id { 0 };

public:
Employee(std::string_view name)
        : Employee{ name, 0 } // delegate initialization to Employee(std::string_view, int) constructor
    {
    }
    
    Employee(std::string_view name, int id)
    : m_name{ name }, m_id { id }
    {
        std::cout << "Employee " << m_name << " created\n";
    }
};

void func8()
{
    Employee e1{ "James" };
    Employee e2{ "Dave", 42 };
}


int main()
{
    // Constructor
    func1();


    // Member initialization via a member initialization list
    func2();


    // Member initialization order
    func3();


    // Member initializer list vs default member initializers
    func4();


    // Default constructor
    func5();


    // Value initialization vs default initialization for class types
    func6();


    // Explicitly defaulted default constructor
    func7();


    // Delegating constructors
    func8();


    return 0;
}

/*
- Remind that normally a non-const member function can’t be invoked on a const object. 
  However, this is one exception: const doesn’t apply to an object under construction, 
  and only comes into effect after the constructor ends.
*/

/* Don't use ( ) for initialization

See: https://www.learncpp.com/cpp-tutorial/temporary-class-objects/#:~:text=Creating%20temporary%20objects%20via%20direct%20initialization
*/

/* References

- https://www.learncpp.com/cpp-tutorial/introduction-to-constructors/
- https://www.learncpp.com/cpp-tutorial/constructor-member-initializer-lists/
- https://www.learncpp.com/cpp-tutorial/default-constructors-and-default-arguments/
- https://www.learncpp.com/cpp-tutorial/delegating-constructors/
- https://www.learncpp.com/cpp-tutorial/temporary-class-objects/
*/