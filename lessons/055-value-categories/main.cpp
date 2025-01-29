/* The properties of an expression

- all expressions in C++ have two properties: a type and a value category.

- The type of an expression: e.g., int, double, std::string, etc.
- The value category of an expression:
    Consider:
    ```
    x = 5; // valid
    5 = x; // invalid
    ```
    How does the compiler know which expressions can legally appear on 
    either side of the assignment statement?

    The answer is: value categories. It indicates whether an expression
    resolves to a value, a function, or something else.

    - Prior to C++11, there were only two value categories: lvalues and rvalues.
    - C++11 introduced 3 new value categories: xvalues, prvalues, and glvalues.

In this lesson, we’ll stick to the pre-C++11 view of value categories.
We will cover the new value categories in a future lesson.
*/

/* lvalue and rvalue

- An lvalue is an expression that evaluates to an identifiable object.
- A rvalue is an expression that evaluates to a value.
  Rvalues aren’t identifiable (meaning they have to be used immediately), 
  and only exist within the scope of the expression in which they are used. 

For example:
```
int x{ 5 }; // 5 is an rvalue expression
int y{ x }; // x is an lvalue expression

int return5()
{
    return 5;
}
int z{ return5() }; // return5() is an rvalue expression

int w{ x + 1 }; // x + 1 is an rvalue expression
```

- lvalues come in two subtypes: modifiable lvalues and non-modifiable lvalues.
    For example:
    ```
    int y { x }; // x is a modifiable lvalue expression
    const int z { x }; // x is a non-modifiable lvalue expression
    ```
*/

/* why x = 5 is valid but 5 = x is not?

- an assignment operation requires its left operand to be a modifiable lvalue expression,
  while 5 is an rvalue.
*/


/* Lvalue-to-rvalue conversion

- assignment operations expect the right operand to be an rvalue expression.
  But why the following code is valid?
  ```
  x = y; // y is not an rvalue, but this is legal
  ```

  Because, lvalue will undergo an implicit lvalue-to-rvalue conversion to produce an rvalue.

Another example, operator+ also expects its operands to be rvalues: e.g., 1 + 2.
*/


/* For advanced readers

- Unlike the other literals (which are rvalues), a C-style string literal is an lvalue 
  because C-style strings decay to a pointer.
*/


/* References

- https://www.learncpp.com/cpp-tutorial/value-categories-lvalues-and-rvalues/
*/