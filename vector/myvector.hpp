#pragma once

#include <cstdlib>
#include <algorithm>
#include <iostream>

namespace ms {
	
	template <class T>
	class vector {
	public:
		/* Constructor & Destructor */

		vector()
		{

		}

		vector(size_t initSize)
		{
			m_size = 0;
			m_capacity = initSize;
			m_charData = new char[m_capacity * sizeof (T)];
			m_data = (T*)m_charData;

			if (!m_data && initSize) throw std::bad_alloc();
		}

		vector(size_t initSize, const T& value)
		{
			m_size = initSize;
			m_capacity = initSize;

			m_charData = new char[m_capacity * sizeof (T)];
			m_data = (T*)m_charData;

			if (!m_data && initSize) throw std::bad_alloc();

			for (size_t i = 0; i < m_size; i++)
				new (m_data + i) T(value);
		}

		~vector()
		{
			for (size_t i = 0; i < m_size; i++)
				m_data[i].~T();
			delete [] m_charData;
		}

		/* Operators */

		vector(vector&& other)
		{
			m_size = other.size();
			m_capacity = other.capacity();
			
			m_charData = new char[m_capacity * sizeof (T)];
			m_data = (T*)m_charData;

			if (!m_data && m_capacity) throw std::bad_alloc();

			for (size_t i = 0; i < m_size; i++)
				new (m_data + i) T(other.data()[i]);
		}

		vector(const vector& other)
		{
			m_size = other.size();
			m_capacity = other.capacity();
			
			m_charData = new char[m_capacity * sizeof (T)];
			m_data = (T*)m_charData;
			
			if (!m_data && m_capacity) throw std::bad_alloc();

			for (size_t i = 0; i < m_size; i++)
				new (m_data + i) T(other.data()[i]);
		}

		vector& operator=(const vector& other)
		{
			this->~vector();

			m_size = other.size();
			m_capacity = other.capacity();

			m_charData = new char[m_capacity * sizeof (T)];
			m_data = (T*)m_charData;

			if (!m_data && m_capacity) throw std::bad_alloc();

			for (size_t i = 0; i < m_size; i++)
				new (m_data + i) T(other.data()[i]);

			return *this;
		}

		/* Capacity */

		bool empty() const
		{
			return m_size == 0;
		}

		size_t size() const
		{
			return m_size;
		}


		void reserve(size_t newCapacity)
		{
			if (newCapacity <= m_capacity)
				return;

			char* newCharData = new char[newCapacity * sizeof (T)];
			T* newData = (T*)newCharData;

			if (!m_data && m_capacity) throw std::bad_alloc();

			for (size_t i = 0; i < m_size; i++)
				new (newData + i) T(m_data[i]);

			this->~vector();

			m_capacity = newCapacity;
			m_charData = newCharData;
			m_data = newData;

		}

		size_t capacity() const
		{
			return m_capacity;
		}

		void shrink_to_fit()
		{
			if (m_capacity <= m_size)
				return;

			char* newCharData = new char[m_size * sizeof (T)];
			T* newData = (T*)newCharData;

			if (!m_data && m_capacity) throw std::bad_alloc();
			
			for (size_t i = 0; i < m_size; i++)
				new (newData + i) T(m_data[i]);

			this->~vector();

			m_capacity = m_size;
			m_charData = newCharData;
			m_data = newData;
		}

		/* Element access */

		T& at(size_t pos) const
		{
			if (pos >= m_size) {
				std::string posStr  = std::to_string(pos);
				std::string sizeStr = std::to_string(m_size);

				std::string errorMsg = "vector range check failed: index ("  + posStr + ")" +
				                       " >= size (" + sizeStr + ")";				
				throw std::out_of_range(errorMsg);
			}
			return m_data[pos];
		}

		T& operator[](size_t pos) const
		{
			return m_data[pos];
		}

		T& front() const
		{
			return m_data[0];
		}

		T& back() const
		{
			return m_data[m_size - 1];
		}

		T* data() const
		{
			return m_data;
		}

		/* Modifiers */

		void clear()
		{
			for (size_t i = 0; i < m_size; i++)
				m_data[i].~T();

			m_size = 0;
		}

		T& insert(size_t pos, const T& value)
		{

		}

		T& erase(size_t pos)
		{

		}

		void push_back(const T& value)
		{
			if (m_capacity == 0) {
				this->reserve(1);
				m_capacity = 1;
			}

			if (m_size >= m_capacity) {
				this->reserve(m_capacity << 1);
				m_capacity <<= 1;
			}

			new (m_data + m_size) T(value);
			m_size++;
		}

		void pop_back()
		{
			if (!m_size)
				return;

			m_size--;
			m_data[m_size].~T();

			if (m_size <= (m_capacity >> 1))
				this->shrink_to_fit();
		}

		void resize(size_t count)
		{

		}

		void swap(vector& other)
		{
			vector<T> temp = other;
			other = *this;
			*this = temp;
		}

	private: 
		size_t m_size = 0;
		size_t m_capacity = 0;
		T* m_data = nullptr;
		char* m_charData = nullptr;
	};

	template <class T>
	std::ostream& operator<<(std::ostream& stream, vector<T>& obj)
	{
		for (size_t i = 0; i < obj.size(); i++) {
			stream << obj.at(i);
			if (i != obj.size() - 1)
				stream << " ";
		}

		return stream;
	}
};
