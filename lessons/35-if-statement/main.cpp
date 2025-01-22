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
}