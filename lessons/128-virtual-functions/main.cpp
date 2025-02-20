
#include <iostream>
#include <string_view>
#include <string>

/* Pointers and references to the base class of derived objects

- C++ will let us set a base pointer or reference to a derived object.
- a base reference and pointer can only see members of the base class.
  Consequently, pAnimal->speak() calls Animal::speak() rather than the Cat::speak() function.
*/

#include <iostream>
#include <string_view>

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

- But note that, Calling a virtual member function directly on an object (not through a pointer or reference) will always invoke 
  the member function belonging to the same type of that object.
  => Virtual function resolution only works when a member function is called through a pointer or reference to a class type object.

- if a function is marked as virtual, all matching overrides in derived classes are also implicitly considered virtual, 
  even if they are not explicitly marked as such.
*/


#include <iostream>
#include <string_view>

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

    // call a virtual function directly on an object (not through a pointer or reference)
    Base2 base { derived };     // copies the A portion of c into a
    std::cout << "base is a " << base.getName() << '\n';    // base is a Base, always calls Base::getName()
}


/* A warning: call virtual functions from constructors or destructors.

- When you create an object of a derived class, the base class constructor is called first.
  If you were to call a virtual function from the base class constructor, it will call the base class version of the function
  because the derived class part of the object has not been constructed yet for the derived class version of the function to work with.

- Similarly, when you destroy an object of a derived class, the derived portion of the object is destroyed first...
*/


int main()
{
    // Pointer and references to the base class of derived objects
    func1();


    // Virtual functions and polymorphism
    func2();

    return 0;
}


/* why not just make all functions virtual

- because it’s inefficient -- resolving a virtual function call takes longer than resolving a regular one.
- Furthermore, to make virtual functions work, the compiler has to allocate an extra pointer 
  for each object of a class that has virtual functions. This adds a lot of overhead to objects that otherwise have a small size. 
*/


/* References 

- https://www.learncpp.com/cpp-tutorial/pointers-and-references-to-the-base-class-of-derived-objects/
- https://www.learncpp.com/cpp-tutorial/virtual-functions/
 */