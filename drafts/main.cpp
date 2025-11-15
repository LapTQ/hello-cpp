#include <algorithm> // for std::max and std::copy_n
#include <iostream>

class MyArray
{
private:
	int* m_data {};
	int m_len {};

public:
	MyArray(const int* data = nullptr, int len = 0 )
		: m_len { len }
	{
        m_data = new int[static_cast<std::size_t>(len)];
        std::copy_n(data, len, m_data); // copy len elements of data into m_data
	}
	~MyArray()
	{
		delete[] m_data;
	}

	// Overloaded assignment    (don't use this version)
	MyArray& operator= (const MyArray& str)
    {
        // if data exists in the current string, delete it
        if (m_data) delete[] m_data;        // m_data will be dangling if self-assignment occurs

        m_len = str.m_len;
        m_data = nullptr;

        m_data = new int[static_cast<std::size_t>(str.m_len)];

        std::copy_n(str.m_data, m_len, m_data);

        return *this;
    }
};

MyArray alex("Alex", 5);
alex = alex;        // self-assignment