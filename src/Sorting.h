#pragma once

#include <algorithm>
#include <iostream>

template <typename Iterator> void SiftDown(Iterator iter, Iterator first, Iterator last)
{
	auto index = std::distance(first, iter);
	Iterator leftChild = first + (2 * index + 1);
	Iterator rightChild = first + (2 * index + 2);
	Iterator child = leftChild;
	// while is not a leaf
	while (leftChild <= last)
	{
		child = leftChild;
		if (!(rightChild > last))
		{
			child = std::max(leftChild, rightChild,
				[](const Iterator& lhs, const Iterator& rhs) -> bool
				{
					return *lhs < *rhs;
				});
		}

		if (*iter > *child)
		{
			break;
		}
		std::iter_swap(iter, child);
		iter = child;
		
		index = std::distance(first, iter);
		leftChild = first + (2 * index + 1);
		rightChild = first + (2 * index + 2);
	}
	
}

template <typename Iterator> void MakeHeap(Iterator first, Iterator last)
{
	// we start from container::end() - 1 and finish, when crossed container::begin()
	last = last - 1;
	for (Iterator iter = last; iter != first - 1; --iter)
	{
		SiftDown(iter, first, last);
	}
}

template <typename Iterator> void PopHeap(Iterator first, Iterator last)
{
	// we can access last - 1 here, assuming last - 1 != end
	std::iter_swap(first, last - 1);
	SiftDown(first, first, last - 2); // pass extra iterator
}

template <typename Iterator> void HeapSortInplace(Iterator first, Iterator last)
{
	Iterator iter = last;
	MakeHeap(first, last);
	while (first != iter)
	{
		PopHeap(first, iter--);
	}
	std::reverse(first, last);
}