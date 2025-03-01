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


/* Class template specialization

- Class template specializations are treated as completely independent classes, 
  even though they are instantiated in the same way as the templated class.
  This means that we can change anything, including the way it’s implemented and even the functions it makes public.
*/

#include <cstdint>

template <typename T>
class Storage8_1
{
private:
    T m_array[8];

public:
    void set(int index, const T& value)
    {
        m_array[index] = value;
    }

    const T& get(int index) const
    {
        return m_array[index];
    }
};

// Specialized for bool
template <>
class Storage8_1<bool>
{

private:
    std::uint8_t m_data{};  // use an unsigned 8-bit integer instead of an array of bools

public:
    void set(int index, bool value)
    {
        auto mask{ 1 << index };

        if (value)
            m_data |= mask;
        else
            m_data &= ~mask;
	}

    bool get(int index)
    {
        auto mask{ 1 << index };
        return (m_data & mask);
    }
};


/* Specializing member functions

- Explicit function specializations are not implicitly inline, so make this inline if put in header file
*/

#include <iostream>

template <typename T>
class Storage2
{
private:
    T m_value {};
public:
    Storage2(T value)
      : m_value { value }
    {
    }

    void print()
    {
        std::cout << m_value << '\n';
    }
};

// This is a specialized member function definition
template<>
void Storage2<double>::print()
{
    std::cout << std::scientific << m_value << '\n';
}

int func2()
{
    // Define some storage units
    Storage2 i { 5 };
    Storage2 d { 6.7 }; // will cause Storage<double> to be implicitly instantiated

    // Print out some values
    i.print(); // calls Storage<int>::print (instantiated from Storage<T>)
    d.print(); // calls Storage<double>::print (called from explicit specialization of Storage<double>::print())
}


/* Partial template specialization

- as of the time of writing (C++23) functions cannot be partially specialized, only classes can be partially specialized.

Read: 
- https://www.learncpp.com/cpp-tutorial/partial-template-specialization/
- https://www.learncpp.com/cpp-tutorial/partial-template-specialization-for-pointers/
*/


int main()
{
    func2();

    return 0;
}


/* Where to define class template specializations

- In order to use a specialization, the compiler must be able to see the full definition of both the non-specialized class and the specialized class.
  => If can only see the definition of the non-specialized class, it will use that instead of the specialization.
- For this reason, specialized classes and functions are often defined in a header file just below the definition of the non-specialized class.
*/



/* References

- https://www.learncpp.com/cpp-tutorial/function-template-specialization/
- https://www.learncpp.com/cpp-tutorial/class-template-specialization/
- https://www.learncpp.com/cpp-tutorial/partial-template-specialization/
- https://www.learncpp.com/cpp-tutorial/partial-template-specialization-for-pointers/
*/