/* Lambdas are anonymous functions

Syntax:
```
[ captureClause ] ( parameters ) -> returnType
{
    statements;
}
```
- The capture clause can be empty if no captures are needed.
- The return type is optional, and if omitted, auto will be assumed.
- lambdas (being anonymous) can have no name.
  If we defined a lambda right where it was needed, this use of a lambda is sometimes called a "function literal".

- In actuality, lambdas aren’t functions (which is part of how they avoid the limitation of C++ not supporting nested functions).
- They’re a special kind of object called a functor.
  Functors are objects that contain an overloaded operator() that make them callable like a function.
*/

void foo(int x, int (*fcn)(int))
{
    fcn(x);
}

void func1()
{
    int x{ 7 };
    int y{};
    
    // lambda can have no name
    y = [](int a) -> int { return a * 2; }(x);  // y = 14

    foo(x, [](int a) -> int { return a * 2; });

}

/* Give lambda a name

3 options:
=> use auto
*/

// Option 1: using auto
void func2()
{
    int x{ 7 };
    int y{};

    auto doubleValue{
        [](int a) 
        { 
            return a * 2; 
        }
    };
    y = doubleValue(x);  // y = 14
}

// Option 2: a regular function pointer, only work for lambda with no capture
void func3()
{
    int (*doubleValue2)(int) {
        [](int a) 
        { 
            return a * 2; 
        }
    };
}

// Option 3: using std::function
#include <functional>
void func4()
{
    std::function<int(int)> doubleValue3{
        [](int a) 
        { 
            return a * 2; 
        }
    };
}


/* Pass a lambda to a function

4 options:
...

=> use std::function (Option 1) or template (Option 2) 
*/

#include <functional>

// Option 1: use std::function
void sol1(int x, const std::function<int(int)>& fcn)    // add some overhead to implicitly covert lambda to std::function
{
    fcn(x);
}

// Option 2: use template
template <typename T>
void sol2(int x, T& fcn)
{
    fcn(x);
}

// (C++20) Option 3: using auto
void sol3(int x, const auto& fcn)
{
    fcn(x);
}

// Option 4: only work for lambda with no capture
void sol4(int x, int (*fcn)(int))
{
    fcn(x);
}

void func5()
{
    int x{ 7 };
    auto doubleValue{
        [](int a) {  return a * 2; }
    };

    sol1(x, doubleValue);
    sol2(x, doubleValue);
    sol3(x, doubleValue);
    sol4(x, doubleValue);
}


/* Generic lambdas (C++14)

- Lamdas’re allowed to use auto for parameters.
*/


/* Constexpr lambdas

- As of C++17, lambdas are implicitly constexpr if:
    + The lambda must either have no captures, or all captures must be constexpr.
    + The functions called by the lambda must be constexpr.
*/


/* Generic lambdas and static variables

- In lambda, static variables work exactly the same as regular functions.
- a unique lambda will be generated for each different type that auto resolves to.
*/


int main()
{   
}


/* References

- https://www.learncpp.com/cpp-tutorial/introduction-to-lambdas-anonymous-functions/
*/