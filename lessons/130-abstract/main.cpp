/* pure virtual function (or abstract function)

- To create a pure virtual function, we simply assign the function the value 0.

- A pure virtual function makes a class abstract, which means it cannot be instantiated.
*/

#include <iostream>
#include <string>
#include <string_view>

class Animal1 // This Animal is an abstract base class
{
protected:
    std::string m_name {};

public:
    Animal1(std::string_view name)
        : m_name{ name }
    {
    }

    const std::string& getName() const { return m_name; }
    virtual std::string_view speak() const = 0; // note that speak is now a pure virtual function

    virtual ~Animal1() = default;
};

class Cow1: public Animal1
{
public:
    Cow1(std::string_view name)
        : Animal1(name)
    {
    }

    std::string_view speak() const override { return "Moo"; }
};

void func1()
{
    Cow1 cow{ "Betsy" };
    std::cout << cow.getName() << " says " << cow.speak() << '\n';
}


/* Pure virtual functions with definitions

- When providing a definition for a pure virtual function, the definition must be provided separately (not inline).
- if the derived class is happy with the default implementation provided by the base class, it can simply call the base class implementation directly.
*/

#include <string>
#include <string_view>

class Animal2 // This Animal is an abstract base class
{
protected:
    std::string m_name {};

public:
    Animal2(std::string_view name)
        : m_name{ name }
    {
    }

    const std::string& getName() { return m_name; }
    virtual std::string_view speak() const = 0; // The = 0 means this function is pure virtual

    virtual ~Animal2() = default;
};

std::string_view Animal2::speak() const  // even though it has a definition
{
    return "buzz";
}

class Dragonfly: public Animal2
{

public:
    Dragonfly(std::string_view name)
        : Animal2{name}
    {
    }

    std::string_view speak() const override// this class is no longer abstract because we defined this function
    {
        return Animal2::speak(); // use Animal's default implementation
    }
};


/* Interface classes

*/

#include <string_view>

class IErrorLog
{
public:
    virtual bool openLog(std::string_view filename) = 0;
    virtual bool closeLog() = 0;
    virtual bool writeError(std::string_view errorMessage) = 0;

    virtual ~IErrorLog() {} // make a virtual destructor in case we delete an IErrorLog pointer, so the proper derived destructor is called
};


int main()
{
    // pure virtual function (or abstract function)
    func1();

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/pure-virtual-functions-abstract-base-classes-and-interface-classes/
*/