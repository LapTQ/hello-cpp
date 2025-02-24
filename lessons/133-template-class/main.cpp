
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


/* References

- https://www.learncpp.com/cpp-tutorial/template-classes/
*/