#pragma once

#include <cstddef>
#include <vector>
#include <iostream>
#include <cmath>

template <typename T> concept Comparable = requires(T t) { t < t; };

template <Comparable T> class PriorityQueue
{
public:
	using ValueType = T;
	using SizeType = std::size_t;
	using Container = std::vector<ValueType>;
	using Iterator = typename Container::iterator;
	using Reference = ValueType&;
	using ConstReference = const ValueType&;

	PriorityQueue() = default;
	~PriorityQueue() = default;

	constexpr SizeType Parent(SizeType index) const { return (index - 1) / 2; }
	constexpr SizeType LeftChild(SizeType index) const { return (2 * index + 1); }
	constexpr SizeType RightChild(SizeType index) const { return LeftChild(index) + 1; }

	SizeType Size() const { return m_Size; }
	constexpr bool IsEmpty() const { return Size() == 0; }
	constexpr bool IsLeaf(SizeType index) const { return LeftChild(index) >= Size(); }
	constexpr bool IsRoot(SizeType index) const { return index == 0; }
	constexpr Reference top() { return *m_Container.begin(); }
	constexpr ConstReference top() const { return *m_Container.begin(); }

	SizeType Height() const { return std::ceil(log2f(static_cast<float>(Size()))); }

	void SiftUp(SizeType index)
	{
		if (IsRoot(index))
		{
			return;
		}
		SizeType parentIndex = Parent(index);

		Reference self = m_Container[index];
		Reference parent = m_Container[parentIndex];

		if (self < parent)
		{
			return;
		}

		std::swap(self, parent);
		SiftUp(parentIndex);
	}

	void SiftDown(SizeType index)
	{
		if (IsLeaf(index))
		{
			return;
		}
		SizeType leftIndex = LeftChild(index);
		SizeType rightIndex = leftIndex + 1;

		SizeType childIndex = leftIndex;
		if (!IsLeaf(rightIndex))
		{
			childIndex = std::min<SizeType>(leftIndex, rightIndex, 
			[&](const SizeType& a, const SizeType& b) -> bool
			{
				return m_Container[a] < m_Container[b];
			});
		}

		Reference child = m_Container[childIndex];
		Reference self = m_Container[index];

		if (child < self)
		{
			return;
		}

		std::swap(child, self);
		SiftDown(childIndex);
	}

	void push(ConstReference& value)
	{
		m_Container.push_back(value);
		m_Size++;
		SiftUp(m_Size - 1);
		
	}
	void push(ValueType&& value)
	{
		m_Container.push_back(std::move(value));
		m_Size++;
		SiftUp(m_Size - 1);
	}
	void pop()
	{
		if (this->IsEmpty())
		{
			return;
		}
		m_Size--;
		std::swap(m_Container[0], m_Container[m_Size]);
		m_Container.erase(m_Container.end() - 1);

		SiftDown(0);
	}
	Iterator begin() { return m_Container.begin(); }
	Iterator end() { return m_Container.end(); }
private:
	Container m_Container{};
	SizeType m_Size{};
};