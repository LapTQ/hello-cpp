/* User-defined conversions

- In the below example, printFoo has a Foo parameter but we’re passing in 
  an argument of type int, which doesn’t match.
- the compiler will find a function that lets it convert int value 5 into a Foo object. 
  That function is the Foo(int) constructor.
*/


#include <iostream>

class Foo
{
private:
    int m_x{};
public:
    Foo(int x)  // allow implicit conversion from int to Foo
        : m_x{ x }
    {
    }

    int getX() const { return m_x; }
};

void printFoo(Foo f) // has a Foo parameter
{
    std::cout << f.getX() << '\n';
}


/* Only one user-defined conversion may be applied

- In the below example, `printEmployee("Joe");` will not compile because it requires
  two user-defined conversions: one from a C-style string literal to std::string_view, 
  and another from std::string_view to Employee.
- 
*/

#include <string>
#include <string_view>

class Employee
{
private:
    std::string m_name{};

public:
    Employee(std::string_view name)
        : m_name{ name }
    {
    }

    const std::string& getName() const { return m_name; }
};

void printEmployee(Employee e)
{
    std::cout << e.getName() << '\n';
}


/* When converting constructors go wrong and the explicit keyword

In the below example, what if we just want `print(5)` to print the number 5 without
being converted to a Dollars object. It might be better if our print(Dollars) function 
could only be called with a Dollars object, not any value that can be implicitly converted to a Dollars.

- Note that default constructors with no parameters or constructors that only accept multiple arguments
  can also undergo implicit conversions using with empty and multiple-argument lists initialization.
*/

class Dollars
{
private:
    int m_dollars{};

public:
    Dollars(int d)
        : m_dollars{ d }
    {
    }

    int getDollars() const { return m_dollars; }
};

void print(Dollars d)
{
    std::cout << "$" << d.getDollars() << '\n';
}

// - To address such issues, we can use the explicit keyword to tell the compiler 
//  that a constructor should not be used as a converting constructor:

class Dollars2
{
private:
    int m_dollars{};

public:
    explicit Dollars2(int d) // now explicit
        : m_dollars{ d }
    {
    }

    int getDollars() const { return m_dollars; }
};

void print2(Dollars2 d)
{
    std::cout << "$" << d.getDollars();
}

// Note that static_cast returns an object that is direct-initialized,
// so it will consider explicit constructors while performing the conversion


int main()
{
    // User-defined conversions
    printFoo(5); // we're supplying an int argument => conversion from `5` to `Foo { 5 }`
    // In C++17 onward, the copy is mandatorily elided. 
    // Parameter f is copy initialized with value 5, and no call to the copy constructor is required.


    // Only one user-defined conversion may be applied
    printEmployee("Joe");   // compile error: requires 2 user-defined conversions

    using namespace std::literals;
    printEmployee( "Joe"sv);    // okay, only 1 user-defined conversion from std::string_view to Employee

    printEmployee(Employee{ "Joe" }); // okay, only 1 user-defined conversion from C-style string literal to std::string_view


    // When converting constructors go wrong and the explicit keyword
    print(5); 
    print2(5); // compile error: cannot convert int to Dollars2
    print2(static_cast<Dollars2>(5)); // okay, explicit conversion

    return 0;
}


/* Best practices

- The following should not be made explicit:
    + Copy (and move) constructors
- The following are typically not made explicit:
    + Default constructors with no parameters
    + Constructors that only accept multiple arguments
    (but can still undergo implicit conversions using empty and multiple-argument lists)
- The following should usually be made explicit:
    + Constructors that accept a single argument
    + Constructors that accept multiple arguments where most or all of them have default values
*/

/* References

- https://www.learncpp.com/cpp-tutorial/converting-constructors-and-the-explicit-keyword/
*/