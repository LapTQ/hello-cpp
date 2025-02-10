/* void pointer

- also known as the generic pointer, is a special type of pointer that can be pointed at objects of any data type!
- void pointer must first be cast to another pointer type before the dereference.
*/

#include <iostream>

int main()
{
    int nValue {};
    double dValue { 5.5 };

    void* pValue {};
    pValue = &nValue;   // okay
    pValue = &dValue;   // okay 

    std::cout << *(static_cast<double*>(pValue)) << '\n';   // okay, must cast before dereference

    return 0;
}


/* References
- https://www.learncpp.com/cpp-tutorial/void-pointers/
*/