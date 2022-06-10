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
	// constexpr SizeType Parent(SizeType index) const { return (index - 1) / 2; }
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

	void push(ConstReference& value)
	{
		m_Container.push_back(value);
		m_Size++;
		SiftUp(Size() - 1);
	}

	void push(ValueType&& value)
	{
		m_Container.push_back(std::move(value));
		m_Size++;
		SiftUp(Size() - 1);
	}

	void SiftDown(SizeType index)
	{
		// if true than this node is a leaf
		// if not, than at least left child exists
		if (IsLeaf(index))
		{
			return;
		}

		// Get left and right children
		SizeType childIndex = LeftChild(index);
		// Check if node at rightIndex exists
		if (!(childIndex + 1 >= Size()))
		{
			// ensure if right index is larger than left index
			childIndex = std::max<SizeType>(childIndex, childIndex + 1, 
				[&](const SizeType& a, const SizeType& b) -> bool
				{
					return m_Container.at(a) < m_Container.at(b);
				});
		}

		Reference child = m_Container.at(childIndex);
		Reference self = m_Container.at(index);

		if (child < self)
		{
			return;
		}

		std::swap(child, self);
		SiftDown(childIndex);
	}

	void pop()
	{
		if (this->IsEmpty())
		{
			return;
		}
		std::swap(m_Container[0], m_Container[Size() - 1]);
		m_Size--;
		m_Container.erase(m_Container.end() - 1);

		SiftDown(0);
	}

	Iterator begin() { return m_Container.begin(); }
	Iterator end() { return m_Container.end(); }
private:
	Container m_Container{};
	SizeType m_Size{};
};