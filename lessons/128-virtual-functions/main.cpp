
#include <iostream>
#include <string_view>
#include <string>

/* Pointers and references to the base class of derived objects

- C++ will let us set a base pointer or reference to a derived object.
- a base reference and pointer can only see members of the base class.
  Consequently, pAnimal->speak() calls Animal::speak() rather than the Cat::speak() function.
*/

class Base1
{
public:
    std::string_view getName() const { return "Base"; }
};

class Derived1: public Base1
{
public:
    std::string_view getName() const { return "Derived"; }
};

void func1()
{
    Derived1 derived {};

    // reference to the base class
    Base1& rBase{ derived };
    std::cout << "rBase is a " << rBase.getName() << '\n';      // rBase is a Base


    // pointer to the base class
    Base1* pBase{ &derived };
    std::cout << "pBase is a " << pBase->getName() << '\n';     // rBase is a Base

}


/* Virtual functions and polymorphism

- A virtual function, when called, resolves to the "most-derived" version of the function for the "actual type" of the object being referenced or pointed to.

- Object slicing: note that, Calling a virtual member function directly on an object (not through a pointer or reference) will always invoke 
  the member function belonging to the same type of that object.
  => Virtual function resolution only works when a member function is called through a pointer or reference to a class type object.

  if used improperly, object slicing can lead to Frankenobject.

- if a function is marked as virtual, all matching overrides in derived classes are also implicitly considered virtual, 
  even if they are not explicitly marked as such.
*/

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

void func2()
{
    Derived2 derived {};

    // reference to the base class
    Base2& rBase{ derived };
    std::cout << "rBase is a " << rBase.getName() << '\n';  // rBase is a Derived

    // Object slicing
    Base2 base { derived };     // copies the A portion of c into a
    std::cout << "base is a " << base.getName() << '\n';    // base is a Base, always calls Base::getName()

    // Frankenobject
    Derived2 d1 {};
    Derived2 d2 {};
    Base2& b{ d1 };
    b = d2; // you might assume that d2 is copied into d1
    // but what actually happens is that: because b is a Base, and operator= is not virtual by default,
    // only the Base part of d2 is copied into d1, while the Derived part of d1 remains unchanged.
    // => d1 is now a Frankenobject: composed of parts of multiple objects.
}


/* a derived class virtual function is only considered an override if its signature and return types match exactly.

=> That can lead to inadvertent issues: functions that are meant to be overrides but aren’t
*/

class A1
{
public:
	virtual std::string_view getName1(int x) { return "A"; }
	virtual std::string_view getName2(int x) { return "A"; }
};

class B1 : public A1
{
public:
	virtual std::string_view getName1(short x) { return "B"; } // note: parameter is a short
	virtual std::string_view getName2(int x) const { return "B"; } // note: function is const
};

void func3()
{
	B1 b{};
	A1& rBase{ b };
	std::cout << rBase.getName1(1) << '\n';     // A
	std::cout << rBase.getName2(2) << '\n';     // A
}


/* override specifiers

- ... to help address the issue of functions that are meant to be overrides but aren’t.
- If a function marked as override:
    + does not override a base class function
    + or is applied to a non-virtual function)
  the compiler will flag the function as an error.

- the override specifier implies virtual => no need to use both together.

- all virtual override functions should be tagged using the override specifier.
*/

class C1 : public A1
{
public:
	std::string_view getName1(short x) override { return "C"; } // compile error, function is not an override
	std::string_view getName2(int x) const override { return "C"; } // compile error, non-virtual member function cannot be marked as override
    std::string_view getName2(int x) override { return "C"; }
};


/* final specifier

- There may be cases where you don’t want someone to be able to override a virtual function, or inherit from a class.
*/

class A2
{
public:
	virtual std::string_view getName() const { return "A"; }
};

class B2 : public A2
{
public:
	std::string_view getName() const override final { return "B"; } // okay, overrides A::getName()
};

class C2 : public B2
{
public:
	std::string_view getName() const override { return "C"; } // compile error: overrides B::getName(), which is final
};

class D2 final : public A2 // note use of final specifier here
{
public:
	std::string_view getName() const override { return "D"; }
};

class E2 : public D2 // compile error: cannot inherit from final class
{
public:
	std::string_view getName() const override { return "E"; }
};


/* Covariant return types

- There is one special case in which a derived class virtual function override can have a different return type 
  than the base class and still be considered a matching override: when the return type of a virtual function 
  is a pointer or a reference to some class, override functions can return a pointer or a reference to a "derived" class
*/


