/* 
- when you redefine a function in the derived class, the derived function does not inherit the access specifier of the function in the base class.
*/

#include <iostream>

class Base1
{
private:
	void print() const
	{
		std::cout << "Base";
	}
};

class Derived1 : public Base1
{
public:
	void print() const
	{
		std::cout << "Derived\n";
	}
};


void func1()
{
	Derived1 derived {};
	derived.print(); // calls derived::print(), which is public
}


/* Adding to existing functionality

- Regarding a call to friend functions in base classes, such as operator<< below.
  we need a way to make our Derived class temporarily look like the Base class so that the right version of the function can be called.
*/

#include <iostream>

class Base2
{
public:
    Base2() { }

    void identify() const { std::cout << "Base::identify()\n"; }

    friend std::ostream& operator<< (std::ostream& out, const Base2&)
    {
        out << "In Base\n";
        return out;
    }
};

class Derived2: public Base2
{
public:
    Derived2() { }

    void identify() const
    {
        std::cout << "Derived::identify()\n";
        Base2::identify(); // note call to Base::identify() here
    }
    
    friend std::ostream& operator<< (std::ostream& out, const Derived2& d)
    {
       out << "In Derived\n";
       // static_cast Derived to a Base object, so we call the right version of operator<<
       out << static_cast<const Base2&>(d);
       return out;
    }
};

void func2()
{
    Derived2 derived {};
    derived.identify();
    std::cout << derived << '\n';
}


/* Overload resolution in derived classes

- When a member function is called on a derived class object:
    + first, all overloaded functions in the same class with that name are considered.
    + if no overloaded functions are found, the search continues in the base class.

In the example Derived3 below, d.print(5) calls Derived::print(double), not Base::print(int).
What if we want to call Base::print(int) instead?
    + Option 1: 
        ```
        void print(int n) { Base::print(n); } // works but not great, as we have to define
        ```
    + Option 2:
        ```
        using Base::print; // this tells the compiler to consider all Base::print functions when resolving print => Base::print(int) is selected over Derived::print(double).
        ```
*/

class Base3
{
public:
    void print(int)    { std::cout << "Base::print(int)\n"; }
    void print(double) { std::cout << "Base::print(double)\n"; }
};

class Derived3: public Base3
{
public:
    void print(double) { std::cout << "Derived::print(double)\n"; } // this function added
};

class Derived4: public Base3
{
public:
    using Base3::print; 
    void print(double) { std::cout << "Derived::print(double)\n"; }
};


void func3()
{
    Derived3 d{};
    d.print(5); // calls Derived::print(double), not Base::print(int)

    Derived4 d2{};
    d2.print(5); // calls Base::print(int)
}


int main()
{
    func1();
    func2();
    func3();

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/adding-new-functionality-to-a-derived-class/
- https://www.learncpp.com/cpp-tutorial/calling-inherited-functions-and-overriding-behavior/
*/