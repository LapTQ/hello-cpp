

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
* **Constexpr functions**:
    * is a function that can be called in a constant expression.
    * The return value of a non-constexpr function is not a constant expression.
* Forward declaration cannot be `constexpr`, because the compiler will need to know the full definition of the function/variable to evaluate it at compile time.


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
* **Inlide namespace**: (Much like an unnamed namespace) All content declared in an inline namespace is treated as part of the parent namespace. The difference is that the inline namespace can be versioned.


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


## Function overhead and inline expansion

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


## Inline functions and variables

* The `inline` keyword is now used to suppress the ODR violation: an inline function is one that is allowed to be *defined* in multiple translation units.
* Requirements of `inline` function:
    1. Inline functions must have full *definitions* in every translation unit that uses them.
    2. Every definition of an inline function must be the identical. Otherwise, the program will have undefined behavior.
* The linker will then de-duplicate the definitions.
* `constexpr` functions are implicitly inline.
* `constexpr` variables are not implicitly inline.


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
* A `static_assert` is checked at compile-time rather than at runtime => the condition must be a constant expression.

    ```C++
    #undef NDEBUG // enable asserts (must be placed before any #includes)
    ```


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
        * Strangely, conversion from a floating point type to a narrower floating point type is not considered narrowing despite loss of precision.
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
    
    



For non-extern constant global variables are visible from the point of declaration until the end of the "file" in which they are declared.


New programmers often think that creating variables is expensive.
- However, creating a variable has no cost.
- it is the initialization that has a cost, and there is typically 
  no cost difference between initialization and assignment. 
