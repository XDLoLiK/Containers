#pragma once

#include <iostream>

namespace ms {
	/* ms::vector */

	template <class Type>
	static inline size_t release(Type* data, size_t start, size_t end)
	{
		for (size_t i = start; i < end; i++)
			data[i].~Type();

		return end - start;
	}

	template <class Type>
	static inline size_t initialize(Type* data, size_t start, size_t end, const Type& value)
	{
		size_t curSize = start;

		try {
			for ( ; curSize < end; curSize++)
				new (data + curSize) Type(value);
		}
		catch (...) {
			release(data, start, curSize);
			throw;
		}

		return end - start;
	}

	template <class Type>
	static inline size_t copy(Type* dest, size_t start, size_t end, const Type* src)
	{
		size_t curSize = start;

		try {
			for ( ; curSize < end; curSize++)
				new (dest + curSize) Type(src[curSize]);
		}
		catch (...) {
			release(dest, start, curSize);
			throw;
		}

		return end - start;
	}

	inline size_t closestPowerOfTwo(size_t number)
	{
		return 1ull << (sizeof number * 8 - (size_t)__builtin_clzl(newSize));
	}

	template <class Type>
	class vector {
	public:
		/* Constructor & Destructor */

		vector():
			m_size(0),
			m_capacity(0),
			m_charData(nullptr),
			m_data(nullptr)
		{

		}

		vector(size_t initSize, const Type& value = Type()):
			m_size(0),
			m_capacity(0),
			m_charData(nullptr),
			m_data(nullptr)
		{
			try {
				m_charData = new char[initSize * sizeof (Type)]();
				m_data     = (Type*)m_charData;
				m_capacity = initSize;

				initialize(m_data, 0, initSize, value);
				m_size = initSize;
			}
			catch (...) {
				this->~vector();
				throw;
			}
		}

		~vector()
		{
			for (size_t i = 0; i < m_size; i++)
				m_data[i].~Type();

			delete [] m_charData;

			m_size     = 0;
			m_capacity = 0;

			m_charData = nullptr;
			m_data     = nullptr;
		}

		/* Operators */

		vector(const vector& other):
			m_size(0),
			m_capacity(0),
			m_charData(nullptr),
			m_data(nullptr)
		{
			try {
				m_charData = new char[other.capacity() * sizeof (Type)]();
				m_data     = (Type*)m_charData;
				m_capacity = other.capacity();

				copy(m_data, 0, other.size(), other.data());
				m_size = other.size();
			}
			catch (...) {
				this->~vector();
				throw;
			}
		}

		vector& operator=(vector other)
		{
			this->swap(other);
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

		size_t capacity() const
		{
			return m_capacity;
		}

		void reserve(size_t newCapacity)
		{
			if (newCapacity <= m_capacity)
				return;

			char* newCharData = nullptr;
			Type* newData     = nullptr;

			try {
				newCharData = new char[newCapacity * sizeof (Type)];
				newData     = (Type*)newCharData;

				size_t newSize = copy(newData, 0, m_size, m_data);
				this->~vector();

				m_size     = newSize;
				m_capacity = newCapacity;
				m_charData = newCharData;
				m_data     = newData;
			}
			catch (...) {
				delete [] newCharData;
				this->~vector();
				throw;
			}
		}

		void shrink_to_fit()
		{
			if (m_capacity <= m_size)
				return;

			char* newCharData = nullptr;
			Type* newData     = nullptr;

			try {
				newCharData = new char[m_size * sizeof (Type)];
				newData     = (Type*)newCharData;

				size_t newSize = copy(newData, 0, m_size, m_data);
				this->~vector();

				m_size     = newSize;
				m_capacity = newSize;
				m_charData = newCharData;
				m_data     = newData;
			}
			catch (...) {
				delete [] newCharData;
				this->~vector();
				throw;
			}
		}

		/* Element access */

		const Type& at(size_t pos) const
		{
			Type& ret = const_cast<vector<Type>*>(this)->at(pos);
			return const_cast<const Type&>(ret);
		}

		Type& at(size_t pos)
		{
			if (pos >= m_size)
				throw std::out_of_range("vector index is out of range");

			return m_data[pos];
		}

		const Type& operator[](size_t pos) const
		{
			Type& ret = const_cast<vector<Type>*>(this)->operator[](pos);
			return const_cast<const Type&>(ret);
		}

		Type& operator[](size_t pos)
		{
			return m_data[pos];
		}

		const Type& front() const
		{
			return const_cast<const Type&>(m_data[0]);
		}

		Type& front()
		{
			return m_data[0];
		}

		const Type& back() const
		{
			return const_cast<const Type&>(m_data[m_size - 1]);
		}

		Type& back()
		{
			return m_data[m_size - 1];
		}

		const Type* data() const
		{
			return const_cast<const Type*>(m_data);
		}

		Type* data()
		{
			return m_data;
		}

		/* Modifiers */

		void clear()
		{
			for (size_t i = 0; i < m_size; i++)
				m_data[i].~Type();

			m_size = 0;
		}

		Type& insert(size_t pos, const Type& value)
		{
			pos = (pos > m_size) ? m_size : pos;
			size_t newCapacity = 1ull << (sizeof m_size * 8 - 
				                         (size_t)__builtin_clzl(m_size + 1));
			this->reserve(newCapacity);

			try {
				new (m_data + m_size) Type(value);
				for (size_t i = m_size; i > pos; i--)
					m_data[i] = m_data[i - 1];

				m_data[pos] = value;
				m_size++;
			}
			catch (...) {
				m_size++;
				this->~vector();
				throw;
			}

			return m_data[pos];
		}

		void erase(size_t pos)
		{
			if (pos >= m_size)
				return;

			try {
				for (size_t i = pos; i < m_size - 1; i++)
					m_data[i] = m_data[i + 1];

				m_size--;
				m_data[m_size].~Type();	
			}
			catch (...) {
				this->~vector();
				throw;
			}
		}

		void push_back(const Type& value)
		{
			this->insert(m_size, value);
		}

		void pop_back()
		{
			if (!m_size)
				return;

			this->erase(m_size - 1);
		}

		void resize(size_t newSize, const Type& value = Type())
		{
			if (m_size > newSize) {
				for ( ; m_size > newSize; m_size--)
					m_data[m_size - 1].~Type();
			}
			else if (m_size < newSize) {
				newSize = (newSize > m_MAX_SIZE) ? (m_MAX_SIZE) : newSize;
				size_t newCapacity = closestPowerOfTwo(newSize)
				this->reserve(newCapacity);

				try {
					initialize(m_data, 0, newSize, value);
					m_size = newSize;
				}
				catch (...) {
					this->~vector();
					throw;
				}
			}
		}

		void swap(vector& other)
		{
			std::swap(m_size,     other.m_size);
			std::swap(m_capacity, other.m_capacity);
			std::swap(m_charData, other.m_charData);
			std::swap(m_data,     other.m_data);
		}

	private:
		static const size_t m_MAX_SIZE = 1ull << 32;

		size_t m_size     = 0;
		size_t m_capacity = 0;

		char* m_charData  = nullptr;
		Type* m_data      = nullptr;
	};

	template <class Type>
	std::ostream& operator<<(std::ostream& stream, vector<Type>& obj)
	{
		for (size_t i = 0; i < obj.size(); i++) {
			stream << obj.at(i);
			if (i != obj.size() - 1)
				stream << " ";
		}

		return stream;
	}
};
