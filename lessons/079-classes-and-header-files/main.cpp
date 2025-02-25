/*
- as classes get longer and more complicated, having all the member function definitions 
  inside the class can make the class harder to manage and work with.

- C++ allows us to separate the “declaration” portion of the class from the “implementation” portion 
  by defining member functions outside of the class definition.
*/


/* Putting class definitions in a header file

- Unlike functions, which only need a forward declaration to be used,
  header files usually contain the full definition of a class.

- Member functions defined inside the class definition are implicitly inline.
  => exempt from the ODR.
- Member functions defined outside the class definition are not implicitly inline.
  => must be explicitly marked as inline if you want to define them in a header file.
  => why such functions are usually defined in a .cpp file.
*/


/* Splitting up template classes

- With non-template classes, the common procedure is to put the class definition in a header file, 
  and the member function definitions in a similarly named code file. 
  However, with templates, this does not work, we’ll get a linker error: https://www.learncpp.com/cpp-tutorial/template-classes/#:~:text=Splitting%20up%20template%20classes

- Solution 1: Put the entire template class in a header file.
    Downside: increase your compile and link times.
- Solution 2: move the contents of .cpp to a new file named .inl, and include the .inl file 
    at the end of the header file (inside the header guard).
    That yields the same result as putting all the code in the header, but helps keep things a little more organized.
- Solution 3: use a three-file approach: header file, code file, and explicit instantiation file.
    For example: Array.h, Array.cpp, and templates.cpp.
    
    Other code files that want to use these types can include Array.h (to satisfy the compiler), 
    and the linker will link in these explicit type definitions from template.cpp.

    => more efficient, but requires more files.
*/

/*

- https://www.learncpp.com/cpp-tutorial/classes-and-header-files/
- https://www.learncpp.com/cpp-tutorial/template-classes/

*/