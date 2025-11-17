#include <iostream>
#include <memory> // for std::unique_ptr

int main()
{
        std::unique_ptr<int> res{ new int { 6 } };

        if (res)    // make sure res contains a Resource
        {
            std::cout << *res << '\n';  // dereference operator*
        }
}