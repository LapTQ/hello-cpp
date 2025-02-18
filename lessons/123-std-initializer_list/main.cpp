/* Class initialization using std::initializer_list

Consider initialization using initializer lists syntax:
```
int array[] { 5, 4, 3, 2, 1 };
auto* array{ new int[5]{ 5, 4, 3, 2, 1 } };
```

- When a compiler sees an initializer list, it automatically converts it into an object of type std::initializer_list.
- Therefore, if we create a constructor that takes a std::initializer_list parameter, we can create objects using the initializer list as an input.

- std::initializer_list has a (misnamed) size() function which returns the number of elements in the list.
- std::initializer_list is often passed by value. Much like std::string_view, std::initializer_list is a view. 
  Copying a std::initializer_list does not copy the elements in the list.
*/

#include <algorithm> // for std::copy
#include <cassert> // for assert()
#include <initializer_list> // for std::initializer_list
#include <iostream>

class IntArray
{
private:
	int m_length {};
	int* m_data{};

public:
	IntArray() = default;

	IntArray(int length)
		: m_length{ length }
		, m_data{ new int[static_cast<std::size_t>(length)] {} }
	{

	}

	IntArray(std::initializer_list<int> list) // allow IntArray to be initialized via list initialization
		: IntArray(static_cast<int>(list.size()))
	{
		std::copy(list.begin(), list.end(), m_data);
	}

	~IntArray()
	{
		delete[] m_data;
		// we don't need to set m_data to null or m_length to 0 here, since the object will be destroyed immediately after this function anyway
	}

	IntArray(const IntArray&) = delete; // to avoid shallow copies
	IntArray& operator=(const IntArray& list) = delete; // to avoid shallow copies

	int& operator[](int index)
	{
		assert(index >= 0 && index < m_length);
		return m_data[index];
	}

	int getLength() const { return m_length; }
};

int func1()
{
	IntArray array{ 5, 4, 3, 2, 1 }; // initializer list
	for (int count{ 0 }; count < array.getLength(); ++count)
		std::cout << array[count] << ' ';

	return 0;
}


/* Accessing elements of a std::initializer_list

- For some inexplicable reason, std::initializer_list does not provide access to the elements of the list via subscripting (operator[])
- Solution: https://www.learncpp.com/cpp-tutorial/stdinitializer_list/#:~:text=Accessing%20elements%20of%20a%20std%3A%3Ainitializer_list
*/


/* List initialization prefers list constructors over non-list constructors

=> best practice:
- Use brace initialization when intending to call the list constructor.
- Use direct initialization when intending to call a non-list constructor .
*/


/* Class assignment using std::initializer_list

- You can also use std::initializer_list to assign new values to a class by overloading the assignment operator to take a std::initializer_list parameter.

Note that if you implement a constructor that takes a std::initializer_list, you should ensure you do at least one of the following:
- Provide an overloaded list assignment operator
- Provide a proper deep-copying copy assignment operator
- Delete the copy assignment operator
Here's why: consider the following code (which doesn’t have any of these things):
*/

class IntArray2
{
private:
	int m_length{};
	int* m_data{};

public:
	IntArray2() = default;

	IntArray2(int length)
		: m_length{ length }
		, m_data{ new int[static_cast<std::size_t>(length)] {} }
	{

	}

	IntArray2(std::initializer_list<int> list)
		: IntArray2(static_cast<int>(list.size()))
	{
		std::copy(list.begin(), list.end(), m_data);
	}

	~IntArray2()
	{
		delete[] m_data;
	}

//	IntArray2(const IntArray2&) = delete; // to avoid shallow copies
//	IntArray2& operator=(const IntArray2& list) = delete; // to avoid shallow copies

	int& operator[](int index)
	{
		assert(index >= 0 && index < m_length);
		return m_data[index];
	}

	int getLength() const { return m_length; }
};

int func2()
{
	IntArray2 array{};
	array = { 1, 3, 5, 7, 9, 11 }; // Here's our list assignment statement

	for (int count{ 0 }; count < array.getLength(); ++count)
		std::cout << array[count] << ' '; // undefined behavior

	return 0;
}

/*
- First, the compiler will note that an assignment function taking a std::initializer_list doesn’t exist.
- Then, it discovers the implicitly provided copy assignment operator.
- However, this function can only be used if it can convert the initializer list into an IntArray.
- Because { 1, 3, 5, 7, 9, 11 } is a std::initializer_list, the compiler will use the list constructor to convert the initializer list into a temporary IntArray.
- Then it will call the implicit assignment operator, which will shallow copy the temporary IntArray into our array object.
- At the end of the assignment statement, the temporary IntArray is destroyed, this leaves array->m_data as a dangling pointer.
*/


int main()
{
    // Class initialization using std::initializer_list
    func1();


    // Class assignment using std::initializer_list
    func2();

    return 0;
}



/* References

- https://www.learncpp.com/cpp-tutorial/stdinitializer_list/
*/