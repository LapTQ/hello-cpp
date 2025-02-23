/* dynamic_cast

- There are case where dynamic_cast fails. E.g., when b wasn’t pointing to a Derived object.
  In this case, the conversion cannot be made and dynamic_cast will return a null pointer.

- there are several cases where downcasting using dynamic_cast will not work:
    + With protected or private inheritance.
    + For classes that do not declare or inherit any virtual functions (and thus don’t have a virtual table).
    + In certain cases involving virtual base classes
*/

#include <iostream>
#include <string>
#include <string_view>

class Base
{
protected:
	int m_value{};

public:
	Base(int value)
		: m_value{value}
	{
	}

	virtual ~Base() = default;
};

class Derived : public Base
{
protected:
	std::string m_name{};

public:
	Derived(int value, std::string_view name)
		: Base{value}, m_name{name}
	{
	}

	const std::string& getName() const { return m_name; }
};

void func1()
{
	Base* b{ new Derived{1, "Apple"} };

	Derived* d{ dynamic_cast<Derived*>(b) }; // use dynamic cast to convert Base pointer into Derived pointer
    if (d) // make sure the conversion succeeded
		std::cout << "The name of the Derived is: " << d->getName() << '\n';

	delete b;
}


/* Downcasting with static_cast

- It turns out that downcasting can also be done with static_cast.
- Using static_cast is faster, but more dangerous. Because it does no runtime type checking,
  so it will “succeed” even if the Base pointer isn’t pointing to a Derived object.
*/


/* dynamic_cast and references

- dynamic_cast can also be used with references. This works analogously to how dynamic_cast works with pointers.
- If the conversion cannot be made, dynamic_cast will throw a std::bad_cast exception.
*/

void func2()
{
    Derived d{1, "Apple"};
    Base& b{ d };
    Derived& newD{ dynamic_cast<Derived&>(b) };
    std::cout << "The name of the Derived is: " << newD.getName() << '\n';
}


int main()
{
    // dynamic_cast
    func1();

    return 0;

}


/* dynamic_cast vs static_cast

- New programmers are sometimes confused about when to use static_cast vs dynamic_cast. 
- The answer is quite simple: use static_cast unless you’re downcasting.
*/


/* References

- https://www.learncpp.com/cpp-tutorial/dynamic-casting/
*/