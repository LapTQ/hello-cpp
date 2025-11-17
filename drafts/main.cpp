
#include <algorithm> // for std::copy
#include <cassert> // for assert()
#include <initializer_list> // for std::initializer_list
#include <iostream>

class Element
{
private:
    int m_value{};
public:
    Element(int value = 0) : m_value{ value } {}
    
    // overload <<
    friend std::ostream& operator<<(std::ostream& out, const Element& elem)
    {
        out << elem.m_value;
        return out;
    }
};

class MyArray
{
private:
	int m_length {};
	Element* m_data{};

public:
	MyArray() = default;

	MyArray(int length)
		: m_length{ length }
		, m_data{ new Element[static_cast<std::size_t>(length)] {} }
	{

	}

	MyArray(std::initializer_list<Element> list) // allow MyArray to be initialized via list initialization
		: MyArray(static_cast<int>(list.size()))
	{
		std::copy(list.begin(), list.end(), m_data);
	}

	~MyArray()
	{
		delete[] m_data;
		// we don't need to set m_data to null or m_length to 0 here, since the object will be destroyed immediately after this function anyway
	}

	MyArray(const MyArray&) = delete; // to avoid shallow copies
	MyArray& operator=(const MyArray& list) = delete; // to avoid shallow copies

	Element& operator[](int index)
	{
		assert(index >= 0 && index < m_length);
		return m_data[index];
	}

	int getLength() const { return m_length; }
};

int main()
{
	MyArray array{ Element{1}, Element{2}, Element{3}}; // initializer list
	for (int count{ 0 }; count < array.getLength(); ++count)
		std::cout << array[count] << ' ';

	return 0;
}