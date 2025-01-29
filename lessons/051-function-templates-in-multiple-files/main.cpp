/*

- a forward declaration of the function template is not enough
    For example:
    main.cpp
    ```
    template <typename T>
    T addOne(T x); // forward declaration

    int main()
    {
        std::cout << addOne(1) << '\n';
        return 0;
    }
    ```

    add.cpp
    ```
    template <typename T>
    T addOne(T x)
    {
        return x + 1;
    }
    ```

    When compile main.cpp, it assumes that addOne<int> exists elsewhere and will be linked in later.
    When compile add.cpp, there is no uses of this template so the compiler will not instantiate anything.
    => the linker is unable to connect the two.

Solution:
- put all the template code in a header (.h) file instead of a source (.cpp) file.

- There is not ODR violation because the ODR says that types, templates, inline functions, 
  and inline variables are allowed to have identical definitions in different files.
- functions implicitly instantiated from templates are implicitly inline.
*/

#include "add.h" // import the function template definition
#include <iostream>

int main()
{
    std::cout << addOne(1) << '\n';
    std::cout << addOne(2.3) << '\n';

    return 0;
}

/* References

- https://www.learncpp.com/cpp-tutorial/using-function-templates-in-multiple-files/
*/