/*
- When instantiating a function template for a given type, a particular function will have the same implementation details for each instanced type.
- However, there are cases where you may want to provide a slightly different implementation for a specific type.

- One way to do this is to define a non-template function that takes the specific type as a parameter, like the print(double) function in the example below.
- Another way to achieve a similar result is to use "explicit template specialization".
*/

#include <iostream>

template <typename T>
void print1(const T& t)
{
    std::cout << t << '\n';
}

void print1(double d)
{
    std::cout << std::scientific << d << '\n';
}


/* Function template specialization


- if a matching non-template function and a matching template function specialization both exist, the non-template function will take precedence.
  In general, you should avoid function template specializations in favor of non-template functions whenever possible.
- Also, full specializations are not implicitly inline.
*/

#include <iostream>

// Here's our primary template (must come first)
template <typename T>
void print(const T& t)
{
    std::cout << t << '\n';
}

// A full specialization of primary template print<T> for type double
template<>                          // a template parameter declaration to tell compiler that we’re doing something related to templates
void print<double>(const double& d) // specialized for type double
{
    std::cout << std::scientific << d << '\n';
}


/* References

- https://www.learncpp.com/cpp-tutorial/function-template-specialization/
*/