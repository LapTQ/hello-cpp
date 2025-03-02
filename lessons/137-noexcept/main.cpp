/* noexcept

- Looking at a typical function declaration, it is not possible to determine 
  whether a function might throw an exception or not:
    ```
    int doSomething();
    ```
  But the answer is important in some contexts.

- In C++, all functions are classified as either "non-throwing" or "potentially throwing". 
- To define a function as non-throwing, we can use the "noexcept" specifier.
    ```
    void doSomething() noexcept;
    ```

- Note that noexcept doesn’t actually prevent the function from throwing exceptions,
  so long as the noexcept function catches and handles those exceptions "internally".
  Otherwise, std::terminate will be called.

The noexcept specifier has an optional Boolean parameter:
  + noexcept(true) is equivalent to noexcept
  + noexcept(false) means the function is potentially throwing.
*/


/* The noexcept operator

- The noexcept operator is checked statically at compile-time, and doesn’t actually evaluate the input expression.
*/

void foo() {throw -1;}
void boo() {};
void goo() noexcept {};
struct S{};

void func2()
{
    constexpr bool b1{ noexcept(5 + 3) }; // true; ints are non-throwing
    constexpr bool b2{ noexcept(foo()) }; // false; foo() throws an exception
    constexpr bool b3{ noexcept(boo()) }; // false; boo() is implicitly noexcept(false)
    constexpr bool b4{ noexcept(goo()) }; // true; goo() is explicitly noexcept(true)
    constexpr bool b5{ noexcept(S{}) };   // true; a struct's default constructor is noexcept by default
}


/* Exception safety guarantees

- ... is a contractual guideline about how functions or classes will behave when an exception occurs.
- There are four levels:
    + No guarantee: no guarantees about what will happen if an exception is thrown.
    + Basic guarantee: if an exception is thrown, no memory will be leaked and the object is still usable, 
      but the program may be left in a modified state.
    + Strong guarantee: If an exception is thrown, no memory will be leaked and the program state will not be changed. 
        => function must either completely succeed or have no side effects if it fails. 
    + No throw / No fail guarantee: the function will never throw an exception to the caller (may throw internally).
      The noexcept specifier is used to indicate this guarantee.
*/


/* When to use noexcept

Read: https://www.learncpp.com/cpp-tutorial/exception-specifications-and-noexcept/#:~:text=When%20to%20use%20noexcept

For your own code, always mark the following as noexcept:
+ Move constructors
+ Move assignment operators
+ Swap functions

For your code, consider marking the following as noexcept:
+ Functions which you want to express a no-throw or no-fail guarantee (e.g., to document that they can be safely called from destructors or other noexcept functions)
+ Copy constructors and copy assignment operators that are no-throw (to take advantage of optimizations).
+ Destructors. Destructors are implicitly noexcept so long as all members have noexcept destructors
*/



/* References

- https://www.learncpp.com/cpp-tutorial/exception-specifications-and-noexcept/
*/