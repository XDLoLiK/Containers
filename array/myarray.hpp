#pragma once

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>

namespace ms {

	template <class T, size_t S>
	class array {
	public:
		array()
		{

		}

		array(const T& initData)
		{
			for (size_t i = 0; i < S; i++)
				m_data[i] = initData;
		}

		size_t size()
		{
			return S;
		}

		T& at(size_t pos)
		{
			if (pos >= S) {
				std::string posStr  = std::to_string(pos);
				std::string sizeStr = std::to_string(S);

				std::string errorMsg = "array range check failed: index ("  + posStr + ")" +
				                       " >= size (" + sizeStr + ")";
				throw std::out_of_range(errorMsg);
			}
			return m_data[pos];
		}

		T& operator[](size_t pos)
		{
			return m_data[pos];
		}

	private:
		T m_data[S];
	};

	template <class T, size_t S>
	std::ostream& operator<<(std::ostream& stream, array<T, S>& obj)
	{
		for (size_t i = 0; i < S; i++) {
			stream << obj[i];
			if (i != S - 1)
				stream << " ";
		}

		return stream;
	}
};
