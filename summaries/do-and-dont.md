

## Print newline: use `"\n"` instead of `std::endl`
Do:
```C++
std::cout << "\n";
```
Don't:
```C++
std::cout << std::endl; // flushes the buffer, which is slower
```

## Don't use comma operator, except in `for` loops

Don't:
```C++
std::cout << (++x, ++y) << '\n'; // increment x and y, evaluates to the right operand
```

Don't:
```C++
z = (x, y); // evaluate (a, b) first to get result of b, then assign that value to variable z.
z = x, y; // evaluates as "(z = a), b", so z gets assigned the value of a, and b is evaluated and discarded.
```

Note that comma has the lowest precedence of all the operators, even lower than assignment.


## Macro


* Avoid using **object-like macros with substitution text**, as better methods are available.
