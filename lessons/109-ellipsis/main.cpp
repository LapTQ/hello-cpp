/* Ellipsis

- so far, the number of parameters a function will take must be known in advance.
- However, there are certain cases, C++ allows us to pass a variable number of parameters to a function.

Form:
```
return_type function_name(argument_list, ...)
```

- functions that use ellipsis must have at least one non-ellipsis parameter.
- The ellipsis must always be the last parameter in the function.
*/


/* ellipsis are dangerous, don't use them
*/

#include <iostream>
#include <cstdarg> // for ellipsis

double findAverage(int count, ...)
{
    int sum{ 0 };

    // We access the ellipsis through a va_list
    std::va_list list;

    // The second argument is the last non-ellipsis parameter.
    va_start(list, count);  // va_list now points to the first parameter in the ellipsis.

    // Loop through all the ellipsis values
    for (int arg{ 0 }; arg < count; ++arg)
    {
         // get the value of the parameter that va_list currently points to
         // The second argument is the type of the value
         sum += va_arg(list, int);  // va_arg() also moves the va_list to the next parameter in the ellipsis
    }

    // Cleanup the va_list when we're done.
    va_end(list);

    // va_start() can be called again any time we want to reset the va_list to point to the first parameter in the ellipses again.

    return static_cast<double>(sum) / count;
}

int main()
{
    std::cout << findAverage(5, 1, 2, 3, 4, 5) << '\n';
    std::cout << findAverage(6, 1, 2, 3, 4, 5, 6) << '\n';


    // ellipsis are dangerous, don't use them
    std::cout << findAverage(5, 1.0, 2, 3, 4, 5) << '\n';  // -3.28117e+08 

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/ellipsis-and-why-to-avoid-them/
*/