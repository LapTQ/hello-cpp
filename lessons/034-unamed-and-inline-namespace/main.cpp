/* Unnamed namespace

- All content declared in an unnamed namespace is treated as if it is part of the parent namespace.
- Other effect of unnamed namespace (notable): all identifiers inside an unnamed namespace are treated as if they have internal linkage.
  => can’t be seen outside of the file.
  => this is effectively the same as defining "all" functions in the unnamed namespace as `static` functions. 

Use cases:
- When we want to make all declarations to have internal linkage without having to declare all of them as static.
*/

#include <iostream>

namespace // unnamed namespace
{
    void doA() // can only be accessed in this file
    {
        std::cout << "v1\n";
    }
}
// equivalent to:
// static void doA()
// ...

void func1()
{
    doA(); // we can call doA() without a namespace prefix
}


/* Inlide namespace

- Much like an unnamed namespace, anything declared inside an inline namespace is considered part of the parent namespace.
- The difference is that an inline namespace can be versioned (notable).

Use case:
- An inline namespace is a namespace that is typically used to version content.
  For example, in the below code, we can switch the doSomething() function between V1 and V2 by placing `inline` before the preferred version. 
*/



inline namespace V1 // declare an inline namespace named V1, an unqualified call to doSomething() will call the V1 version
{
    void doSomething()
    {
        std::cout << "V1\n";
    }
}

namespace V2 // declare a normal namespace named V2
{
    void doSomething()
    {
        std::cout << "V2\n";
    }
}

int main()
{
    // unnamed namespace
    func1();

    // using inline namespace
    V1::doSomething(); // calls the V1 version of doSomething()
    V2::doSomething(); // calls the V2 version of doSomething()
    doSomething(); // calls the inline version of doSomething() (which is V1)

    return 0;
}