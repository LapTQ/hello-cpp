/* 
- So far, all of the I/O examples you have seen have been writing to cout or reading from cin.
- There are six stream classes for strings: istringstream, ostringstream, stringstream, wistringstream, wostringstream, and wstringstream.
*/

// To use the stringstreams, you need to #include the sstream header.
#include <iostream>
#include <sstream> 
#include <string>

int func1()
{
    std::stringstream os {};

    // Insertion
    os << "Hello, world!";  // insert "Hello, world!" into the stream
    os << 5;                // insert the number 5 into the stream
    std::cout << os.str() << '\n'; // print: Hello, world!5

    os.str("LapTQ hello");    // set the buffer to "LapTQ hello"
    std::cout << os.str() << '\n'; // print: LapTQ hello


    // clear the stream
    os.str("");     // by setting the buffer to an empty string
    os.str(std::string {}); // by setting the buffer to a blank std::string


    // reset any error flags
    os.clear();


    // // Extraction
    std::string str1 {};
    std::string str2 {};
    os.str("LapTQ hello");
    os >> str1 >> str2; 
    std::cout << str1 << " - " << str2 << '\n'; // print: LapTQ - hello


    // insertion and extraction operators know how to work with all of the basic data types
    int nValue { 12345 };
    double dValue { 67.89 };
    os.str("");
    os.clear();
    os << nValue << ' ' << dValue;
    os >> str1 >> str2;
    std::cout << str1 << " - " << str2 << '\n'; // print: 12345 - 67.89
    
    os.str("24 0.5");
    os.clear();
    os >> nValue >> dValue;
    std::cout << nValue << " - " << dValue << '\n'; // print: 24 - 5


    return 0;
}


int main()
{
    func1();

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/input-and-output-io-streams/
- https://www.learncpp.com/cpp-tutorial/input-with-istream/
- https://www.learncpp.com/cpp-tutorial/output-with-ostream-and-ios/
- https://www.learncpp.com/cpp-tutorial/stream-classes-for-strings/
*/