/* C++ templates

- Unlike a normal definition (where all types must be specified).
- Once a template is defined, the compiler can generate as many overloaded functions 
  as needed, each using different actual types!
- template code can be used with types that didn’t even exist when the template was written!

- The initial function template is called the "primary template".
  The functions generated from the primary template are called "specializations".
*/


// template parameter declaration
template <typename T> // tell the compiler: this is a template, and T is a type template parameter
T max(T x, T y)
{
    return (x < y) ? y : x;
}
// The scope of a template parameter declaration is strictly limited to the function template that follows.


/* typename vs class

- keyword typename (preferred) or class can be used to declare type template parameters.
- There is no difference between them in this context, but we prefer typename because it makes
  it clearer that any type (such as fundamental type) can be used, not just class types.
*/

/* References 

- https://www.learncpp.com/cpp-tutorial/function-templates/
*/