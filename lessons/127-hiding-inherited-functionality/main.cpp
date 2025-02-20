/* Changing an inherited member’s access level

- Perhaps surprisingly, given a set of overloaded functions in the base class, there is no way to change the access specifier for a single overload. You can only change them all.
*/

#include <iostream>

class Base1
{
private:
    int m_value {};

public:
    Base1(int value)
        : m_value { value }
    {
    }

protected:
    void printValue() const { std::cout << m_value; }
};

class Derived1: public Base1
{
public:
    Derived1(int value)
        : Base1 { value }
    {
    }

    // Base::printValue was inherited as protected, so the public has no access
    // But we're changing it to public via a using declaration
    using Base1::printValue;
};

void func1()
{
    Derived1 derived { 7 };

    // printValue is public in Derived, so we can call it here
    derived.printValue();
}


/* Hiding functionality

- In C++, it is not possible to remove or restrict functionality from a base class. However, you can hide it by changing the access specifier in the derived class.
- You can also mark member functions as deleted in the derived class, which ensures they can’t be called at all through a derived object.

- Note that the Base version of getValue() is still accessible though. We can call Base::getValue() in one of two ways:
*/

class Base2
{
private:
    int m_value {};

public:

	Base2(int value)
		: m_value { value }
	{
	}

	int getValue() const { return m_value; }
};

class Derived2 : public Base2
{
public:
	Derived2(int value)
		: Base2 { value }
	{
	}

	int getValue() const = delete; // mark this function as inaccessible using delete
};

int func2()
{
	Derived2 derived { 7 };

	std::cout << derived.getValue();    // won't work

	std::cout << derived.Base2::getValue(); // call the Base::getValue() function directly

	std::cout << static_cast<Base2&>(derived).getValue();   // call the Base::getValue() function by casting to a Base& (rather than a Base to avoid making a copy)

	return 0;
}


int main()
{
    // Changing an inherited member’s access level
    func1();

    // Hiding functionality
    func2();

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/hiding-inherited-functionality/
*/