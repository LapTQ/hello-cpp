/* Why You Should Avoid std::vector<bool>
*/

/* 1. It's Not a Real Container and can breaks generic code

- The C++ standard explicitly calls out vector<bool> as a special container where each bool 
  uses only one bit of space rather than one byte as a normal bool would => you can't take the address of a bit within a byte.
- => things such as operator[] can't return a bool&, which means you can't assign its address to a bool* like you could with
  the other "normal" container.

Read: https://stackoverflow.com/questions/17794569/why-isnt-vectorbool-a-stl-container
*/

#include <vector>
#include <iostream>

void process(bool& value) {
    value = !value;
}

int func1() {
    // This works fine with vector<int>
    std::vector<int> v_int = {1, 2, 3};
    int& ref = v_int[0];  // ✅ OK
    int* ptr = &v_int[0]; // ✅ OK
    
    // This FAILS with vector<bool>
    std::vector<bool> v_bool = {true, false, true};
    bool& ref = v_bool[0];  // ❌ Compilation error!
    bool* ptr = &v_bool[0]; // ❌ Compilation error!
    
    // This breaks generic code
    process(v_bool[0]);  // ❌ Won't compile
    
    return 0;
}

/* 2. Performance Issues

- performance depends heavily on how well the implementation is optimized. Some implementations can be slower than alternatives.
*/


/* What Should You Use Instead?

- Option 1: std::vector<char> (Most Common)
*/

void func2()
{
    std::vector<char> v = {true, false, true};
    char& ref = v[0];     // ✅ Works!
    char* ptr = &v[0];    // ✅ Works!
}


/* References

- https://www.learncpp.com/cpp-tutorial/stdvector-bool/
*/