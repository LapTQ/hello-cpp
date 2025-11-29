/* throw, try, and catch

- In C++, a throw statement is used to signal that an exception or error case has occurred.
- You can any data type you wish. For example:
    ```
    throw -1; // throw a literal integer value
    throw ENUM_INVALID_INDEX; // throw an enum value
    throw "Can not take square root of negative number"; // throw a literal C-style (const char*) string
    throw dX; // throw a double variable that was previously defined
    throw MyException("Fatal Error"); // Throw an object of class MyException
    ```

- The catch keyword is used to define a block of code hat handles exceptions for a single data type.
  For example:
  ```
  catch (int x)
    {
        // Handle an exception of type int here
    }
- exceptions of non-fundamental types should be caught by const reference to avoid making an unnecessary copy.
    For example:
    ```
    catch (const MyException& e)
        {
            // Handle an exception of type MyException here
        }
    ```
- Just like with functions, if the parameter is not going to be used in the catch block, the variable name can be omitted:
    ```
    catch (int)
        {
            // Handle an exception of type int here
        }
    ```
*/


/* stack unwinding

- when a function throws an exception, the program will look for a catch block that can handle the exception.
- if a handler is not found in the current function, it will look in the calling function and so on up the call stack
  until it finds a catch block that can handle the exception, or no handler can be found.
- If a matching handler is found, the stack is unwound.
- If no handler is found, the stack might or might not be unwound.
    => local variables will not be destroyed => any cleanup expected upon destruction of said variables will not happen!!!
    => Fortunately, C++ also provides us with a mechanism to catch all types of exceptions: catch-all handler.
*/


#include <iostream>

int func1()
{
	try
	{
		throw 5; // throw an int exception
	}
	catch (double x)
	{
		std::cout << "We caught an exception of type double: " << x << '\n';
	}
	catch (...) // catch-all handler
	{
		std::cout << "We caught an exception of an undetermined type\n";
	}
}


/* Debugging unhandled exceptions

- if we have a catch-all handler, then we might lose useful diagnostic information.
- Therefore, in debug builds, it can be useful to disable the catch-all handler with the following template:
  ...
  Syntactically, a try block requires at least one associated catch block => we create a dummy class that can't be instantiated
  to satisfy the compiler.
*/

#include <iostream>

void runGame()
{
    throw 1;
}

class DummyException // a dummy class that can't be instantiated
{
    DummyException() = delete;
};

int func2()
{

    try
    {
        runGame();
    }
#ifndef NDEBUG // if we're in release node
    catch(...) // compile in the catch-all handler
    {
        std::cerr << "Abnormal termination\n";
    }
#else // in debug mode, compile in a catch that will never be hit (for syntactic reasons)
    catch(DummyException)
    {
    }
#endif

    return 0;
}


/* Catch-all handlers

- C++ also provides us with a mechanism to catch all types of exceptions
*/


/* If a constructor must fail for some reason, simply throw an exception
...  in such a case, the object’s construction is aborted, and all class members (which have "already been created" and initialized prior to the body of the constructor executing) 
    are destructed as per usual.
    However, the class’s destructor is never called (because the object never finished construction). 
    This leads to the question of what we should do if we’ve allocated resources in our constructor and then an exception occurs prior to the constructor finishing?
    1. Solution 1: wrap any code that can fail in a try block. But this adds a lot of clutter.
    2. Solution 2: wrap the resource allocations inside a class member (because (recall that) class members are destructed if the constructor fails). However, creating a custom class like to manage a resource allocation isn’t efficient.
    3. Solution 3: use RAII-compliant classes such as files (std::fstream), smart pointers (std::unique_ptr, ...).
*/


/* Exceptions and inheritance

- exception handler will also match classes derived from the exception class.
*/

#include <iostream>

class Base1
{
public:
    Base1() {}
};

class Derived2: public Base1
{
public:
    Derived2() {}
};

int main()
{
    try
    {
        throw Derived2();
    }
    catch (const Base1& base)   // Catch here
    {
        std::cerr << "caught Base";
    }
    catch (const Derived2& derived)
    {
        std::cerr << "caught Derived";
    }

    return 0;
}


/* std::exception

- Many of the classes and operators in the standard library throw exception classes on failure.
  e.g.: std::bad_alloc, std::bad_cast, ...
- all of these exception classes are derived from a single class called std::exception.
*/

int func3()
{
    try
    {
        throw std::runtime_error("An error occurred");
    }
    catch (const std::exception& e)
    {
        std::cerr << "Caught an exception: " << e.what() << '\n';
    }
}


/* The lifetime of exceptions

- The object being thrown is typically a temporary object or a local variable.
  But recall that when a function throws an exception, the stack is unwound, causing all variables local to the function to be destroyed.
  So how can the object being thrown persist after the function has been exited?
- The answer is that the object is copied to some piece of memory (outside the stack).
  => the object being thrown generally need to be copyable. 
*/


/* References

- https://www.learncpp.com/cpp-tutorial/the-need-for-exceptions/
- https://www.learncpp.com/cpp-tutorial/basic-exception-handling/
- https://www.learncpp.com/cpp-tutorial/uncaught-exceptions-catch-all-handlers/
- https://www.learncpp.com/cpp-tutorial/exceptions-classes-and-inheritance/
- https://www.learncpp.com/cpp-tutorial/exception-dangers-and-downsides/
*/