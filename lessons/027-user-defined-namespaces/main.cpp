/* The syntax for a namespace is as follows:

namespace NamespaceIdentifier
{
    // content of namespace here
}

- The best way to tell the compiler to look in a particular namespace for an identifier is to use the scope resolution operator (::).
- If :: is used without providing a namespace name (e.g. ::doSomething), the identifier (e.g. doSomething) is explicitly looked for in the global namespace.
- If :: not used, the compiler will first try to find a matching declaration in that same namespace. 
  If no matching identifier is found, the compiler will then check each containing namespace in sequence, with the global namespace being checked last.
*/

/* Multiple namespace blocks are allowed

- either across multiple files, or multiple places within the same file
*/

#include "add.h" // for BasicMath::add()
#include "circle.h" // for BasicMath::pi
#include <iostream>

void func1()
{
    std::cout << BasicMath::add(4, 3) << '\n';
    std::cout << BasicMath::pi << '\n';
}

// Nested namespaces
namespace Foo
{
    namespace Goo // Goo is a namespace inside the Foo namespace
    {
        int add(int x, int y)
        {
            return x + y;
        }
    }
}
// Since C++17, you can also use an equivalent syntax for nested namespaces:
// namespace Foo::Goo // Goo is a namespace inside the Foo namespace (C++17 style).
// It’s worth noting that namespaces in C++ were not originally designed as a way to implement hierarchy -- they were designed primarily to prevent naming collisions.

void func2()
{
    std::cout << Foo::Goo::add(1, 2) << '\n';
}

/* Namespace aliases

- One nice advantage of namespace aliases: If you ever want to move the functionality within Foo::Goo
  to a different place, you can just update the Active alias to reflect the new destination, rather than having to find/replace every instance of Foo::Goo.
*/

void func3()
{
    namespace Active = Foo::Goo; // namespace alias
    std::cout << Active::add(1, 2) << '\n';
}

int main()
{
    // multiple namespace blocks are allowed
    func1();

    
    // nested namespaces
    func2();


    // namespace aliases
    func3();

    return 0;
}

// Convention: Company or org :: project or library :: module (e.g. Foosoft::Foologger::Lang)

/* References

- https://www.learncpp.com/cpp-tutorial/user-defined-namespaces-and-the-scope-resolution-operator/
*/