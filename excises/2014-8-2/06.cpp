#include <iostream>
#include <stdlib.h>
using namespace std;

class int_array
{
public:
	int_array(int number_of_elements = 10);
	int_array(int_array const &array);
	~int_array();
	int_array const& operator=(int_array const &array);
	int &operator[](int index);
private:
	int number_of_elements;
	int* data;
	void check_index(int index) const;
	void copy_array(int_array const &array);
};

int_array::int_array(int n)
{
	if (n < 1)
	{
		cerr << "number od elements cannot be " << n << ", must be >= 1" << endl;
		exit(1);
	}
	number_of_elements = n;
	data = new int [number_of_elements];
	for (int i = 0; i < number_of_elements; ++i)
	{
		data[i] = 0;
	}
}

int_array::int_array(int_array const & array)
{
	copy_array(array);
}

int_array::~int_array()
{
	delete[] data;
}

int_array const &int_array::operator=(int_array const &array)
{
	if (this != &array)
	{
		delete[] data;
		copy_array(array);
	}
	return *this;
}

int &int_array::operator[](int index)
{
	check_index(index);
	return data[index];
}

void int_array::copy_array(int_array const &array)
{
	number_of_elements = array.number_of_elements;
	data = new int [number_of_elements];
	for (int i = 0; i < number_of_elements; i++)
	{
		data[i] = array.data[i];
	}
}

void int_array::check_index(int index) const
{
	if (index < 0 || index >= number_of_elements)
	{
		cerr << "invalid index " << index << ", range is 0 to " << number_of_elements - 1 << endl;
		exit(1);
	}
}

int main(int argc, char const *argv[])
{
	int_array a(15);
	int i;
	for (int i = 0; i < 15; ++i)
	{
		cout << a[i] << ' ';
	}
	cout << endl;
	for (int i = 0; i < 15; ++i)
	{
		a[i] = i * 10;
	}
	for (int i = 0; i < 15; ++i)
	{
		cout << a[i] << ' ';
	}
	cout << endl;
	exit(0);
	return 0;
}