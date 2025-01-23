/* constexpr if statement

- Normally, the conditional of an if-statement is evaluated at runtime.
- C++17 introduces the constexpr if statement, which requires the conditional to be a constant expression. 
*/


#include <iostream>
#define PASS

int main() 
{   
    // null statement
    int x{ 5 };
    if (x > 10)
        ; // this is a null statement
    
    if (x > 10); // be careful, this is also a null statement (pay attention to the ";")
        x;  // this is not part of the if statement

    // mimic Python' null statement
    if (x > 10)
        PASS;

    
    // constexpr if statement
	constexpr double gravity{ 9.8 };
	if constexpr (gravity == 9.8) // now using constexpr if
		std::cout << "Gravity is normal.\n";
}

/* References

- https://www.learncpp.com/cpp-tutorial/constexpr-if-statements/
*/