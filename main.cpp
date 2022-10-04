#include "myarray.hpp"
#include "myvector.hpp"

class TestClass {
public:
	TestClass(int val)
	{
		m_val = val;
	}

	int val()
	{
		return m_val;
	}

private:
	int m_val = 0;
};

int main()
{
	ms::vector<ms::vector<int>> test(2, ms::vector<int>(3, 1));
	std::cout << test << std::endl;

	ms::vector<ms::vector<int>> test2 = test;
	std::cout << test2 << std::endl;

	test.push_back(ms::vector<int>(2, 1));
	std::cout << test << std::endl;

	test.swap(test2);
	std::cout << test << std::endl;

	test.pop_back();
	std::cout << test << std::endl;
	test.clear();
	test.shrink_to_fit();
	std::cout << test.size() << " " << test.capacity() << std::endl;

	ms::vector<TestClass> test3(1, TestClass(2));
	std::cout << test3.at(0).val() << std::endl;

	return 0;
}