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

#include <vector>

int main()
{
	ms::array<int, 5> intArray(9);
	std::cout << "Test #1: (create an array of ints)" << std::endl;
	std::cout << intArray << std::endl << std::endl;

	ms::array<ms::vector<int>, 3> vectorArray(ms::vector<int>(5, 4));
	std::cout << "Test #2: (create an array of vectors of ints)" << std::endl;
	std::cout << vectorArray << std::endl << std::endl;

	ms::vector<ms::vector<int>> test(2, ms::vector<int>(3, 1));
	std::cout << "Test #3: (create a vector of vectros of ints)" << std::endl;
	std::cout << test << std::endl << std::endl;
	
	test.insert(1, ms::vector<int>(2, 2));
	std::cout << "Test #4: (insert into a vector of vectros of ints)" << std::endl;
	std::cout << test << std::endl << std::endl;

	test.erase(1);
	std::cout << "Test #5: (erase from a vector of vectros of ints)" << std::endl;
	std::cout << test << std::endl << std::endl;

	ms::vector<ms::vector<int>> test2 = test;
	std::cout << "Test #6: (copy a vector of vectros of ints)" << std::endl;
	std::cout << test2 << std::endl << std::endl;

	test.push_back(ms::vector<int>(2, 1));
	std::cout << "Test #7: (push_back into a vector of vectros of ints)" << std::endl;
	std::cout << test << std::endl << std::endl;

	test.pop_back();
	std::cout << "Test #8: (pop_back from a vector of vectros of ints)" << std::endl;
	std::cout << test << std::endl << std::endl;

	test.clear();
	std::cout << "Test #9: (clear a vector of vectros of ints)" << std::endl;
	std::cout << test.size() << " " << test.capacity() << std::endl << std::endl;

	test.shrink_to_fit();
	std::cout << "Test #10: (shrink_to_fit a vector of vectros of ints)" << std::endl;
	std::cout << test.size() << " " << test.capacity() << std::endl << std::endl;

	ms::vector<TestClass> test3(1, TestClass(2));
	std::cout << "Test #11: (create a vector of TestClass objects)" << std::endl;
	std::cout << test3.at(0).val() << std::endl;

	return 0;
}
