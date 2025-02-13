/* Self-assignment

- Read: https://www.learncpp.com/cpp-tutorial/overloading-the-assignment-operator/#:~:text=Issues%20due%20to%20self%2Dassignment
- Handle self-assignment:
    + self-assignment guard
    + The copy and swap idiom
*/


/* The implicit copy assignment operator

- Unlike other operators, the compiler will provide an implicit public copy assignment operator for your class if you do not provide a user-defined one. 
- This assignment operator does memberwise assignment (essentially the same as the memberwise initialization that default copy constructors do).

- Just like other constructors and operators, you can prevent assignments by making your copy assignment operator private or using the `delete` keyword.
- if your class has const members, the compiler will instead define the implicit operator= as deleted.
*/


/* References

- https://www.learncpp.com/cpp-tutorial/overloading-the-assignment-operator/
*/