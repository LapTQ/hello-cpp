/* C++ templates

- Unlike a normal definition (where all types must be specified).
- template code can be used with types that didn’t even exist when the template was written!

- The initial function template is called the "primary template".
  The functions generated from the primary template are called "specializations" (or "function instance").

- Function templates are not actually functions -- their code isn’t compiled or executed directly. 
  Instead, function templates have one job: to generate functions.
*/

#include <iostream>

// template parameter declaration
template <typename T> // tell the compiler: this is a template, and T is a type template parameter
T max(T x, T y)
{
    return (x < y) ? y : x;
}
// The scope of a template parameter declaration is strictly limited to the function template that follows.

void func1()
{
    std::cout << max<int>(1, 2) << '\n'; // instantiates and calls function max<int>(int, int)
    std::cout << max<int>(4, 3) << '\n';    // calls already instantiated function max<int>(int, int)
    std::cout << max<double>(1, 2) << '\n'; // instantiates and calls function max<double>(double, double)
}


/* Function template instantiation

- To use our max<T> function template, follow the syntax:
max<actual_type>(arg1, arg2);

the addition of the type in angled brackets is called a "template argument".

- The process of creating functions (with specific types) from function templates (with template types) is called "instantiation".
- Implicit instantiation: instantiated due to a function call.

- A function template is only instantiated the first time a function call is made in each translation unit. 
  Further calls to the function are routed to the already instantiated function.
*/



/* Template argument deduction

- In cases where the type of the arguments match the actual type we want, we do not need to specify the actual type.

- 2 ways:
    ++ consider only template function overloads (with the empty angled brackets): print<>
    ++ consider both template and non-template function overloads (with no angled brackets): print. In this case,
       the non-template function will be "preferred".
*/

// generic
template <typename T>
void print(T x) { std::cout << x; }

void print(bool x) { std::cout << std::boolalpha << x; }


void func2()
{
    print<bool>(true); // calls print<bool>(bool) -- prints 1
    std::cout << '\n';

    print<>(true);     // deduces print<bool>(bool) (non-template functions not considered) -- prints 1
    std::cout << '\n';

    print(true);       // calls print(bool) -- prints true
    // consider both template and non-template function overloads, but non-template function is preferred
    std::cout << '\n';
}



/* Function templates with non-template parameters

For example:
template <typename T>
int someFcn(T, double);
*/


/*
- we can disallow certain types from being used with a function template by using the "delete" specifier.
*/

template <typename T>
T addOne(T x)
{
    return x + 1;
}

template <>
const char* addOne(const char* x) = delete;
// addOne("Hello, world!"); // compile error


/* Beware function templates with modifiable static local variables

- each function instantiated from that template will have a separate version of the static local variable.
- This is rarely a problem if the static local variable is const. 
  But if the static local variable is one that is modified, the results may not be as expected.
*/

template <typename T>
void printIDAndValue(T value)
{
    static int id{ 0 };
    std::cout << ++id << ") " << value << '\n';
}

void func3()
{
    printIDAndValue(12);    // 1) 12
    printIDAndValue(13);    // 2) 13
    printIDAndValue(14.5);  // 1) 14.5
}


/* multiple template types

For example:
```
template <typename T>
T max(T x, T y)

max(2, 3.5);  // compile error
```

- T can only represent a single type.

- You might wonder why the compiler didn’t generate function max<double>(double, double) 
  and then use numeric conversion to type convert the int argument to a double?
- The answer is simple: type conversion is done only when resolving function overloads, 
  not when performing template argument deduction.

- Solution 1: Use static_cast
    ```
    max(static_cast<double>(2), 3.5);
    ```
    => awkward and hard to read.
- Solution 2: specify an explicit type template argument
    ```
    max<double>(2, 3.5);
    ```
    and let the implicit type conversion rules convert int argument to double argument.
- Solution 3: multiple template type parameters
    ```
    max2(2, 3.5)
    ```
    Narrowing conversion problem:
        - 2 will be converted to double
        - ((2 < 3.5) ? 3.5 : 2) will be 3.5, which is correct
        - but the return type is T, which is int, so 3.5 will be narrowed to 3.
    Fix:
        - return type deduction via `auto` keyword (max3 below)

        Note that:
            - a function with an auto return type needs to be fully defined before it can be used 
              (a forward declaration won’t suffice). If we need a function that can be forward declared, 
              we have to be explicit about the return type. In the case of max3, we can add further `std::common_type_t`:
                ```
                template <typename T, typename U>
                auto max4(T x, U y) -> std::common_type_t<T, U>;
                ```
*/

// Solution 3
template <typename T, typename U>
T max2(T x, U y)
{
    return (x < y) ? y : x;
    // the conditional operator (?:) requires that both operands have the same type.
}

// fix narrowing conversion problem
template <typename T, typename U>
auto max3(T x, U y)
{
    return (x < y) ? y : x;
}

// add return type deduction
template <typename T, typename U>
auto max4(T x, U y) -> std::common_type_t<T, U>
{
    return (x < y) ? y : x;
}

void func4()
{
    std::cout << max2(2, 3.5) << '\n'; // print 3, due to narrowing conversion problem
    std::cout << max3(2, 3.5) << '\n'; // print 3.5, correct
    std::cout << max4(2, 3.5) << '\n'; // print 3.5, correct
}


/* (C++20) Abbreviated function templates

- C++20 introduces a new use of the auto keyword:
```
auto max(auto x, auto y);
```
is equivalent to:
```
template <typename T, typename U>
auto max(T x, U y);
```
*/


/* Function templates may be overloaded
*/

template <typename T>
auto foo(T x, T y) {}

template <typename T, typename U>
auto foo(T x, U y) {}

template <typename T, typename U, typename V>
auto foo(T x, U y, V z) {}

void func5()
{
    foo(1.2, 3.4); // call foo<double>(), preferred over foo<int, double>() (prefer the stricter match)
    foo(1, 3.4);   // call foo<int, double>()
    foo(1, 2, 3);  // call foo<int, int, int>()
}


int main()
{   
    // function template
    func1();
    

    // Template argument deduction
    func2();


    // Beware function templates with modifiable static local variables
    func3();    


    // multiple template types
    func4();
    


    // Function templates may be overloaded
    

    return 0;
}


/* typename vs class

- keyword typename (preferred) or class can be used to declare "type template parameters"
- There is no difference between them in this context, but we prefer typename because it makes
  it clearer that any type (such as fundamental type) can be used, not just class types.
*/

/* References 

- https://www.learncpp.com/cpp-tutorial/function-templates/
- https://www.learncpp.com/cpp-tutorial/function-template-instantiation/
- https://www.learncpp.com/cpp-tutorial/function-templates-with-multiple-template-types/
*/