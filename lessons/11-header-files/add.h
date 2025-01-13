/*
- header files only consist of two parts:
++ A header guard
++ forward declarations
*/

// 1) We really should have a header guard here, but will omit it for simplicity

// 2) declarations
int add(int x, int y);

/*
- You should avoid putting function or variable "definitions" in header files.
  Doing so will generally result in a violation of the one-definition rule (ODR) in cases 
  where the header file is included into more than one source file.
*/