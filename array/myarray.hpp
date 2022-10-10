#pragma once

#include <iostream>

namespace ms {

	template <class Type, size_t Size>
	class array {
	public:
		array()
		{

		}

		array(const Type& initData)
		{
			for (size_t i = 0; i < Size; i++)
				m_data[i] = initData;
		}

		size_t size()
		{
			return Size;
		}

		Type& at(size_t pos)
		{
			if (pos >= Size)
				throw std::out_of_range("array index is out of range");

			return m_data[pos];
		}

		Type& operator[](size_t pos)
		{
			return m_data[pos];
		}

	private:
		Type m_data[Size];
	};

	template <class Type, size_t Size>
	std::ostream& operator<<(std::ostream& stream, array<Type, Size>& obj)
	{
		for (size_t i = 0; i < Size; i++) {
			stream << obj[i];
			if (i != Size - 1)
				stream << " ";
		}

		return stream;
	}
};
