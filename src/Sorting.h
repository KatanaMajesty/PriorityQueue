#pragma once

#include <algorithm>
#include <iostream>

template <typename Iterator> void SiftDown(Iterator iter, Iterator first, Iterator last)
{
	auto index = std::distance(first, iter);

	// check if leaf -> return if so
	Iterator leftChild = first + (2 * index + 1);
	Iterator rightChild = first + (2 * index + 2);
	if (leftChild > last)
	{
		return;
	}

	Iterator child = leftChild;
	if (!(rightChild > last))
	{
		child = std::max(leftChild, rightChild,
			[](const Iterator& lhs, const Iterator& rhs) -> bool
			{
				return *lhs < *rhs;
			});
	}

	if (*iter < *child)
	{
		std::iter_swap(iter, child);
		iter = child;
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
	while (first != iter)
	{
		PopHeap(first, iter);
		// std::cout << *last << std::endl;
		iter--;
	}
	std::reverse(first, last);
}