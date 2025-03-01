/* Rethrowing an exception (the wrong way)

- Remind: when we throw an exception, the thrown exception is copy-initialized from variable exception.
- In the example below, the re-thrown exception object is sliced.
*/

#include <iostream>
class Base
{
public:
    Base() {}
    virtual void print() { std::cout << "Base"; }
};

class Derived: public Base
{
public:
    Derived() {}
    void print() override { std::cout << "Derived"; }
};

int func1()
{
    try
    {
        try
        {
            throw Derived{};
        }
        catch (Base& b)
        {
            std::cout << "Caught Base b, which is actually a ";
            b.print();      // prints "Derived"
            std::cout << '\n';
            throw b; // the Derived object gets sliced here
        }
    }
    catch (Base& b)
    {
        std::cout << "Caught Base b, which is actually a ";
        b.print();    // prints "Base"!!!
        std::cout << '\n';
    }

    return 0;
}


/* Rethrowing an exception (the right way)

- simply use the throw keyword from within the catch block (with no associated variable)
*/

int func2()
{
    try
    {
        try
        {
            throw Derived{};
        }
        catch (Base& b)
        {
            std::cout << "Caught Base b, which is actually a ";
            b.print();
            std::cout << '\n';
            throw; // note: We're now rethrowing the object here
        }
    }
    catch (Base& b)
    {
        std::cout << "Caught Base b, which is actually a ";
        b.print();
        std::cout << '\n';
    }

    return 0;
}


int main()
{
    // Re-throwing an exception (the wrong way)
    func1();


    // Re-throwing an exception (the right way)
    func2();

    return 0;
}

/* References

- https://www.learncpp.com/cpp-tutorial/rethrowing-exceptions/
*/