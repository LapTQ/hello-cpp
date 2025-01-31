/*
- In prior lessons, we’ve covered two different ways to pass an argument to a function: 
  pass by value and pass by reference.
- C++ provides a third way to pass values to a function, called "pass by address", via pointers.

- This pointer is copied into a pointer parameter of the called function.
  copying a pointer is always fast.

- Prefer pass by reference to pass by address unless you have a specific reason to use pass by address.
*/


#include <iostream>
#include <string>

void printByValue(std::string val)
{
    std::cout << val << '\n';
}

void printByReference(const std::string& ref)
{
    std::cout << ref << '\n';
}

void printByAddress(const std::string* ptr)
{
    std::cout << *ptr << '\n';
}


/* Pass by address… by reference

- we can also pass pointers by reference.
*/

void nullify(int*& refptr) // refptr is now a reference to a pointer
{
    refptr = nullptr; // Make the function parameter a null pointer
}

int main()
{
    std::string str{ "Hello, world!" };

    printByValue(str); // pass str by value, makes a copy of str
    printByReference(str); // pass str by reference, does not make a copy of str
    printByAddress(&str); // pass str by address, does not make a copy of str


    // Pass by address… by reference
    int x{ 5 };
    int* ptr{ &x };
    std::cout << ptr << '\n'; // print the address of x
    nullify(ptr); // pass ptr by reference
    std::cout << ptr << '\n'; // print nullptr

    return 0;
}


/* There is only pass by value

- Actually, references are normally implemented by the compiler using pointers.
- This means that behind the scenes, pass by reference is essentially just a pass by address.
- Therefore, we can conclude that C++ really passes everything by value!
*/

/* References

- https://www.learncpp.com/cpp-tutorial/pass-by-address/
- https://www.learncpp.com/cpp-tutorial/pass-by-address-part-2/
*/