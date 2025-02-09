/*
C++ supports three basic types of memory allocation:
- Static memory allocation: happens for static and global variables.
  Memory for these types of variables is allocated once when your program is run and persists throughout the life of your program.
- Automatic memory allocation: happens for function parameters and local variables. 
  Memory for these types of variables is allocated when the relevant block is entered, 
  and freed when the block is exited.
- Dynamic memory allocation

Both static and automatic allocation have two things in common:
- The size of the variable / array must be known at compile time.
- Memory allocation and deallocation happens automatically.
=> Limitation:
    - For example, we may want to read in a number of records from disk, but we don’t know in advance how many records there are.
      the best we can do is try to make a guess the maximum size.
      => wasted memory if the variables aren’t actually used.
    - most normal variables (including fixed arrays) are allocated in stack memory, which is generally quite small.

Dynamic memory allocation: 
- is a way for running programs to request memory from the operating system when needed.
  This memory comes from heap memory.
- Unlike static or automatic memory, the program itself is responsible for disposing of dynamically allocated memory.

- Note that accessing heap-allocated objects is generally slower than accessing stack-allocated objects.
*/


/* Dynamically allocating "single" variables

- To allocate a single variable dynamically, use operator `new`:
    ```
    int* ptr{ new int }; 

    int* ptr1{ new int (5) }; // use direct initialization
    int* ptr2{ new int { 6 } }; // use uniform initialization
    ```
- To return the memory back to the OS:
    ```
    delete ptr;     // return the memory to the OS
    ptr = nullptr;
    ```
    The OS is then free to reassign that memory to another application. We don't actually delete
    the `ptr` variable, it can be assigned a new value (e.g., nullptr) just like any other variable.
*/


/* Deallocating memory may create multiple dangling pointers

```
int main()
{
    int* ptr{ new int{} };
    int* otherPtr{ ptr }; // otherPtr is now pointed at that same memory location

    delete ptr; // ptr and otherPtr are now dangling pointers.
    ptr = nullptr;

    // however, otherPtr is still a dangling pointer!

    return 0;
}
```
*/


/* Operator new can fail

- When requesting memory from the OS,  in rare circumstances, the OS may not have any memory to grant.

- By default, if new fails, a bad_alloc exception is thrown. If this exception isn’t properly handled,
  the program will simply crash.
- Alternatively, we can use return a null pointer by adding the constant std::nothrow:
    ```
    int* value { new (std::nothrow) int };
    ```
*/


/* Memory leaks

- ... when your program loses the address of some bit of dynamically allocated memory 
  before giving it back to the OS.

- The OS cannot use this memory, because the memory is considered to be still in use by your program.
*/

void exampleMemoryLeak()
{
    int* ptr{ new int{} };

    // forget to `delete ptr;` here
} // ptr goes out of scope, we lost the address of the memory we allocated


void exampleMemoryLeak2()
{
    int value = 5;
    int* ptr{ new int{} }; // allocate memory
    // forget to `delete ptr;` here
    ptr = &value; // old address lost, memory leak results
}


/* References

- https://www.learncpp.com/cpp-tutorial/dynamic-memory-allocation-with-new-and-delete/
*/