/* function overloading

- function overloading: multiple functions with the same name, so long as each has different parameter types.
- Each function is called an "overloaded function" (or "overload" for short).
*/

/* How overloaded functions are differentiated

- Number of parameters
- Type of parameters

- Not consider: return type
*/

/* function’s type signature

= function name + number of parameters + parameter type + function-level qualifiers
*/

/* Name mangling

- When the compiler compiles a function, it performs name mangling, which means the 
  compiled name of the function is altered (“mangled”) so that the linker has unique names.
- For example, a function with prototype `int fcn()` might compile to mangled name `__fcn_v`,
   whereas `int fcn(int)` might compile to mangled name `__fcn_i`
   => the two overloaded functions share the name will have different mangled names.
*/

/* overload resolution

- With non-overloaded functions, there is only one function. That function either matches,
  or can be made to match after type conversions, or it doesn’t match.
- With overloaded functions, there can be many functions, a function call can only resolve to one of them.
  The process of matching function calls to a specific overloaded function is called "overload resolution".

For example, given overloads:
void print(int x);
void print(double x);

print('a'); // char does not match int or double, so what happens?
print(5L);  // long does not match int or double, so what happens?
*/

/* Resolving overloaded function calls

Steps:
1. The compiler tries to find an exact match. This includes "trivial conversions":
    Example 1:
        void foo(int);
        void foo(double);

        foo(5); // exact match with foo(int)
        foo(5.0); // exact match with foo(double)
    Example 2:
        void foo(const int);
        void foo(const double&); // reference to const double

        foo(5); // exact match with foo(const int) via trivial conversion
        foo(5.0); // exact match with foo(const double&) via trivial conversion

    Example 3:
        void foo(int);
        void foo(const int&);

        foo(5); // ambiguous match
2. If no exact match is found, the compiler tries to match by applying numeric promotion to the argument(s).
    Example:
        void foo(int);
        void foo(double);

        foo('a'); // promoted to match foo(int)
        foo(true); // promoted to match foo(int)
        foo(4.5f); // promoted to match foo(double)
3. If no match is found, the compiler tries to match by numeric conversion.
    Example:
        void foo(double);
        void foo(std::string);

        foo('a'); // 'a' converted to match foo(double)
4. If no match is found, the compiler tries to match by applying user-defined conversions (not covered yet).
5. If no match is found, the compiler will use ellipsis.
6. If no match is found, the compiler will report an error.
*/

/* Ambiguous matches

Example:
void foo(int);
void foo(double);

foo(5L); // ambiguous match at numeric conversion step.

How to resolve:
- Define new overloads that can exactly match.
- Or, explicitly cast the argument to the desired type.
*/

/* Matching for functions with multiple arguments

- the compiler applies the matching rules to each argument in turn.
- the function chosen must provide a better match than all the other candidate functions 
  for at least one parameter, and no worse for all of the other parameters.
*/


/* References

- https://www.learncpp.com/cpp-tutorial/introduction-to-function-overloading/
- https://www.learncpp.com/cpp-tutorial/function-overload-differentiation/
- https://www.learncpp.com/cpp-tutorial/function-overload-resolution-and-ambiguous-matches/
*/