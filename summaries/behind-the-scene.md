

## How `std::cin >>` works (simplified)

1. First, leading whitespace is discared from the input buffer.
2. If the input buffer is now empty, `>>` will wait for the user input. Leading whitespace is again discarded.
3. `>>` then extracts as many consecutive characters as it can, until it encounters either a newline character or a character that is not valid for the variable being extracted to.

    If no characters could be extracted in this step, e.g. typing a non-digit `a` character 
    for an int `y`, 3 things happen at this point:
    * the object being extracted to is assigned the value 0 (as of C++11)
    * `a` is left in the input buffer
    * `std::cin` goes into “failure mode” (until the `clear()` function is called): any requests for further extraction are ignored. This means that instead waiting for us to enter an operation, the input prompt is silently skipped.
4. Any non-extracted characters (including newlines) remain available for the next extraction attempt.


## Compiling and naming collision

* If the colliding identifiers are introduced into the same file, the result will be a compiler error. 
* If the colliding identifiers are introduced into separate files belonging to the same program, the result will be a linker error.
* When the compiler compiles this program, it will compile each file (e.g., a.cpp and main.cpp) independently, and each file will compile with no problems.
    
    However, when the linker executes, it will link all the definitions in a.cpp and main.cpp together, and discover conflicting definitions for function myFcn().


## Preprocessor

* Prior to compilation, each code file goes through a preprocessing phase.
* A ***translation unit*** is a single file after it has been preprocessed, and before it is compiled.
* When the preprocessor runs, it processes the code file from top to bottom, looking for ***preprocessor directives*** (lines that start with `#`):
    * `#include`: replaces the directive with the contents of the specified file.
    * `#define`: 2 types: object-like macros and function-like macros.


## Scope of directives

* an `#include` can "copy" directives (other `#include` and `#define`) from the included file into the current file.

    => if you `#define` a macro in a header file, and `#include` the header file in a source file, the macro will be available in the source file. 
