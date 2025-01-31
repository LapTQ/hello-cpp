/* Reminders

- auto keyword can be used to have the compiler deduce the type of a variable from the initializer.
- type deduction will drop const from types.
*/

/* Type deduction also drops references

- if you want the deduced type to be a reference, you can reapply the 
  reference at the point of definition: `auto&`.

*/

/* Top-level const and low-level const

- Top-level const: apply to the object itself.
    ```
    const int x; // const applies to the int, top-level const
    int* const ptr; // const applies to the pointer, top-level const
    // references are implicitly top-level const
    ```
- Low-level const: apply to the object being pointed or referenced to.
    ```
    const int* ptr; // const applies to the int, low-level const
    const int& ref; // const applies to the int, low-level const

    constexpr const int& ref; // NOTE: constexpr applies to the reference (top-level), const applies to the int (low-level)
    ```
*/

/* Type deduction only drops top-level const, not low-level const.

=> Dropping a reference may change a low-level const to a top-level const:
    For example:
    const int& (low-level const) -> const int (top-level const)
*/

/* If the initializer is a reference to const, 
   the reference is dropped first (and "then" reapplied if applicable), 
   then any top-level const is dropped

  Example 1:
  ```
  const int& x { ... }; // x is a reference to const int, low-level const

  auto ref1 { x }; // int: const int&  -> const int (drop reference) -> int (drop top-level const)

  const auto ref2 { x }; // const int: const int& -> const int (drop reference) -> int (drop top-level const) -> const int (reapply const)

  auto& ref2 { x }; //  const int&: const int& -> const int (drop reference) -> const int& (reapply reference) 
  ```

   Example 2:
    ```
    constexpr const int& x { ... }; // constexpr is top-level, const is low-level

    auto ref1 { x }; // int: constexpr const int& -> constexpr const int (drop reference, now both constexpr and const are top-level) -> int (drop top-level const)

    auto& ref2 { x }; // const int&: constexpr const int& -> constexpr const int (drop reference) -> constexpr const int& (reapply reference, only constexpr is top-level) -> const int& (drop top-level const)
    ```
*/

/* type deduction does not drop pointers (Unlike references)

```
int* x; // x is a pointer

auto y { x }; // int*, also a pointer
auto* z { x }; // int*, also a pointer (same, but more clear)


auto y { *x }; // int, not a pointer
auto* z { *x }; // compile error: initializer not a pointer

*/

/* (Just like with references) only top-level const is dropped during pointer type deduction
*/

/* auto vs auto* for pointers

```
int* x; // x is a pointer

// auto => order not matter
const auto y { x }; // int* const, make the deduced pointer type a const pointer
auto const y { x }; // int* const, make the deduced pointer type a const pointer

// auto* => order matters
const auto* y { x }; // const int*, make the deduced pointer a pointer to const
auto* const y { x }; // int* const, make the deduced pointer type a const pointer
```

=> auto* is more clear and less error-prone than auto
*/


/* References

- https://www.learncpp.com/cpp-tutorial/type-deduction-with-pointers-references-and-const/
*/