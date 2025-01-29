/* C++ templates

- Unlike a normal definition (where all types must be specified).
- template code can be used with types that didn’t even exist when the template was written!

- The initial function template is called the "primary template".
  The functions generated from the primary template are called "specializations" (or "function instance").

- Function templates are not actually functions -- their code isn’t compiled or executed directly. 
  Instead, function templates have one job: to generate functions.
*/


// template parameter declaration
template <typename T> // tell the compiler: this is a template, and T is a type template parameter
T max(T x, T y)
{
    return (x < y) ? y : x;
}
// The scope of a template parameter declaration is strictly limited to the function template that follows.


/* Function template instantiation

- To use our max<T> function template, follow the syntax:
max<actual_type>(arg1, arg2);

the addition of the type in angled brackets is called a "template argument".

- The process of creating functions (with specific types) from function templates (with template types) is called "instantiation".
- Implicit instantiation: instantiated due to a function call.

- A function template is only instantiated the first time a function call is made in each translation unit. 
  Further calls to the function are routed to the already instantiated function.
*/

#include <iostream>


/* Template argument deduction

- In cases where the type of the arguments match the actual type we want, we do not need to specify the actual type.

- 2 ways:
    ++ consider only template function overloads (with the empty angled brackets): print<>
    ++ consider both template and non-template function overloads (with no angled brackets): print. In this case,
       the non-template function will be "preferred".
*/

// generic
template <typename T>
void print(T x)
{
    std::cout << x;
}

// specialize how to handles printing of a bool
void print(bool x)
{
    std::cout << std::boolalpha << x;
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


int main()
{
    std::cout << max<int>(1, 2) << '\n'; // instantiates and calls function max<int>(int, int)
    std::cout << max<int>(4, 3) << '\n';    // calls already instantiated function max<int>(int, int)
    std::cout << max<double>(1, 2) << '\n'; // instantiates and calls function max<double>(double, double)


    // Template argument deduction
    print<bool>(true); // calls print<bool>(bool) -- prints 1
    std::cout << '\n';

    print<>(true);     // deduces print<bool>(bool) (non-template functions not considered) -- prints 1
    std::cout << '\n';

    print(true);       // calls print(bool) -- prints true
    // consider both template and non-template function overloads, but non-template function is preferred
    std::cout << '\n';


    // Beware function templates with modifiable static local variables
    printIDAndValue(12);    // 1) 12
    printIDAndValue(13);    // 2) 13
    printIDAndValue(14.5);  // 1) 14.5

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
*/