#pragma once

#include <cstddef>
#include <iterator>

class MyStringConstIterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using difference_type = ptrdiff_t;
	using value_type = char;
	using pointer = value_type*;
	using reference = value_type&;

	using MyStringConstReverseIterator = std::reverse_iterator<MyStringConstIterator>;

public:
	MyStringConstIterator();
	MyStringConstIterator(pointer ptr);

	reference operator*() const;
	pointer operator->() const;
	MyStringConstIterator& operator++();
	MyStringConstIterator operator++(int);
	MyStringConstIterator& operator--();
	MyStringConstIterator operator--(int);
	MyStringConstIterator& operator+=(const difference_type offset);
	MyStringConstIterator operator+(const difference_type offset) const;
	MyStringConstIterator& operator-=(const difference_type offset);
	MyStringConstIterator operator-(const difference_type offset) const;
	difference_type operator-(const MyStringConstIterator& other) const;
	reference operator[](const difference_type offset) const;
	bool operator==(const MyStringConstIterator& other) const;
	bool operator!=(const MyStringConstIterator& other) const;
	bool operator<(const MyStringConstIterator& other) const;
	bool operator>(const MyStringConstIterator& other) const;
	bool operator<=(const MyStringConstIterator& other) const;
	bool operator>=(const MyStringConstIterator& other) const;

private:
	pointer m_ptr;
};

class MyStringIterator : public MyStringConstIterator
{
public:
	using MyStringReverseIterator = std::reverse_iterator<MyStringIterator>;

	MyStringIterator();
	MyStringIterator(pointer ptr);

	reference operator*() const;
	pointer operator->() const;
	MyStringIterator& operator++();
	MyStringIterator operator++(int);
	MyStringIterator& operator--();
	MyStringIterator operator--(int);
	MyStringIterator& operator+=(const difference_type offset);
	MyStringIterator operator+(const difference_type offset) const;
	MyStringIterator& operator-=(const difference_type offset);
	MyStringIterator operator-(const difference_type offset) const;
	difference_type operator-(const MyStringIterator& other) const;
	reference operator[](const difference_type offset) const;
};
