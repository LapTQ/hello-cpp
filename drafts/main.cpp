

#include <iostream>

class Base2
{
public:
    virtual std::string_view getName() const { return "Base"; } // note addition of virtual keyword
};

class Derived2: public Base2
{
public:
    virtual std::string_view getName() const { return "Derived"; }
};

int main()
{
    Derived2 derived {};
	std::cout << "rBase is a " << derived.getName() << '\n';

    // reference to the base class
    Base2& rBase{ derived };
    std::cout << "rBase is a " << rBase.getName() << '\n';  // rBase is a Derived

    
}