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

- For template classes, template member functions defined outside the class are almost always defined inside the header file, 
  beneath the class definition. Because, the compiler needs to see the full template definition in order to instantiate it.
*/

/*

- https://www.learncpp.com/cpp-tutorial/classes-and-header-files/
*/