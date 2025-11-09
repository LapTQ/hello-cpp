/*
- Much like variables, functions live at an assigned address in memory (making them lvalues).
- When a function is referred to by name (without parenthesis), 
  C++ converts the function into a function pointer 
*/

#include <iostream>

int foo() // code for foo starts at memory address 0x002717f0
{
    return 5;
}

void func1()
{
    foo(); // jump to address 0x002717f0
    std::cout << foo << '\n'; // print 1, because foo is converted to a function pointer
    // and << does not know how to print a function pointer, so it converts foo to a boolean value.
}


/* Pointers to functions

- The syntax is one of the ugliest things you will ever see in C++.
- Type of the function pointer must match the type of the function.
- Unlike fundamental types, C++ will implicitly convert a function into a function pointer if needed
*/

int goo() {
    return 6;
}

int hoo(int x) {
    return x;
}

void func2()
{
    int (*fcnPtr)();

    int (*fcnPtr2)(){ &foo }; // fcnPtr2 points to function foo
    fcnPtr2 = &goo; // fcnPtr2 now points to function goo

    int (*fcnPtr3)() { &hoo }; // error
    int (*fcnPtr4)(int) { &hoo }; // okay

    int (*fcnPtr5)(int) { hoo }; // okay, C++ will automatically convert hoo to a function pointer
    void* fcnPtr6 { hoo };        // error
}


/* Calling a function using a function pointer
*/

void func3()
{
    int (*fcnPtr2)(){ &foo }; // fcnPtr2 points to function foo

    (*fcnPtr2)(); // explicitly dereference
    fcnPtr2();    // implicitly dereference
}


/* callback functions
*/

void loo(int x, int y, bool (*fcnPtr)(int, int))    // or equivalently: void loo(int x, int y, bool fcnPtr(int, int)), but less preferred
{
    if (fcnPtr(x, y))
        std::cout << x << " is greater than " << y << '\n';        
    else
        std::cout << x << " is not greater than " << y << '\n';
}

bool moo(int x, int y)
{
    return x > y;
}

void func4()
{
    loo(3, 4, &moo); // okay
    loo(3, 4, moo);  // okay
}


/* Making function pointers prettier with type aliases
*/

using fcnPtrType = bool (*)(int, int);

void loo2(int x, int y, fcnPtrType fcnPtr)
{
    // ...
}


/* Using std::function

- ... An alternate method of defining and storing function pointers.
- note that std::function only allows calling the function via 
  implicit dereference (e.g. fcnPtr()), not explicit dereference (e.g. (*fcnPtr)()).
*/

#include <functional>
void loo3(int x, int y, std::function<bool(int, int)> fcnPtr) {}

using fcnPtrType2 = std::function<bool(int, int)>;  // type alias

int soo() {}

int zoo(int x) {}

void func5()
{
    std::function<int()> fcnPtr7 { &soo }; // function pointer that return in int and takes no arguments
    std::function fcnPtr8 { &zoo }; // okay, CTAD
}

/* Type inference for function pointers
*/

void func6()
{
    auto fcnPtr9 { &hoo }; 
}


int main()
{
    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/function-pointers/
*/