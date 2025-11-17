#include <iostream>

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
    Resource* ptr = new Resource();

    // return 0; // the function returns early, and ptr won’t be deleted!

    delete ptr;
} // => memory leak