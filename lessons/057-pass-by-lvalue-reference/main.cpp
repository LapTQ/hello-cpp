/* Introduction

- why create an alias to a variable when you can just use the variable itself?

- In previous lessons, we discuss when an argument passed to a function by value,
  its value is copied. 
  Fortunately, because fundamental types are cheap to copy, this isn’t a problem.
- Class types (such as std::string) are usually expensive to copy.

- One way to avoid making an expensive copy of an argument when calling 
  a function is to use "pass by reference".
*/


/* Pass by reference

- Because the reference acts as an alias for the argument, 
  no copy of the argument is made.
- Binding a reference is always inexpensive.
*/

#include <iostream>
#include <string>

void printValue(std::string& y)
{
    std::cout << y << '\n';
}

void printAddresses(int val, int& ref)
{
    std::cout << "The address of the value parameter is: " << &val << '\n';
    std::cout << "The address of the reference parameter is: " << &ref << '\n';
}


/* Pass by reference allows us to change the value of an argument
*/

void addOne(int& y)
{
    ++y;
}


/* Pass by reference can only accept modifiable lvalue arguments,
   unless we make a reference parameter const

- Passing by const reference offers the same primary benefit 
  + as pass by non-const reference: avoiding making a copy of the argument)
  + as pass by value: can not change the value being referenced.

Warning: 
  + ensure the type of the argument matches the type of the reference, 
    or it will result in an unexpected (and possibly expensive) type conversion.
*/

void printValue(int& y) // y only accepts modifiable lvalues
{
    std::cout << y << '\n';
}

void printRef(const int& y) // y is a const reference
{
    std::cout << y << '\n';
}


/* For function parameters, prefer std::string_view over const std::string& in most cases

See: https://www.learncpp.com/cpp-tutorial/pass-by-const-lvalue-reference/#stringparameter:~:text=For%20function%20parameters%2C%20prefer%20std%3A%3Astring_view%20over%20const%20std%3A%3Astring%26%20in%20most%20cases
(or the table image:string_view-vs-string-ref.png)
*/

int main()
{
    // Pass by reference
    std::string x { "Hello, world!" };
    printValue(x); // inexpensive, lvalue reference parameter y is bound to argument x

    // check addresses
    int a { 5 };
    std::cout << "The address of a is: " << &a << '\n'; // 0x7ffd6abaa51c
    printAddresses(a, a); // 0x7ffd6abaa4dc and 0x7ffd6abaa51c


    // make a reference parameter const
    int b { 5 };
    const int c { 5 };
    printValue(b); // okay: b is a modifiable lvalue
    printValue(c); // error: c is a const lvalue
    printValue(6);   // error: 6 is an rvalue
    printRef(b);   // okay: b is a modifiable lvalue
    printRef(c);   // okay: c is a const lvalue
    printRef(6);   // okay: 6 is an rvalue

    return 0;
}


/* why we don’t just pass everything by reference

See: https://www.learncpp.com/cpp-tutorial/pass-by-const-lvalue-reference/#google_vignette:~:text=Object%20slicing).-,The%20cost%20of%20pass%20by%20value%20vs%20pass%20by%20reference,-Advanced
*/


/* Best practice

- pass fundamental types by value
- pass class types by const reference (or by reference if you need to change the value of an argument).
*/


/* References

- https://www.learncpp.com/cpp-tutorial/pass-by-lvalue-reference/
- https://www.learncpp.com/cpp-tutorial/pass-by-const-lvalue-reference/
*/