class Base3
{
public:
	// This version of getThis() returns a pointer to a Base class
	virtual Base3* getThis() { std::cout << "called Base::getThis()\n"; return this; }
	void printType() { std::cout << "returned a Base\n"; }
};

class Derived3 : public Base3
{
public:
	// Normally override functions have to return objects of the same type as the base function
	// However, it's okay to return Derived* instead of Base* because Derived is derived from Base.
	Derived3* getThis() override { std::cout << "called Derived::getThis()\n";  return this; }
	void printType() { std::cout << "returned a Derived\n"; }
};

void func4()
{
	Derived3 d{};
	Base3* b{ &d };
	d.getThis()->printType(); // calls Derived::getThis(), returns a Derived*, calls Derived::printType
	b->getThis()->printType(); // calls Derived::getThis(), returns a Base*, calls Base::printType because printType is not virtual
}


/* Ignoring virtualization

- There may be cases where you want a Base pointer to a Derived object to call Base::getName() 
  instead of Derived::getName(). To do so, simply use the scope resolution operator:
*/

class Base5
{
public:
    virtual ~Base5() = default;
    virtual std::string_view getName() const { return "Base"; }
};

class Derived: public Base5
{
public:
    virtual std::string_view getName() const { return "Derived"; }
};

void func5()
{
    Derived derived {};
    const Base5& base { derived };

    // Calls Base::getName() instead of the virtualized Derived::getName()
    std::cout << base.Base5::getName() << '\n';

}


/* Slicing vectors

- To avoid slicing in a vector of objects, you can use pointers or references wrapper (because references are not reassignable).
*/

#include <vector>
#include <functional>

class Base6
{
public:
    virtual ~Base6() = default;
    virtual std::string_view getName() const { return "Base"; }
};

class Derived6: public Base6
{
public:
    virtual std::string_view getName() const { return "Derived"; }
};

void func6WithPointer()
{
    std::vector<Base6*> v;
    Derived6 d1;
    Derived6 d2;
    v.push_back(&d1);
    v.push_back(&d2);

    for (const auto& element : v)
    {
        std::cout << element->getName() << '\n';
    }
}

void func6WithReferenceWrapper()
{
    std::vector<std::reference_wrapper<Base6>> v;
    Derived6 d1;
    Derived6 d2;
    v.push_back(d1);
    v.push_back(d2);

    for (const auto& element : v)
    {
        std::cout << element.get().getName() << '\n';
    }
}


int main()
{
    // Pointer and references to the base class of derived objects
    func1();
    
    
    // Virtual functions and polymorphism
    func2();


    // a derived class virtual function is only considered an override if its signature and return types match exactly.
    func3();


    // covariant return types
    func4();


    // Slicing vectors
    func6WithPointer();
    func6WithReferenceWrapper();
    
    return 0;
}


/* A warning: call virtual functions from constructors or destructors.

- When you create an object of a derived class, the base class constructor is called first.
  If you were to call a virtual function from the base class constructor, it will call the base class version of the function
  because the derived class part of the object has not been constructed yet for the derived class version of the function to work with.

- Similarly, when you destroy an object of a derived class, the derived portion of the object is destroyed first...
*/


/* Virtual destructors

- Sometimes you will want to provide your own destructor (particularly if the class needs to deallocate memory).
  => Whenever you are dealing with inheritance, you should make any destructors virtual.
*/


/* Virtual assignment

- unlike the destructor case where virtualization is always a good idea, virtualizing the assignment operator 
  really opens up a bag full of worms and gets into some advanced topics outside of the scope of this tutorial.
*/


/* why not just make all functions virtual

- because it’s inefficient -- resolving a virtual function call takes longer than resolving a regular one.
- Furthermore, to make virtual functions work, the compiler has to allocate an extra pointer 
  for each object of a class that has virtual functions. This adds a lot of overhead to objects that otherwise have a small size. 
*/


/* References 

- https://www.learncpp.com/cpp-tutorial/pointers-and-references-to-the-base-class-of-derived-objects/
- https://www.learncpp.com/cpp-tutorial/virtual-functions/
- https://www.learncpp.com/cpp-tutorial/the-override-and-final-specifiers-and-covariant-return-types/
- https://www.learncpp.com/cpp-tutorial/virtual-destructors-virtual-assignment-and-overriding-virtualization/
- https://www.learncpp.com/cpp-tutorial/object-slicing/
 */