* Directives are only valid from the point of definition to the end of the file in which they are defined.
    
    => directives defined in one file do not carry over to other files that are compiled separately (unless they are #included in those files).


## One-Definition Rule (ODR)

* A variable or function identifier can only have one definition (not declaration).
* But types (including program-defined types) are exempt from the part of the ODR. For example:
    * Including a given type definitions into multiple translation units does not violate ODR, but
    * Including a given type definition more than once into a single translation unit is still violates ODR (=> still need header guards).


## Fundamental data types

* C++ standard does not define the exact size (in bits) of any of the fundamental types.
* WARNING: `std::int8_t` and `std::uint8_t` typically behave like chars.
* The fixed-width integers actually don’t define new types -- they are just aliases for existing integral types.
* Types that use less memory are not sure to be faster than types that use more memory. CPUs are often optimized to process data of a certain size (e.g. 32 bits).
* **integer** vs **integral**:
    * **integer**: refer to a broad set including `short`, `int`, `long`, `long long`.
    * **integral**: means “like an integer”, includes the broader set of types that are stored in memory as integers, including `bool`, `char`.
* Fast and least integral types. E.g.:
    * `std::int_fast32_t` gives the fastest (i.e., most quickly by the CPU) signed integer type that’s at least 32-bits.
    * `std::int_least32_t` gives the smallest (i.e., least memory) signed integer type that’s at least 32-bits.
* `sizeof()` returns a value of type `std::size_t`, which is an **alias** for an *implementation-defined* **unsigned** integral type.
* Floating point numbers:
    * `float` is almost always implemented using the 4-byte IEEE 754 single-precision format.
    * `double` is almost always implemented using the 8-byte IEEE 754 double-precision format.
    * `long double`: On different platforms, its size can vary between 8 and 16 bytes or may not use an IEEE 754 compliant format. 
* Boolean values are **stored** and **evaluated to** as integral values: 0, 1, not `true` or `false`.


## Constant expression

* **Constant expression** is an expression that *must* be evaluatable at compile-time.
* `constexpr` means that the object can be used in a constant expression.
* **Constexpr variable**:
    * must be initialized with a constant expression.
    * are implicitly `const`.
    * can be initialized with a non-`const` value.
* **Constexpr functions**:
    * is a function that **can** be called in a constant expression (i.e., non-`constexpr` functions cannot be called in a constant expression).
    * The return value of a non-constexpr function is not a constant expression.
    * To evaluate at compile-time, two other things must also be true:
        * passed arguments must be constant expressions
        * all statements in the function must be evaluatable at compile-time.
* Forward declaration cannot be `constexpr`, because the compiler will need to know the full definition of the function/variable to evaluate it at compile time.
* The parameters of a constexpr function cannot be declared as `constexpr` (nor implicitly `constexpr`). 
    * It means these parameters cannot be used in constant expressions within the function:
        
        ```C++
        constexpr int foo(int b)    // b is not constexpr
        {
            constexpr int b2 { b }; // compile error: b cannot be used in constant expressions
        }
        ```
    * However, these parameters can be used in a call to another `constexpr` function:
        
        ```C++
        constexpr int goo(int c) { return c; }

        // b is not a constant expression within foo(), but goo() will be evaluated at compile-time if foo() is called at compile-time
        constexpr int foo(int b) { return goo(b); }

        int main()
        {
            constexpr int a { foo(5) };     // foo(5) must evaluate at compile-time
        }
        ```
* In a non-constant expression that uses a constexpr function, the compiler may choose to or not to evaluate the constexpr function at either compile-time. `consteval` (C++20) forces the compiler to evaluate the function at compile-time.


## C-style string, `std::string`, `std::string_view`

* `std::string` and `std::string_view` aren’t fundamental types (they’re class types).
* `std::string_view` provides read-only access to an existing string without making a copy.
* Both a C-style string and a `std::string` will implicitly convert to a `std::string_view`.
* `std::string_view` will not implicitly convert to `std::string`.
* `std::string` is a (sole) owner, `std::string_view` is a viewer.
* String literals:
    * `"Hello, world!"`: C-style string literal
    * `"Hello, world!"s`: `std::string` literal
    * `"Hello, world!"ss`: `std::string_view` literal


## Switch-case

* Declaration is allowed, but initialization is disallowed underneath a `case` label. But it allowd inside an explicit block.


## `goto` statement

* If you jump forward, you can’t jump forward over the initialization of any variable 
  that is still in scope at the location being jumped to.


## `for` loop

* The order of execution:

    ```
    for (init-statement; condition; end-expression)
        statement;
    ```
    1. Init-statement: only happens once when the loop is initiated.
    2. Condition: with each loop iteration, the condition is evaluated. If this evaluates to true, the statement is executed.
    3. Loop body: the statement is executed.
    4. End-expression: executed after the statement, then jumps back to condition.


## Namespace

* **Namespace** is used to prevent *naming conflicts*.
* If `::` is used without providing a namespace name (e.g. `::doSomething`), the identifier (e.g. `doSomething`) is explicitly looked for in the global namespace.
* If `::` not used, the compiler will first try to find a matching declaration in that same namespace. If no matching identifier is found, the compiler will then check each containing namespace in sequence, with the global namespace being checked last.
* Multiple namespace blocks and nested namespaces are allowed.
* **Unnamed namespace**: All content declared in an unnamed namespace is treated as part of the parent namespace.
* **Inline namespace**: (Much like an unnamed namespace) All content declared in an inline namespace is treated as part of the parent namespace. The difference is that the inline namespace can be versioned.


## Storage duration

* Global variables are variables that are defined outside of any function. Global variables can also be defined inside a user-defined namespace.
* **Storage duration** determines when and how a variable will be created and destroyed.
* **Automatic duration**: variables are created at the point of definition and destroyed at the end of the block they are defined in.
* **Static duration**: variables are created when the program starts (before `main()` begins execution) and destroyed when the program ends
* Local variables have **automatic duration**.
* Global variables have **static duration**.
* Static local variables have **static duration** (like global variables), but have **local scope** (like local variables).


## Linkage

* An identifier’s **linkage** determines whether it can be seen and used by other translation units.
* **Internal linkage**: the identifier can be seen and used within a single **translation unit**, but it is not accessible from other translation units. This means that if 2 source files have identical internal linkage identifiers, they are treated as independent.
* Global variables with internal linkage are called **internal variables**.
* Global variables with external linkage are called **external variables**.
* By default:
    * Non-constant globals have external linkage: `int g_x1{};`. 
        
        It can be set to internal linkage by using the `static` keyword: `static int g_x1{};`.
    * `const` globals have internal linkage: `const int g_x2{};`.

        It can be set to external linkage by using the `extern` keyword: `extern const int g_x2{};`.
    * `constexpr` globals have internal linkage: `constexpr int g_x3{};`.
    
        It can be set to external linkage by using the `extern` keyword: `extern constexpr int g_x3{};`.
    * `inline` variables have external linkage.
    * Functions have external linkage: `void doSomething();`.
    
        Functions can be set to internal linkage by using the `static` keyword: `static void doSomething();`.

* To use an external that has been defined in another file:
    * With external global varibale: you must put a forward declaration of the variable using the `extern` keyword with no initialization value.
    * With external function: just put a forward declaration of the function without the `extern` keyword.
* All identifiers inside an unnamed namespace are treated as if they have internal linkage:

    ```C++
    namespace // unnamed namespace
    {
        void doA() // can only be accessed in this file
        {
            std::cout << "v1\n";
        }
    }
    // equivalent to:
    // static void doA()
    // ...
    ```


## Function overhead and inline expansion (historical view)

* For example,

    ```C++
    int min(int x, int y)
    {
        return (x < y) ? x : y;
    }
    ```
    1. When a call to `min()` is encountered, the CPU must store the address of the current instruction it is executing along with the values of various CPU registers. Then parameters x and y must be instantiated and then initialized. 
    2. Then the execution path has to jump to the code in the `min()` function. When the function ends, the program has to jump back to the location of the function call, and the return value has to be copied so it can be output.
* All of the extra work that must happen to setup, facilitate, and/or cleanup after some task is called **overhead**.
* For small functions (such as `min()` above), the overhead costs can be larger than the time needed to actually execute the function’s code! If it is called often, it can result in a significant performance penalty over writing the same code in-place.
* **Inline expansion** is a process where a function call is replaced by the code from the called function’s definition.
* Historically, compilers were not very good at determining whether it should apply inline expansion, so the `inline` keyword was introduced. However, modern C++ compilers are better than human in most cases, so it will likely ignore the `inline` keyword for this purpose.


## Inline functions and variables (modern view)

* The `inline` keyword is now used to suppress the ODR violation: an inline function is one that is allowed to be *defined* in multiple translation units.
* Requirements of `inline` function:
    1. Inline functions must have full *definitions* in every translation unit that uses them.
    2. Every definition of an inline function must be the identical. Otherwise, the program will have undefined behavior.
* The linker will then de-duplicate the definitions.
* `constexpr` functions are implicitly inline. Because, the compiler needs its definition in every translation unit that uses it to be able to evaluate it at compile time.
* `constexpr` variables are not implicitly inline.
* Member functions defined **inside** the class definition are **implicitly** inline.
* Member functions defined **outside** the class definition are **not implicitly** inline.
* constexpr members variables of a class are **implicitly** inline.


## Exit

* `std::exit()` causes the program to **terminate normally**.
* Note that "terminate normally" does not mean your program was successful. It can return a non-zero status code, but still have a normal termination.
* `std::exit()` is called implicitly after function `main()` returns.
* `std::exit()` performs a number of cleanup functions:
    * Objects with static storage duration are destroyed.
    * Miscellaneous file cleanup is done if any files were used.
    * ⚠️ It does not clean up local variables.
* `std::atexit` allows you to specify a function that will automatically be called on program termination via `std::exit()`.
* `std::abort()` function causes your program to terminate "abnormally" (e.g., dividing by 0).
* `std::abort()` does not do any cleanup.
* `std::terminate()` often called implicitly when an exception isn’t handled. By default, `std::terminate()` calls `std::abort()`.


## `assert` and `static_assert`

* When assertion fails, the program will terminate via `std::abort()`.
* C++ comes with a built-in macro `NDEBUG`: if it's defined, the assert macro gets disabled.

    ```C++
    #undef NDEBUG // enable asserts (must be placed before any #includes)
    ```
* A `static_assert` is checked at compile-time rather than at runtime => the condition must be a constant expression.


## Implicit type conversions

* 4 **standard** conversions:
    * Numeric promotions
    * Numeric conversions
    * Arithmetic conversions 
    * Other conversions
* When a type conversion is needed, the compiler may apply zero, one, or two standard conversions.
* **Numeric promotions** includes the following *specific* narrower to wider numeric types:
    * `float` -> `double`
    * `signed char`, `signed short` -> `int`
    * `unsigned char`, `char8_t`, `unsigned short` -> `int` if `int` can represent all values of the original type, otherwise `unsigned int`
    * `bool` -> `int`, with false becoming `0` and true becoming `1`

    Not all widening conversions (such as `char` to `short`, or `int` to `long`) are numeric promotions because they do not assist converting *efficiently*.

    ✅ Numeric promotions are value-preserving, and thus “safe” => reduces redundancy. You can define `void printInt(int x)` and pass `short`, `char` to it without having to define `void printShort(short x)`, `void printChar(char x)`.
* **Numeric conversions**:
    * integral type -> any integral type (excluding integral promotions)
    * floating point type -> any floating point type (excluding floating point promotions)
    * floating point type -> any integral type
    * integral type -> any floating point type
    * integral type or floating point type -> bool

    Numeric conversions fall into 3 categories:
    * Value-preserving conversions:
        * ✅ The compiler will not raise warnings.
        * ✅ The destination type can represent all values of the source type.
        * ✅ Can be converted back to the source type without loss of information. E.g., `int` -> `long` -> `int`.
    * Reinterpretive conversions:
        * ⚠️ The compiler might not raise warnings.
        * ⚠️ The destination type cannot represent all values of the source type.
        * ✅ Can be converted back to the source type without loss of information. E.g., `int` -> `unsigned int` -> `int`.
    * Lossy conversions: E.g., `int` -> `float` -> `int`.
        * ❌ The compiler will raise warnings.
        * Strangely, conversion from a floating point type to an integral type is always considered narrowing, even if the value can be represented exactly.

            ```C++
            int n { 5.0 }; // compile error: narrowing conversion
            ```
        * Strangely, conversion from a floating point type to a narrower floating point type is not considered narrowing despite loss of precision.
        
            ```C++
            constexpr double d { 0.1 };
            float f { d }; // not narrowing, even though loss of precision results
            ```
* **Arithmetic conversions**: e.g., `??? y { 2 + 3.5 };`
    * In C++, certain operators require that their operands be of the same type. One or both of the operands will be implicitly converted to **common type** using **usual arithmetic conversions**.
    * The compiler has a ranked list of types (simplified):
        1. long double (highest rank)
        2. double
        3. float
        4. long long
        5. long
        6. int (lowest rank)
    * Rules to find a **matching type**:
        1. Step 1:
            * If one operand is an **integral type** and the other a **floating point type**, the integral operand is converted to the type of the floating point operand (no integral promotion takes place).
            * Otherwise, any integral operands are numerically promoted.
        2. Step 2:
            * After promotion, if one operand is signed and the other unsigned, special rules apply:
                * If the rank of the unsigned operand is greater than or equal to the rank of the signed operand, the signed operand is converted to the type of the unsigned operand.
                * If the type of the signed operand can represent all the values of the type of the unsigned operand, the type of the unsigned operand is converted to the type of the signed operand.
                * Otherwise both operands are converted to the corresponding unsigned type of the signed operand.
            * Otherwise, the operand with lower rank is converted to the type of the operand with higher rank.


## Function overloading

* **Function overloading**: multiple functions with the same name, each has different number/type of parameters. Each function is called an **overloaded function** (or **overload**).
* **Signature**: = function name + number of parameters + parameter type + function-level qualifiers.
* **Overload resolution**: The process of matching function calls to a specific overloaded function. Steps:
    1. The compiler tries to find an exact match (this includes **trivial conversions**). For examples:

        ```C++
        void foo(int);
        void foo(double);
        foo(5); // exact match with foo(int)
        foo(5.0); // exact match with foo(double)
        ```

        ```C++
        void foo(const int);
        void foo(const double&); // reference
        foo(5); // exact match with foo(const int) via trivial conversion
        foo(5.0); // exact match with foo(const double&) via trivial conversion
        ```

        ```C++
        void foo(int);
        void foo(const int&);

        foo(5); // ambiguous match
        ```
    2. If no exact match is found, the compiler tries to match by applying numeric promotion to the argument(s).
    3. If no match is found, the compiler tries to match by numeric conversion.
    4. If no match is found, the compiler tries to match by applying user-defined conversions.
    5. If no match is found, the compiler will use ellipsis.
    6. If no match is found, the compiler will report an error.
* Matching for functions with multiple arguments: 
    * The compiler applies the matching rules to each argument *in turn*.
    * The function chosen must provide a better match than all the other candidate functions for at least one parameter, and no worse for all of the other parameters.


## Function templates

* Function templates are not actually functions. They generate functions.
* The process of creating functions from function templates is called **instantiation**.
* A **function instance** is only instantiated **once**, by the first time a function call is made in each translation unit. Further calls to the function are routed to the already instantiated function.
* ⚠️ Beware function templates with **modifiable static local variables**: each function instantiated from that template will have a separate version of the static local variable.
* Function templates can be overloaded.
* A **non-type template parameter**: a template parameter with a fixed type that serves as a placeholder for a constexpr value.
* Functions implicitly instantiated from templates are implicitly inline.


## Value categories 

* All expressions in C++ have two properties: a type and a value category.
* An **lvalue** is an expression that evaluates to an **identifiable** object.
* A **rvalue** is not identifiable (meaning they have to be used immediately), and only exist within the scope of the expression in which they are used. 
    ```C++
    int x { 5 };    // 5 is an rvalue
    int y { x };    // x is an lvalue
    int z { x + 1 }; // x + 1 is an rvalue
    int t{ return5() }; // return5() is an rvalue
    ```
* **Lvalue-to-rvalue conversion**: assignment operations `=` expects the right operand to be an rvalue. But `x = y;` is still valid because the lvalue `y` is implicitly converted to an rvalue.
* Unlike the other **literals** (which are rvalues), a C-style string **literal** is an lvalue because C-style strings decay to a pointer.


## References and Pointers

* A **reference** is an **alias** for an existing object.
* References aren’t objects. So, you can't have a reference to a reference.
* An **lvalue reference** is an alias to an existing lvalue. We can read or modify the value of the object being referenced to via the reference.
* ⚠️ An **lvalue reference to a const**: treat the object being referenced to as const (regardless of the object being referenced to is const or not):
* ⚠️ Nomenclature:
    * An **lvalue reference to a non-const** is commonly just called:
        * **lvalue reference to non-const**
        * **non-const lvalue reference**
        * **lvalue reference** (!!!)
    * An **lvalue reference to a const** is commonly just called:
        * **lvalue reference to const**
        * **const lvalue reference**
* Reference initialization:
    * All references **must** be initialized. 
    * Once initialized, references **can’t be reseated** (changed to refer to another object)
    * ⚠️ An **lvalue reference to const** can be initialized with an rvalue. C++ has a special rule: When a **const lvalue reference** is **directly** bound to a **temporary** object, the lifetime of the temporary object is extended to match the lifetime of the reference.
  		```C++
    	const int& ref_rvalue { 5 }; // okay, lvalue reference to const can be initialized with an rvalue
    	```
    * ⚠️ When you initialize an **lvalue reference to const** with a value of a **different** type, the compiler will create a temporary object of the same type as the reference and bind the reference to that temporary object.
      	```C++
       	const double& r1 { 5 };
	    std::cout << r1 << '\n'; // prints 5
       
	    char c { 'a' };
	    const int& r2 { c };     
	    std::cout << r2 << '\n'; // prints 97
       
	    short s { 6 };
	    const int& r3 { s };
	    s--;          // modification not reflected in r3, because r3 is bound to a temporary copy
	    std::cout << s << r3 << '\n'; // 56
       	```
        This is an example of case when reference is not identical to the object it is bound to.
* Assign a reference to a non-reference variable will **copy** the value.
  	```C++
    int x { 5 };
    int& ref { x };
    int y { ref }; // y is now a copy of x
    std::cout << &x << '\n';    // 0x7ffc70904a60
    std::cout << &ref << '\n';  // 0x7ffc70904a60 (same as x)
    std::cout << &y << '\n';    // 0x7ffc70904a64 (different from x)
    ```
* Binding a reference is always cheap.
* A **pointer** is an **object** that holds a memory address as its value.
* The address-of operator (`&`) does not return a literal. Instead, it returns a pointer, whose type is derived from the argument.
* The dereference operator (`*`) accesses the object stored at an address. It returns an **lvalue**.
* Pointers behave much like lvalue references. The primary difference:
    * References must be initialized, while pointers do not.
    * References are not objects, while pointers are.
    * References can not be reassigned, while pointers can.
    * References must always be bound to an object, while pointers can point to nothing.
    * References are safer to use than pointers.
* The size of pointers is always the same. It is dependent upon the architecture.
* ⚠️ Nomenclature:
    * A **pointer to const** treats the object being pointed to as const (regardless of the object being pointed to is const or not).
    * A *const pointer** is a pointer that can’t be reseated (changed to point to another object).
    * You can have a **const pointer to a const**.
* Actually, references are normally implemented by the compiler using pointers. Therefore, we can conclude that C++ really passes everything by value!
* Pointer arithmetic:
    * Given some pointer `ptr` that is an `int*`, and assume `int` is 4 bytes:
        * `ptr + 1` will return the address that is 4 bytes after `ptr`.
        * `ptr - 1` will return the address that is 4 bytes before `ptr`.
        * `ptr[n]` is the syntax equivalent to the expression `*((ptr) + (n))`
        
        => this is why C-style array allow signed integer to be used as index. For example: `ptr[-1]`.
* ✅ **Void pointer** (aka **generic pointer**): a special type of pointer that can be pointed at objects of any data type!
    * must first be cast to another pointer type before the dereference.
    ```C++
    int nValue {};
    double dValue { 5.5 };

    void* pValue {};
    pValue = &nValue;   // okay
    pValue = &dValue;   // okay 

    std::cout << *(static_cast<double*>(pValue)) << '\n';   // okay, must cast before dereference
    ```


## Function pointer

* Much like variables, functions live at an assigned address in memory (making them lvalues)
    ```C++
    // code for foo starts at memory address 0x002717f0
    int foo() { return 5; }

    foo(); // jump to address 0x002717f0
    ```
* Pointers to functions (⚠️ ugly syntax):
    ```C++
    int goo() { return 6; }
    int hoo(int x) { return x; }

    int (*fcnPtr)();
    int (*fcnPtr2)(){ &foo };       // fcnPtr2 points to function foo
    int (*fcnPtr4)(int) { &hoo };   // fcnPtr4 points to function hoo

    auto fcnPtr9 { &hoo };  // int (*)(int)
    ```
* Type of the function pointer must match the type of the function:
    ```C++
    int hoo(int x) { return x; }

    int (*fcnPtr3)() { &hoo }; // error
    int (*fcnPtr4)(int) { &hoo }; // okay
    ```
* When a function is referred to by name (without parenthesis), C++ will implicitly convert it into a function pointer:
    ```C++
    int hoo(int x) { return x; }

    int (*fcnPtr5)(int) { hoo }; // okay, automatically convert hoo to a function pointer
    void* fcnPtr6 { hoo };        // error
    ```
* Calling a function using a function pointer: 2 ways: explicitly dereference and implicitly dereference
    ```C++
    int (*fcnPtr2)(){ &foo }; // fcnPtr2 points to function foo

    (*fcnPtr2)(); // explicitly dereference
    fcnPtr2();    // implicitly dereference
    ```
* Callback functions:
    ```C++
    void loo(int x, int y, bool (*fcnPtr)(int, int))
    // void loo(int x, int y, bool fcnPtr(int, int))     equivalent, but less preferred
    {
        fcnPtr(x, y);
    }

    bool moo(int x, int y) { return x > y; }

    loo(3, 4, &moo); // okay
    loo(3, 4, moo);  // okay
    ```
* Making function pointers prettier:
    * Type alias:
        ```C++
        using fcnPtrType = bool (*)(int, int);

        void loo2(int x, int y, fcnPtrType fcnPtr) {}
        ```
    * Using `std::function`:
        ```C++
        void loo3(int x, int y, std::function<bool(int, int)> fcnPtr) {}
        ```

        ```C++
        int soo() {}
        int zoo(int x) {}

        std::function<int()> fcnPtr7 { &soo }; // function pointer that return in int and takes no arguments
        std::function fcnPtr8 { &zoo }; // okay, CTAD
        ```

        ```C++
        using fcnPtrType2 = std::function<bool(int, int)>;  // type alias
        ```
        
        Note that `std::function` only allows calling the function via implicit dereference (e.g. `fcnPtr()`), not explicit dereference (e.g. `(*fcnPtr)()`).



## Low-level const and top-level const

* **Low-level const** applies to the object being pointed to or referenced to.
* **Top-level const** applies to the object itself.

    ```C++
    const int* ptr; // low-level const, apply to the int
    const int& ref; // low-level const, apply to the int

    const int x; // top-level const, apply to the int
    int* const ptr; // top-level const, apply to the pointer
    int& ref; // reference are implicitly top-level const

    constexpr const int& ref; // constexpr applies to the reference (top-level), const applies to the int (low-level)
    ```
* ⚠️ Dropping a reference may change a low-level const to a top-level const. For example:
    
    ```C++
    const int&  // low-level const
    const int   // top-level const
    ```


## Type deduction

* Type deduction does not include `const`/`constexpr`. If you want them, you must explicitly specify them:

    ```C++
    const int a { 5 };
    auto b { a };      // b has type int, not const int
    const auto e { a }; // must explicitly specify const
    ```
* Type deduction also drops references. If you want them, you must explicitly specify them:

    ```C++
    int& getRef();
    auto x { getRef() }; // x has type int, not int&
    auto& y { getRef() }; // must explicitly specify reference
    ```
* ⚠️ Type deduction only drops top-level const, not low-level const.
* If the initializer is a **reference to const**:
    1. the reference is dropped first (and "then" reapplied if applicable), 
    2. then any top-level const is dropped

    ```C++
    const int& x { ... }; // x is a "reference to const" int, low-level const

    auto ref1 { x }; // int. Because: const int&  -> const int (drop reference) -> int (drop top-level const)
    const auto ref2 { x }; // const int. Because: const int& -> const int (drop reference) -> int (drop top-level const) -> const int (reapply const)
    auto& ref2 { x }; //  const int&. Because: const int& -> const int (drop reference) -> const int& (reapply reference) 
    ```

    ```C++
    constexpr const int& x { ... }; // constexpr is top-level, const is low-level

    auto ref1 { x }; // int. Because: constexpr const int& -> constexpr const int (drop reference, now both constexpr and const are top-level) -> int (drop top-level const)
    auto& ref2 { x }; // const int&. Because: constexpr const int& -> constexpr const int (drop reference) -> constexpr const int& (reapply reference, only constexpr is top-level) -> const int& (drop top-level const)
    ```
* Type deduction does not drop pointers (Unlike references).

    ```C++
    int* x;

    auto y { x }; // int*, also a pointer
    auto* z { x }; // int*, also a pointer (same, but more clear)

    auto y { *x }; // int, not a pointer
    auto* z { *x }; // compile error: initializer not a pointer
    ```
* C-style string type deduction:
    ```C++
    auto s1{ "Alex" };  // const char*
    auto* s2{ "Alex" }; // const char*
    auto& s3{ "Alex" }; // const char(&)[5]
    ```
    
* A function with `auto` return type needs to be fully defined before it can be called (a forward declaration is not enough). If we need a function that can be forward declared we have to be explicit about the return type:
    ```C++
    auto add(int x, double y) -> std::common_type_t<decltype(x), decltype(y)>;
    ```
    ```C++
    template <typename T, typename U>
    auto max(T x, U y) -> std::common_type_t<T, U>;
    ```


## Program-defined types: Enumerated types

* **Unscoped enumerations**:
    * Implicitly constexpr.
    * Its enumerators are in the same scope as the enumeration itself => an enumerator name can’t be used in multiple enumerations within the same scope.
    * Unscoped enumerations will **implicitly** convert to integral values. By default, the first enumerator is given the integral value 0, but you can explicitly define the value.

        ```C++
        enum Animal
        {
            cat = -3,    // values can be negative
            dog,         // -2
            horse = 5,
            giraffe = 5, // shares same value as horse
            chicken,     // 6
        };
        ```
    * Integers will **not implicitly** convert to an enumeration:

        ```C++
        Animal a1 { -3 };                       // error: 2 is not an enumerator of Animal
        Animal a2 { static_cast<Animal>(-3) };  // okay
        ```
    * ⚠️ If an enumeration is **zero-initialized**, the enumeration will be given value 0, even if there is no corresponding enumerator with that value:

        ```C++
        Animal a {}; // a is initialized to 0
        ```
    * Most compilers will use `int` as the underlying type for an enumeration. But you explicitly specify a different one:
        
        ```C++
        enum Foo : std::int8_t
        {
            goo,
            boo,
        };
        ```
* **Scoped enumerations** (`enum class`):
    * Do not implicitly convert to integers.
    * Enumerators are only placed into the scope region of the enumeration.


## Program-defined types: Class types

* **Aggregate**:
    * In general programming: any type that can contain multiple data members.
    * In C++: a bit narrower and more complicated:
        * No user-declared constructors.
        * No private or protected non-static data members.
        * No virtual functions.
* Aggregate initialization 
    * using **initializer list**: 
        * It does a **memberwise** initialization. Each member in the struct is initialized **in the order of declaration**
	
            ```C++
            truct Employee
            {
                // data members (or member variables)
                int id {};
                int age {};
                double wage {};
            };

            Employee frank = { 1, 32, 60000.0 }; // initialization list, (copy-list initialization)
            Employee alice { 2, 28, 45000.0 };     // initialization list (list initialization (preferred))

            // assigment
            alice = { 2, 30, 4000.0 };

            Employee dummyEmployee() { return Employee { 1, 32, 60000.0 };}
            Employee dummyEmployee2() { return { 1, 32, 60000.0 }; }  // can omit the type
            Employee dummyEmployee3() { return { }; } // value-initialize all members
            ```
        * Initialization possibilities:
            * If an aggregate is defined with no initialization list:
                * If a default member initializer exists, the default is used.
                * If no default member initializer exists, the member remains uninitialized (**default-initialization**).
            * If an aggregate is defined with an initialization list:
                * If an explicit initialization value exists, that explicit value is used.
                * If an initializer is missing and a default member initializer exists, the default is used.
                * If an initializer is missing and no default member initializer exists, **value-initialization** occurs.
        * You cannot use aggregate initialization for a non-aggregate type.

            ```C++
            class CDate // now a class instead of a struct
            {
                int m_year {};     // private by default
                int m_month {};    // private by default
            };

            void func1()
            {
                CDate today { 2020, 10 }; // compile error: this is not aggregate initialization (CDate does not qualify as an aggregate because it has private members) and CDate does not have a constructor to handle.

                CDate today2 {};   // okay, calling implicit default constructor
            }
            ```
    * Using another struct of the same type:

        ```C++
        struct Foo
        {
            int a {};
            int b {};
            int c {};
        };
        
        Foo f3 { 1, 2, 3};

        // The followings are not aggregate initialization:
        Foo f4 = f3;    // copy initialization
        Foo f5 { f3 };  // direct-list initialization
        Foo f6(f3);     // direct-initialization
        ```

* **Constructors**:
    * Constructors do not create the objects. The compiler sets up the memory allocation for the object prior to the constructor call.
    * **Default constructor**: a constructor that accepts no arguments.

        ```C++
        class Foo6
        {
        public:
            Foo6() // default constructor
            {
                std::cout << "Foo default constructed\n";
            }
        };
        ```
    * **Implicit default constructor**: If a non-aggregate class type object has no user-declared constructors, the compiler will generate a public default constructor (with no member initializer list, no statements in the body of the constructor).
    * If all of the parameters in a constructor have default arguments, the constructor is a default constructor.
        ```C++
        class Foo6
        {
        public:
            Foo6(int x=0, int y=0) // default constructor
            {
            }
        };
        ```
    * ⚠️ Both **value-initialization** and **default-initialization** will call default constructor.

        ```C++
        Foo6 foo6{}; // value-initialization, call default constructor
        Foo6 foo6; // default-initialization, also call default constructor
        ```
    * Delegating constructors: Steps:
        1. Initialization is delegated to another constructor:
            1. The member initializer list of the delegated constructor initializes the members.
            2. The body of the delegated constructor is executed.
        2. The body of the delegating constructor is executed.
* Non-aggregate initialization:
    * Using **member initializer list**: ⚠️ Attention: the members are always initialized in the order in which they are defined inside the class, not from left to right in the list.

        ```C++
        class Foo3
        {
        private:
            int m_x {};
            int m_y {};

        public:
            Foo3(int x, int y)
                : m_y { std::max(x, y) }, m_x { m_y } // issue on this line
            {
            }

            void print() const { std::cout << "Foo(" << m_x << ", " << m_y << ")\n"; }
        };

        void func2()
        {
            Foo3 foo3{ 6, 7 };  // member initialization list
            foo3.print();       // Foo(6, 7)
        }
        ```
    * Initialization possibilities:
        * If a member is listed in the member initializer list, that initialization value is used.
        * Otherwise, if the member has a default member initializer, that initialization value is used.
        * Otherwise, the member is default-initialized.
* List constructor:
    * Containers (such as `std::vector`) typically have a special constructor called a **list constructor** that allows us to construct an instance of the container using an **initializer list**.
        ```C++
        std::vector<int> primes{ 2, 3, 5, 7 };
        ```
    * It does three things:
        * Ensures the container has enough storage to hold all the initialization values (if needed).
        * Sets the length of the container to the number of elements in the initializer list (if needed).
        * Initializes the elements to the values in the initializer list (in sequential order).

        ```C++
        std::vector vowels { 'a', 'e', 'i', 'o', 'u' }; //  Uses CTAD (C++17) to deduce element type char (preferred).
        ```
    * C++ has a special rule:
        * If the initializer list is empty, the default constructor is preferred over the list constructor.
        * If the initializer list is non-empty, a matching list constructor is preferred over other constructors.
* **Implicit object**:
    
    ```C++
    CDate today { 2020, 10, 14 };
    today.print();
    ```
    * when we call `today.print()`, today is the **implicit object**, and it is implicitly passed to the `print()`.
    * Inside every member function, `this` is a const pointer that holds the address of the current implicit object.
        
        ```C++
        void print() const { std::cout << m_id; }       // implicit use of this
        void print() const { std::cout << this->m_id; } // explicit use of this
        ```
    * In Java and C#, `this` is implemented as a reference instead of a pointer.
* **Const member function**: is a member function that guarantees it will not modify the object or call any non-const member functions.
    * Const objects may not call non-const member functions, even if the member function does not modify the object.
    * It is possible to overload a member function to have a const 
  and non-const version of the same function.
* Member functions can be defined in any order. Because, when the compiler encounters a member function definition:
    1. The member function is implicitly forward declared.
    2. The member function definition is moved immediately after the end of the class definition.
* Access levels:
    * By default, members of a struct are `public`.
    * By default, members of a class are `private`.
    * ⚠️ C++ access levels work on a per-class basis, not per-object.
* **Copy constructor**:
    * It's a constructor that is used to initialize an object with an existing object of the same type. The copy constructor’s parameter must be a **reference**.

        ```C++
        class Fraction2
        {
        private:
            int m_numerator{ 0 };
            int m_denominator{ 1 };

        public:
            Fraction2(int numerator=0, int denominator=1)
                : m_numerator{numerator}, m_denominator{denominator}
            {
            }

            // Copy constructor
            Fraction2(const Fraction2& fraction)
                : m_numerator{ fraction.m_numerator }
                , m_denominator{ fraction.m_denominator }
            {
            }
        };
        ```
    * **Implicit copy constructor**: 
        * If you do not provide a copy constructor for your classes, C++ will create a public implicit copy constructor. 
        * By default, the implicit copy constructor will do memberwise initialization.

            ```C++
            class Fraction
            {
            private:
                int m_numerator{ 0 };
                int m_denominator{ 1 };

            public:
                // Default constructor
                Fraction(int numerator=0, int denominator=1)
                    : m_numerator{numerator}, m_denominator{denominator}
                {
                }
            };

            void func1()
            {
                Fraction f { 5, 3 };
                Fraction fCopy { f }; // => implicit copy constructor
            }
            ```
    * **Pass by value**, **return by value**, **initialization** of the same class type will implicitly invoke the copy constructor:

        ```C++
        void printFraction(Fraction2 f) // f is pass by value
        {
        }

        void func2()
        {
            Fraction2 f2 { 5, 3 };
            printFraction(f2); // f is copied using copy constructor

        }
        ```

        ```C++
        Fraction2 generateFraction(int n, int d)
        {
            return Fraction2{ n, d };
        }

        void func3()
        {
            Fraction2 f3 { generateFraction(5, 3) }; // 2 copy constructors are called here, one for the return value and one for the initialization of f3
        }
        ```
    * **Copy elision**: the compiler can optimize away the unnecessary copy constructor calls. We say the constructor has been **elided**.
* Copy semantics and Move semantics:
    * **Copy semantics**:
        * refers to how copies of objects are made.
        * For class types, copy semantics are typically implemented via the copy constructor and copy assignment operator.

        ```C++
        std::vector<int> generate() // return by value
        {
            std::vector arr1 { 1, 2, 3, 4, 5 }; // copies { 1, 2, 3, 4, 5 } into arr1
            return arr1;
        }

        int main()
        {
            std::vector arr2 { generate() }; // the return value of generate() is a temporary object and will die at the end of the expression

            return 0;
        }
        ```
        => We've made a potentially expensive copy with copy semantics. We don’t need two sets of data to exist simultaneously.
    * **Move semantics**:
        * determine how the data from one object is moved (transfer ownership, usually just two or three pointer assignments) to another object.
        * 👍 When move semantics is invoked, any data member that can be moved is moved, and any data member that can’t be moved is copied. => more efficient than copy semantics
    * ⚠️ Normally, when an object is being initialized with (or assigned) an object of the **same type**, copy semantics will be used (assuming the copy isn’t elided). However, when all of the following are true, move semantics will be invoked instead:
        1. The type of the object supports move semantics.
        2. The object is being initialized with (or assigned) an rvalue (temporary) object of the same type.
        3. The move isn’t elided.
    * ✅ For move-capable types, move semantics is invoked **automatically** when **returning by value**.

        Both `std::vector` and `std::string` support move semantics => it is okay to return them by value!!!
* Type conversion using converting constructor:
    * **Implicit** conversion: in the below example, the `printFoo` function accepts a `Foo` parameter, but we're passing an `int` value. When compiler sees `printFoo(5);`, it will find a function that lets it convert an `int` to a `Foo`. That function is the `Foo(int)` constructor.
        ```C++
        class Foo
        {
        private:
            int m_x{};
        public:
            Foo(int x)  // allow implicit conversion from int to Foo
                : m_x{ x }
            { }
        };

        void printFoo(Foo f) { }

        printFoo(5); // conversion from `5` to `Foo { 5 }`
        ```
    * The compiler might allow **only one** implicit user-defined conversion: in the below example, `printEmployee("Joe");` will not compile because it requires two user-defined conversions: C-style string literal -> std::string_view -> Employee.
        ```C++
        class Employee
        {
        private:
            std::string m_name{};

        public:
            Employee(std::string_view name)
                : m_name{ name }
            { }
        };

        void printEmployee(Employee e) { }

        printEmployee("Joe");   // compile error: requires 2 user-defined conversions
        printEmployee( "Joe"sv);    // okay, only 1 user-defined conversion from std::string_view to Employee
        printEmployee(Employee{ "Joe" }); // okay, only 1 user-defined conversion from C-style string literal to std::string_view
        ```
    * To prevent such implicit conversion, we can use `explicit` keyword to tell the compiler that a constructor should not be used as a converting constructor:
        ```C++
        class Dollars2
        {
        private:
            int m_dollars{};

        public:
            explicit Dollars2(int d) // now explicit
                : m_dollars{ d }
            { }
        };

        void print2(Dollars2 d) { }

        print2(5); // compile error: cannot convert int to Dollars2
        print2(static_cast<Dollars2>(5)); // okay, explicit conversion
        ```



## Program-defined types and header files

* Note that this is a full definition, not a forward declaration:
    ```C++
    struct Fraction
    {
        int numerator {};
        int denominator {};
    };
    ```
* Unlike functions, which only need a forward declaration to be used, header files usually contain the full definition of a class. This is because the compiler needs to understand how members are declared in order to ensure they are used properly, and it needs to be able to calculate how large objects of that type are in order to instantiate them.
* With non-template classes, the common procedure is to put the class definition in a header file, and the member function definitions in a similarly named .cpp file. However, with templates, this does not work, we’ll get a linker error. Briefly, the reason is that:
    1. remember that C++ compiles files individually, and
    2. the compiler will only instantiate a class template if the class template is used (i.e., the compiler must see both the full class template definition (not just a declaration) and the specific template type(s) needed).

    => the compiler will not instantiate it in the .cpp file to be linked with the call from the main.cpp file. More details [here](https://www.learncpp.com/cpp-tutorial/template-classes/#:~:text=Splitting%20up%20template%20classes)
 

## Nested types

- A nested class does not have access to the `this` pointer of the outer (containing) class. But can access any private members of the outer class that are in scope:

    ```C++
    #include <string>
    #include <string_view>

    class Employee2
    {
    public:
        using IDType = int;     // Nested typedefs and type aliases

        class Printer   // Nested types
        {
        public:
            void print(const Employee2& e) const
            {
                // Printer can't access Employee's `this` pointer
                // but we can access private members e.m_name and e.m_id that are in scope
                std::cout << e.m_name << " has id: " << e.m_id << '\n';
            }
        };

    private:
        std::string m_name{};
        IDType m_id{};

    public:
        Employee2(std::string_view name, IDType id)
            : m_name{ name }
            , m_id{ id }
        {
        }
    };

    void func3()
    {
        const Employee2 john2{ "John", 1, 45000 };
        const Employee2::Printer p{}; // instantiate an object of the inner class
        p.print(john2);
    }
    ```

## Destructor

* Destructor: a special member function that is called automatically when an object of a non-aggregate class type is destroyed. For example:
    * when an object goes out of scope normally
    * when a dynamically allocated object is explicitly deleted using the `delete` keyword
* The destructor must have the same name as the class, preceded by a tilde (`~`).
* The destructor can not take arguments.
* The destructor has no return type.
* ⚠️ `std::exit()` can be used to terminate your program immediately. But it does not clean up local variables => no destructors will be called. Be wary if you’re relying on your destructors to do necessary cleanup work (closing a file, releasing memory, writing to a log file, etc.).



## Static members

* Static member variables:
    * are shared by all objects of the class.
    * exists independently of any class objects.
    * are global variables that live inside the scope region of the class.
* ⚠️ You **must explicitly** define (and optionally initialize) the static member **outside** of the class, in the **global scope**.
    ```C++
    class Something
    {
    public:
        static int s_value; // declare
    };

    int Something::s_value{ 1 }; // define and initialize

    void func1()
    {
        Something::s_value = 2;
    }
    ```

    2 exceptions:
    * when the static member variables is a constant integral type or const enum, or
    * when the static member variables is inline. (Note: constexpr members variables are implicitly inline)
    ```C++
    class Whatever
    {
    public:
        static const int s_value1{ 4 }; // okay, constant integral type or const enum
        static inline int s_value2{ 4 }; // okay, inline
        static constexpr int s_value3{ 4 }; // okay, constexpr members are implicitly inline
    };
    ```
* If no initializer is provided, static member variables are zero-initialized by default.
* Static member function
    * can be useful when we need to access a **private** static member variable.
    * cannot directly access other non-static members.
    * have no `this` pointer.


## Friend

* A ***friend*** is a class or function (member or non-member) that has been granted full access to the private and protected members of another class.
* Friend non-member function:
    * ⚠️ A friend non-member function defined inside a class is treated as a non-member function.
* Friend classes:
    * class A is a friend of class B does not mean class B is also a friend of class A.
    * Nor is friendship inherited. If class A makes B a friend, classes derived from B are not friends of A.
    * A friend class declaration acts as a forward declaration for the class being friended. This means we do not need to forward declare the class being friended before friending it:

        ```C++
        class Storage
        {
        private:
            int m_nValue {};
        public:
            Storage(int nValue)
            : m_nValue { nValue }
            { }

            // Make the Display class a friend of Storage
            friend class Display;
        };

        class Display
        {
            // ...
        };
        ```
* Friend member functions: instead of making an entire class a friend, you can make a single member function a friend.


## Containers and arrays

* Array: 
    * a container data type that stores a sequence of values contiguously (in an adjacent memory location, with no gaps).
    * 3 primary C++ array types:
        * ⚠️ (C-style) arrays, behave strangely and they are dangerous.
        * `std::vector`, most flexible.
        * `std::array`: introduced in C++11 as a direct replacement for C-style arrays. More limited than `std::vector`, but can also be more efficient, especially for smaller arrays.
* Length and subscript problem:
    * ⚠️ when the container classes in the C++ standard library was being designed, the **length** and **subscripts** were decided to be **unsigned**. However, in retrospect, this is a wrong choice. Previously, we discussed the reasons why we prefer to use signed values to hold quantities.
* `std::vector`
    * is a template class.
        ```C++
        void passByRef(const std::vector<int>& arr) // we must explicitly specify <int> here
        {
            // ...
        }

        template <typename T>       // use a template
        void passByRef2(const std::vector<T>& arr)
        {
            // ...
        }
        ```
    * cannot be made constexpr.
    * ⚠️ The length and indices of `std::vector` have type `size_type`. `size_type` is almost always an alias for `std::size_t`. `std::size_t` is a typedef for some large unsigned integral type, usually `unsigned long` or `unsigned long long`.
        ```C++
        for (std::size_t index{ arr.size() - 1 }; index >= 0; --index) // index is unsigned
        ```
    * Under the hood, `std::vector` holds its elements in a C-style array. 👍  C-style arrays allow indexing with both signed and unsigned types (see: *Pointer arithmetic*).
    * Accessing array elements:
        * ⚠️ using operator[] does no bounds checking.
        * 👍 using the `.at()` member function does runtime bounds checking, but slower than operator[].
            ```C++
            std::vector<int> primes{ 2, 3, 5, 7 };

            std::cout << primes[9]; // undefined behavior
            std::cout << primes.at(9); // throws exception
            ```
        * 👍 Indexing with a constexpr signed int is not a narrowing conversion.
            ```C++
            constexpr int index { 3 };         // constexpr
            std::cout << primes[index] << '\n'; // okay, constexpr index implicitly converted to std::size_t, not a narrowing conversion
            ```
        * 👍 Indexing with a non-constexpr `std::size_t` value is not a narrowing conversion
            ```C++
            std::size_t index2 { 3 };           // non-constexpr of type std::size_t
            std::cout << primes[index2] << '\n'; // okay, no conversion required
        * ⚠️ Indexing with a non-constexpr signed value is a narrowing conversion.
            ```C++
            int index3 { 3 };                   // non-constexpr signed value
            std::cout << primes[index3] << '\n'; // possible warning: index implicitly converted to std::size_t, narrowing conversion
            ```
        * 👍 Indexing the result of the `.data()` member function with signed values is not a narrowing conversion.

             The `.data()` member function returns a pointer to the underlying C-style array => we don’t run into any sign conversion issues.

            ```C++
            int index3 { 3 };                   // non-constexpr signed value
            std::cout << primes.data()[index] << '\n'; // okay: no sign conversion warnings
            ```
    * `std::vector<bool>`:
        * ⚠️ It's not a real container and can breaks generic code. The C++ standard explicitly calls out `vector<bool>` as a special container where each bool uses only one bit of space rather than one byte as a normal bool would.
            * 👎️ => you can't take the address of a bit within a byte.
            * 👎️ => things such as operator[] can't return a bool&.
            * 👎️ => you can't assign its address to a bool* like you could with the other "normal" container.
            ```C++
            std::vector<bool> v_bool = {true, false, true};
            bool& ref = v_bool[0];  // error
            bool* ptr = &v_bool[0]; // error
            ```
        * Performance depends heavily on how well the implementation is optimized. Some implementations can be slower than alternatives.
* Fixed-size arrays vs dynamic arrays:
    * `std::array` and C-style arrays are fixed-size array types.
    * `std::vector` is a dynamic array.
    * **Length** vs **capacity**:
        * **capacity** is how many elements the std::vector has allocated storage for.
        * **length** is how many elements are currently being used.
        * A std::vector with a capacity of 5 has allocated space for 5 elements. If the vector contains 2 elements in active use, the length (size) of the vector is 2. The 3 remaining elements have memory allocated for them, but they are not considered to be in active use. They can be used later without overflowing the vector. (See syntax-and-snippnet for a demo).
    * Reallocation process:
        * When `std::vector` acquires new memory with capacity for the desired number of elements, these elements are **value-initialized**.
        * The elements in the old memory are copied (or moved, if possible) into the new memory. The old memory is then returned to the system.
        * The capacity and length of the std::vector are set to the new values.

        => ⚠️ Reallocation is an expensive process.
    * ⚠️ Resizing a vector changes both capacity and length:
        ```C++
        std::vector<int> arr2(3); // vector containing 3, the length is also being set to 3
        arr2.push_back(4);        // push on top of the stack
        for (auto i : arr2)
            std::cout << i << ' ';  // [0 0 0 4] instead of [4 0 0]

        std::vector arr3{1, 2, 3};
        arr3.resize(5);  // also changes the length
        arr3.push_back(4);
        for (auto i : arr3)
            std::cout << i << ' ';  // [1 2 3 0 0 4]
        ```
    * 👍 `reserve()` member function changes the capacity (but not the length):
        ```C++
        std::vector<int> arr4{};
        arr4.reserve(5);  // reserve 5 elements
        arr4.push_back(1);
        for (auto i : arr4)
            std::cout << i << ' ';  // [1]
        ```
    * `push_back()` vs `emplace_back()`:
        * Both push element to end of vector.
        * When we already have an object to be push, `push_back` and `emplace_back` are similar in efficiency.
        * However, in cases where we are creating a temporary object, `emplace_back` is more efficient:
        ```C++
        class Foo
        {
        public:
            Foo(int x, std::string b) {}
        };

        void func4()
        {
            std::vector<Foo> arr5;
            arr5.push_back({ 1, "a" }); // creates a temporary object, and then copies it into the vector
            arr5.emplace_back(1, "a");          // forwards the arguments so the object can be created directly in the vector (no copy made)
        }
        ```
* `std::array`:
    * When to use `std::array` over `std::vector`:
        * `std::vector` is slightly less performant than `std::array`.
        * (Main reason) `std::vector` only supports constexpr in very limited contexts.

            👎️ => Define `std::array` as constexpr whenever possible. If your `std::array` is not constexpr, consider using a `std::vector` instead.
    * the length of a `std::array` **must** be a constant expression.
        ```C++
        std::vector<int> b(7);    // a std::vector of 7 ints (for comparison)

        std::array<int, 7> arr2 {};  // using literal constant

        constexpr int len3 { 7 };
        std::array<int, len3> arr3 {};  // using constexpr variable
        ```
    * is an aggregate => to initialize it, we provide an initializer list.
        ```C++
        std::array<int, 5> arr5 { 1, 2, 3, 4, 5 };  // list initialization
        std::array<int, 5> arr6 = { 1, 2, 3, 4, 5 }; // copy-list initialization

        std::array<int, 5> arr7; // member default initialization (in most case left uninitialized)    
        std::array<int, 5> arr8 {}; // member value initialization (zero-initialized)

        std::array<int, 5> arr9 { 1, 2 }; // [1 2 0 0 0]

        // CTAD (C++17)
        constexpr std::array arr12 { 1, 2, 3}; // type is deduced to std::array<int, 3>
        ```
    * ⚠️ Aggregate initialization syntax works for `std::array`:
        ```C++
        struct House
        {
            int number{};
            int stories{};
            int roomsPerStory{};
        };

        void func1()
        {
            // work
            std::array<House, 3> houses{};
            houses[0] = { 13, 1, 7 };
            houses[1] = { 14, 2, 5 };
            houses[2] = { 15, 2, 4 };

            // work
            constexpr std::array houses2 { // CTAD to deduce <House, 3>
                House{ 13, 1, 7 },
                House{ 14, 2, 5 },
                House{ 15, 2, 4 }
            };

            // ⚠️ doesn't work
            constexpr std::array<House, 3> houses3 { 
                { 13, 1, 7 },
                { 14, 2, 5 },
                { 15, 2, 4 }
            };

            // works
            constexpr std::array<House, 3> houses4 {
                { // extra set of braces 
                    { 13, 4, 30 }, 
                    { 14, 3, 10 }, 
                    { 15, 3, 40 }, 
                }
            };
        }
        ```
        A `std::array` is defined as a "struct" like this:
        ```C++
        template<typename T, std::size_t N>
        struct array
        {
            T implementation_defined_name[N];
        }
        ```
        where `implementation_defined_name` is a C-style array with N elements of type T.

        => ⚠️ in the 3rd example, `{ 13, 1, 7 }` is used to initialize `implementation_defined_name`. Then the compiler will discover that we’ve provided two more initialization values (`{ 14, 2, 7 }` and `{ 15, 2, 5 }`) which exceeds the number of members in the struct.
    * Brace elision for `std::array`: 
        
        Given the explanation above, you may be wondering why the following single-brace syntax work?
        ```C++
        constexpr std::array<int, 3> arr { 1, 2, 3 }; // single braces
        constexpr std::array<int, 3> arr { { 1, 2, 3 } }; // double braces
        ```
        Generally, you can omit braces when initializing a `std::array` with:
        * scalar values, or
        * with class types where the type is explicitly named.

        👍 There is no harm in always initializing `std::array` with double braces.
    * Length and indexing of `std::array` is similar to `std::vector`. 👍 But, because the length of a `std::array` is constexpr, each of the `.size()`, `std::size()`, `.ssize()` (C++20) will return the length as a constexpr value (even when called on a non-constexpr std::array object)
        ```C++
        std::array<int, 5> arr13 { 1, 2, 3, 4, 5 }; // not constexpr
        constexpr int len13 { arr13.size() };  // ok, return value is constexpr std::size_t and can be converted to int, not a narrowing conversion
        ```
    * While 👎️ `operator[]` does no bounds checking and 👎️ `at()` member function 
  only does runtime bounds checking (remind that function parameters can’t be constexpr), 👍 the `std::get()` function template does compile-time bounds checking.

        ```C++
        constexpr std::array<int, 5> arr14 { 1, 2, 3, 4, 5 };
        std::cout << std::get<2>(arr14) << '\n';  // 3
        std::cout << std::get<10>(arr14) << '\n';  // compile-time error
        ```
    * ⚠️ Pass `std::array` by (const) reference: the type of the non-type template parameter for std::array should be `std::size_t`, not `int`. 
        ```C++
        void passByRef(const std::array<int, 5>& arr) // we must explicitly specify <int, 5> here
        {
            // ...
        }

        template <typename T, std::size_t N>
        void passByRef2(const std::array<T, N>& arr)
        {
            // ...
        }
        ```
    * ⚠️ Returning a `std::array`: Unlike `std::vector`, `std::array` is not move-capable, so **returning it by value** will make a copy => Consider using an out parameter or use `std::vector` instead.
* Arrays of references:
    * ⚠️ You **cannot** make an array of references. Because, the elements of an array must be assignable, while references can’t be reseated.
        ```C++
        int x { 1 };
        int y { 2 };
        std::array<int&, 2> refarr { x, y }; // compile error

        int& ref1 { x };
        int& ref2 { y };
        std::array valarr { ref1, ref2 }; // ok, but this is actually a std::array<int, 2>, not an array of references
        valarr[0] = 10;
        std::cout << valarr[0] << " " << x << '\n'; // 10 1
        ```
    * 👍 `std::reference_wrapper` behaves like a modifiable lvalue reference to T:
        ```C++
        std::array<std::reference_wrapper<int>, 2> arr { x, y };
        arr[0].get() = 10;
        std::cout << arr[0] << " " << x << '\n'; // 10 10
        ```

        Notes about `std::reference_wrapper`:
        * `Operator=` will "reseat" a `std::reference_wrapper`.
        * `std::reference_wrapper<T>` will implicitly convert to `T&`.
        * `get()` member function can be used to get a `T&`.
* C-style array:
    * Syntax: use square brackets (`[]`) to declare a C-style array:
        ```C++
        int arr[5]; // define an array of 5 int values
        ```
    * The length of a C-style array **must** be a constant expression of type `std::size_t` (Just like `std::array`).
    * CTAD doesn’t work with C-style array, so we must explicitly specified element's type.
        ```C++
        auto arr7[5] { 1, 2, 3, 4, 5 }; // compile error
        ```
    * C-style arrays are aggregates (Just like `std::array`) => they can be initialized using aggregate initialization.
    * When we initialize a C-style array with an initializer list, we can omit the length:
        ```C++
        int arr8[] { 1, 2, 3, 4, 5 }; // the length is deduced
        ```
    * Getting the length of a C-style array:
        * (C++17) can use `std::size()` or `std::ssize()`.
        * ⚠️ Prior to C++17, there was no standard library function to get the length of a C-style array => we can use this function instead:
            ```C++
            template <typename T, std::size_t N>
            constexpr std::size_t length(const T(&)[N]) noexcept
            {
                return N;
            }

            int arr[5];
            std::cout << length(arr) << '\n'; // prior to C++17
            std::cout << std::size(arr) << '\n'; // C++17, returns unsigned integral
            std::cout << std::ssize(arr) << '\n'; // C++20, returns signed integral
            ```
    * C-style arrays don’t support assignment:
        ```C++
        int arr9[3] { 1, 2, 3 };
        arr9[0] = 4; // ok
        arr9 = { 4, 5, 6 }; // compile error
        ```
    * C-style array decay:
        * In most cases, when a C-style array is used in an expression, the array will be implicitly converted into a pointer, initialized with the address of the first element (with index 0).
            ```C++
            int arr1[] { 1, 2, 3, 4, 5 };   // array
            auto ptr{ arr1 }; // decayed array. Type deduction should deduce type int*
            std::cout << std::boolalpha << (typeid(ptr) == typeid(int*)) << '\n'; // true
            std::cout << std::boolalpha << (&arr1[0] == ptr) << '\n'; // true

            ```
        * Cases in C++ where an C-style array doesn’t decay:
            * When used as an argument to `sizeof()` or `typeid()`.
            * When taking the address of the array using `operator&`.
            * When passed as a member of a class type.
            * When passed by reference.
        * 👍 => avoid expensive copy
        * 👍 => a single function can accept arrays of different sizes
            ```C++
            void f(const int* arr) // pass by const address
            {
                // ...
            }

            int arr1[] { 1, 2, 3, 4, 5 };
            f(arr1);
            ```
        * Syntax:
            * 👎️ declaring the function parameter as `int* arr` makes it not obvious that `arr` is a "pointer to an array" rather than a pointer to a single integer.
            * 👎️ declaring the function parameter as `int arr[]` is more preferred, but makes it less obvious that `arr` has decayed

            ```C++
            void f(const int arr[]) // pass by const address
            {
                // ...
            }
            ```
        * ⚠️ Problems: Loss of length information. Consequence:
            * `sizeof()` will return different values for arrays and decayed arrays:
                ```C++
                void printArraySize(int arr[])
                {
                    std::cout << sizeof(arr) << '\n'; // prints 4 (assuming 32-bit addresses)
                }

                int arr1[] { 1, 2, 3, 4, 5 };
                std::cout << sizeof(arr1) << '\n'; // prints 20 (assuming 32-bit addresses)
                ```
            * make refactoring difficult
            * Some work-arounds:
                * pass the length of the array as a separate parameter.
                    * 👎️ sign conversion issues
                    * 👎️ cannot do compile-time validation
                    * 👎️ only work with explicit call. If the array is passed as operand, we cannot pass in the length.
                * mark the end of the array using a special element.
                    * 👎️ need special handling for the terminating element.
                    * 👎️ mismatch between the array actual length and the number of semantically valid elements.
    * C-style string: 
        * simply declare a C-style array variable of `char`:
            ```C++
            char str1[8]{};                    // 8 char, including hidden null-terminator character
            const char str2[]{ "string" };     // 7 char, including hidden null-terminator character
            ```
        * Outputting: `std::cout` outputs characters until it encounters the null terminator. `std::cout` makes some assumptions:
            * If you pass it a non-char **pointer**, it will simply print the contents of that pointer.
            * If you pass it an object of type `char*` or `const char*`, it will print a string.
            ```C++
            const char str2[]{ "string" };
            std::cout << str2 << '\n'; // string

            int narr[]{ 9, 7, 5, 3, 1 };
            std::cout << narr << '\n'; // 0x7ffeeb1b3b40

            char c{ 'Q' };
            std::cout << &c << '\n'; // undefined behavior
            // intending to print the address of c. However, &c has type char*, so std::cout will try to print this as a string.
            // But, because c is not null-terminated, we get undefined behavior.
            ```
        * Inputting:
            * ⚠️ Prior to C++20, `std::cin` would extract as many charaters as possible (stopping at the first non-leading whitespace) => might overflow.
            * In C++20, `operator>>` only work for inputing non-decayed C-style strings => extract only as many characters as length will allow
            * *See syntax-and-snippnet for the the recommended way to read C-style strings.*
        * ⚠️ Getting the length:
            * `std::size()` or `std::ssize()` returns the actual length of the array, not the length of the string => use `strlen()`
            * But `strlen()` is slow, as it has to traverse through the array to count until it hits the null terminator.
        * C-style string symbolic constants:
            ```C++
            const char name[] { "Alex" };     // case 1: const C-style string initialized with C-style string literal
            const char* const color{ "Orange" };    // case 2: const pointer to C-style string literal
            ```
            While producing the same results, the memory allocation for the 2 methods behave differently:
            * Case 1:
                * “Alex” is put into (probably read-only) memory somewhere.
                * program allocates memory for a C-style array of length 5 and initializes it with “Alex"

                => 2 copies of “Alex”.
            * Case 2:
                * places the string “Orange” into read-only memory somewhere.
                * initializes the pointer with the address of the string.
* Multidimensional arrays: *see code in github lesson*.
* Iterate through an array: Different ways:
    * using indexes
    * using *Pointer arithmetic*:
        * All standard library containers offer direct support for iteration:
            * using member functions `begin()` and `end()`
            * or, using functions `std::begin` and `std::end`

        ```C++
        template <typename T>
        void print(const T* begin, const T* end)
        {
            for (auto p{ begin }; p != end; ++p) // ++ to move to next element.
            {
                std::cout << *p << ' '; // Indirection to get value of current element.
            }
        }

        std::array array{ 1, 2, 3 };

        auto begin{ array.begin() };
        auto end{ array.end() };
        print(begin, end);

        auto begin2{ std::begin(array) };
        auto end2{ std::end(array) };
        print(begin2, end2);
        ```

        ```C++
        void printArray(const int* begin, const int* end)
        {
            for (; begin != end; ++begin)   // iterate from begin up to (but excluding) end
            {
                std::cout << *begin << ' '; // dereference our loop variable to get the current element
            }
        }

        constexpr int arr[]{ 9, 7, 5, 3, 1 };

        const int* begin{ arr };                // begin points to start element
        const int* end{ arr + std::size(arr) }; // end points to one-past-the-end element

        printArray(begin, end);
        ```
        * ⚠️ Much like pointers and references, iterators can be left “dangling” if the elements being iterated over change address or are destroyed.
    * Range-based for-loops: They use iterators.
        ```C++
        template <typename T>
        void print(const std::vector<T>& arr)
        {
            for (auto num : arr) // iterate and copy each value into `num`
            {
                // ...
            }
        }
        ```
        * Work with a wide variety of array types, including non-decayed C-style arrays, std::array, std::vector, linked list, trees, and maps.
        * The loop variable should have the same type as the array elements => prefer using `auto`
        * ⚠️ Elements are copied to the loop variable 
            * Expensive for some types => ✅ can use reference to avoid such copy.
            * Cannot change the values in the array => ✅ can use non-const reference.
            ```C++
            for (const auto& num : arr) // if non-const, the reference can change the values in the array
            {
                // ...
            }
            ```
        * Loops in reverse (C++20):
            ```C++
            #include <ranges> // C++20
            for (const auto& num : std::views::reverse(arr))
            {
                // ...
            }
            ```
        * Behind the scenes, the range-based for-loop calls `begin()` and `end()` of the type to iterate over.

## Command line arguments

* `argc`: the number of arguments passed to the program, always be at least 1.
* `argv`: C-style array of char pointers (the length of this array is `argc`), each of which points to a C-style string.
* To use a command line argument as a number, you must convert it from a string to a number. (See syntax-and-snippnet).


## Ellipsis

* 👍 Ellipsis allows us to pass a **variable** number of parameters to a function. (See code in github lesson). 

## Memory allocation

* Overview of memory:
    * The memory that a program uses is typically divided into areas, called ***segments***:
        * code segment (text segment): stores compiled program
        * bss segment (uninitialized data segment): stores zero-initialized global and static variables
        * data segment (initialized data segment): stores initialized global and static variables
        * heap: stores dynamically allocated variables
        * call stack: stores function parameters, local variables, and other function-related information
    * The call stack:
        * When the program encounters a function call:
            1. A **stack frame** is constructed and pushed on the stack. The stack frame consists of:
                * The address of the instruction beyond the function call (called the **return address**) => where to return to after the called function exits.
                * All function arguments.
                * Memory for any local variables.
                * Saved copies of any registers modified by the function that need to be restored when the function returns.
            2. The CPU jumps to the function’s start point.
            3. The instructions inside of the function begin executing.
        * When the function terminates:
            1. Registers are restored from the call stack
            2. The stack frame is popped off the stack. This frees the memory for all local variables and arguments.
            3. The return value is handled.
            4. The CPU resumes execution at the return address.
        * All memory allocated on the stack is known at compile time. Consequently, this memory can be accessed directly through a variable.
        * ⚠️ Stack overflow:
            * The stack has a limited size. E.g., default 1MB on Visual Studio, 8MB with g++/Clang for Unix.
            * Stack overflow is generally due to allocating too many variables or nested function calls on the stack.
            ```C++
            int stack[10000000];
            std::cout << "hi" << stack[0];
            // Segmentation fault, tries to allocate a huge (likely 40MB) array on the stack
            ```
* C++ supports three basic types of memory allocation:
    * **Static** memory allocation: happens for static and global variables.
        * allocated once when your program is run, and persists throughout the life of your program.
    * **Automatic** memory allocation: happens for function parameters and local variables.
        * allocated when the relevant block is entered, and freed when the block is exited.

        Both static and automatic allocation have things in common:
            * The size of the variable must be known at compile time.
            * 👍 Memory allocation and deallocation happens **automatically**.
            * most normal variables are allocated in **stack** memory (quite small).
    * **Dynamic** memory allocation:
        * a way to request memory from the OS when needed.
        * ⚠️ we must dispose the allocated memory by ourselves.
        * use **heap** memory (generally slower than stack memory).
* Dynamic memory allocation:
    * allocating "single" variables:
        ```C++
        int* ptr{ new int };    // dynamically allocate an integer and assign the address to ptr
        delete ptr;     // return the memory to the OS
        ptr = nullptr;

        // dynamically allocate and initialize
        int* ptr1{ new int (5) }; // direct initialization
        int* ptr2{ new int { 6 } }; // uniform initialization
        delete ptr1;
        ptr1 = nullptr;
        delete ptr2;
        ptr2 = nullptr;
        ```
    * allocating arrays (demo with C-style arrays):
        ```C++
        std::size_t length{ 10 };   // not constepxr
        int* array{ new int[length]{} }; 
        delete[] array;

        // dynamically allocate and initialize
        int* array2{ new int[5]{ 9, 7, 5, 3, 1 } };
        auto* array3{ new int[5]{ 9, 7, 5, 3, 1 } };    // type deduction
        int* array4{ new int[]{ 9, 7, 5, 3, 1 } }; // Explicitly stating the size of the array is optional.
        delete[] array2;
        delete[] array3;
        delete[] array4;
        ```
    * ⚠️ Deallocating memory may create multiple dangling pointers:
        ```C++
        int* ptr3{ new int{} };
        int* otherPtr{ ptr3 }; // otherPtr is now pointed at that same memory location
        delete ptr3; // ptr3 and otherPtr are now dangling pointers.
        ptr3 = nullptr;
        // however, otherPtr is still a dangling pointer!
        ```
    * ⚠️ allocation can fail: in rare circumstances, the OS may not have any memory to grant. By default, a bad_alloc exception is thrown and the program will crash. ✅ Alternatively, we can return a null pointer by adding `std::nothrow`:
        ```C++
        int* value { new (std::nothrow) int };
        ```
    * We don't actually delete the `ptr` variable, it can be assigned a new value (e.g., nullptr) just like any other variable.
    * ⚠️ **Memory leaks**: when your program loses the address of the memory before giving it back to the OS => The OS cannot use this memory.
        ```C++
        {
            int* ptr{ new int{} };
        } // ptr goes out of scope, we lost the address of the memory

        {
            int value = 5;
            int* ptr{ new int{} }; // allocate memory
            ptr = &value; // old address lost
        }
    

## Lambdas

* **Functors** are objects that contain an overloaded `operator()` that make them callable.
* **Lambdas** are a special kind of functor.
* ✅ Lambdas aren’t functions, which is part of how they avoid the limitation of C++ not supporting nested functions.
* Lambdas can have no name if we defined a it right where it was needed. This use is called a **function literal**:
    ```C++
    int x{ 7 };
    int y{};
    y = [](int a) -> int { return a * 2; }(x);  // y = 14
    ```
* (C++14) Lamdas’re allowed to use `auto` for parameters. A unique lambda will be generated for each different type that `auto` resolves to.
* In lambda, static variables work exactly the same as regular functions.
* (C++17) Lambdas are implicitly constexpr if:
    1. They have no captures, or all captures must be constexpr.
    2. Functions called by the lambda must be constexpr.
* Lambda **captures**:
    * 👎️ Unlike nested blocks, where any identifier accessible in the outer block is accessible in the nested block. Lambdas can only access objects defined outside the lambda if:
        * they have static (or thread local) storage duration (e.g., global variables and static locals)
        * or, they are constexpr (explicitly or implicitly)
        * or, they are listed in **capture clause**.
    * ⚠️ The captured variables of a lambda are **copies** of the outer scope variables.
        ```C++
        int y{ 5 };
        [y]() { } ();  // y is cloned
        ```
    * ⚠️ 
        * At **compile** time, when the compiler encounters a lambda definition, it creates a custom object definition for the lambda. Each captured variable becomes a data member of the object.
        * At runtime, when the lambda definition is encountered, the lambda object is instantiated. The members of the lambda are initialized at that point and ⚠️ persisted across multiple calls to the lambda!
    * Captures are const by default:
        ```C++
        [y]() { ++y } (); // error, inside the lambda, y is const.
        ```
    * *Mutable* captures:
        ```C++
        int y{ 5 };

        auto increment {[y]() mutable
        {
            ++y;
            std::cout << y << '\n';
        }};
        increment();    // 6, y is modified inside the lambda. But it's a copy of the outer y.
        increment();    // 7, y is persisted across multiple calls to the lambda

        std::cout << y << '\n'; // 5, y is not modified outside the lambda.
        ```
    * Capture by reference
        ```C++
        int y{ 5 };
        [&y]() { ++y; } ();
        std::cout << y << '\n'; // 6, y is modified.
        ```
    * Multiple captured variables: 
        * This can include a mix of variables captured by value or by reference
            ```C++
            [x, &y]() { } ();
            ```
        * **Default captures** capture all variables.
            * To capture all variables by value, use `=`.
            * To capture all variables by reference, use `&`.
            * can be mixed with normal captures.

            ```C++
            int a{ 1 }, b{ 2 }, c{ 3 };
            auto d{ [=]() { return a + b + c; } () };   // a, b, c are captured by value.            
            auto e{ [&, a, b]() { return a + b + c; } () };   // a, b are captured by value, c is captured by reference.
    * Defining new variables in the lambda-capture:
        * The newly defined variable is the same for every call. But if a lambda is "mutable" and modifies a variable that was defined in the capture, the original value will be overridden.
            ```C++
            int x{ 2 };
            int y{ 5 };

            auto f { [new_var{ x * y }]() mutable { new_var++; } };
            
            f();    // new_var is 11
            f();    // new_var is 12
    * ⚠️ Dangling captured variables
        ```C++
        // returns a lambda
        auto print1(const std::string& name)
        {
            return [&]() {          // Capture name by reference
                std::cout << name;  // Undefined behavior
            };
        }

        auto print2(const std::string& name)
        {
            return [=]() {          // Capture name by value
                std::cout << name;
            };
        }

        auto printWilly1{ print1("Willy") }; // the temporary string literal "Willy" dies at the end of this command
        printWilly1(); // `name` is a dangling reference 
        auto printWilly2{ print1("Willy") };
        printWilly2(); // okay
        ```


## Overloading operators

* 3 different ways:
    1. Using friend functions
    2. Using normal functions
    3. Using member functions
* Overload io operators: (See code in github lesson)
* Overload subscript operator: (See code in github lesson)






---

Few reminders about passing temporary objects:
- they are created and initialized at the point of definition, 
  and are destroyed at the end of the full expression in which they are created.
- And evaluation of a temporary object is an rvalue expression.
- it will only bind to parameters that accept rvalues.
  This includes pass by value and pass by const reference, 
  and excludes pass by non-const reference and pass by address.




When passing arguments into a function by value, a copy of the argument is made.
- We encounter a similar situation when returning by value: a copy of the return value is passed back to the caller.




For non-extern constant global variables are visible from the point of declaration until the end of the "file" in which they are declared.


New programmers often think that creating variables is expensive.
- However, creating a variable has no cost.
- it is the initialization that has a cost, and there is typically 
  no cost difference between initialization and assignment. 
