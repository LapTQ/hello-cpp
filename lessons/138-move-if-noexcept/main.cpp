/*
- we covered std::move, which casts its lvalue argument to an rvalue so that we can invoke move semantics.
- We also covered the strong exception guarantee. In particular, all constructors should uphold the 
  strong exception guarantee, so that the rest of the program won’t be left in an altered state if construction of an object fails.
*/


/* The move constructors exception problem

- Consider the case where we are copying some object, and the copy fails for some reason.
  In such a case, the object being copied is not harmed in any way. 
- Now consider the case where we are instead moving an object. If the move operation is interrupted 
  by an exception after the transfer of ownership occurs, then our source object will be left in a modified state.
  => for non-temporary objects, we’ve now damaged the source object. 
*/


/* std::move_if_noexcept to the rescue

- std::move_if_noexcept is a counterpart to std::move, and is used in the same way.
- std::move_if_noexcept() is used to determine whether a move or a copy should be performed. 
- std::move_if_noexcept will return a movable r-value if the object has a noexcept move constructor, 
  otherwise it will return a copyable l-value. 
  We can use the noexcept specifier in conjunction with std::move_if_noexcept to use move semantics 
  only when a strong exception guarantee exists (and use copy semantics otherwise).
*/


/* References

- https://www.learncpp.com/cpp-tutorial/stdmove_if_noexcept/
*/