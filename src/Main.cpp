#include <iostream>
#include <queue>
#include <PriorityQueue.h>
#include <algorithm>
#include <Sorting.h>

template <typename Queue, typename T>
float testPriorityQueueSpeed(Queue&& priorityQueue)
{
	const int iters = 100000;
	clock_t timeStart = clock();
	for (int i = 0; i < iters; i++)
	{
		int insertDataAmount = rand() % 6 + 5;
		for (int j = 0; j < insertDataAmount; j++)
		{
			priorityQueue.push(T{static_cast<float>(j)});
		}
		auto& a = priorityQueue.top();
		priorityQueue.pop();
	}
	clock_t timeEnd = clock();
	float time = (float(timeEnd - timeStart)) / CLOCKS_PER_SEC;
	return time;
}

template <typename T>
bool testPriorityQueue()
{
	srand(time(NULL));
	const int iters = 2000;
	PriorityQueue<T> myPriorQueue;
	std::priority_queue<T> stlPriorQueue;
	bool isDataEqual = true;
	for (int i = 0; i < iters; i++)
	{
		int insertDataAmount = rand() % 6 + 5;
		// std::cout << "Pushing\n";
		for (int j = 0; j < insertDataAmount; j++)
		{
			T randData = T();
			myPriorQueue.push(randData);
			stlPriorQueue.push(randData);
		}
		// std::cout << "Done pushing\n";
		if (!(myPriorQueue.top() == stlPriorQueue.top()))
		{
			isDataEqual = false;
			std::cerr << "Comparing failed on iteration " << i << std::endl << std::endl;
			break;
		}
		int removeDataAmount = rand() % insertDataAmount;
		for (int j = 0; j < removeDataAmount; j++)
		{
			myPriorQueue.pop();
			stlPriorQueue.pop();
		}
	}
	int myQueueSize = myPriorQueue.Size();
	int stlQueueSize = stlPriorQueue.size();
	float stlTime = testPriorityQueueSpeed<std::priority_queue<T>, T>(std::priority_queue<T>());
	float myTime = testPriorityQueueSpeed<PriorityQueue<T>, T>(PriorityQueue<T>());

	std::cout << "My PriorityQueue:" << std::endl;
	std::cout << "Time: " << myTime << ", size: " << myQueueSize << std::endl;
	std::cout << "STL priority_queue:" << std::endl;
	std::cout << "Time: " << stlTime << ", size: " << stlQueueSize << std::endl << std::endl;

	if (isDataEqual && myQueueSize == stlQueueSize)
	{
		std::cout << "The lab is completed" << std::endl << std::endl;
		return true;
	}

	std::cerr << ":(" << std::endl << std::endl;
	return false;
}

struct Object
{
	float distance;
	bool operator<(const Object& other) const { return this->distance < other.distance; }
	bool operator>(const Object& other) const { return !(*this < other); }
	bool operator==(const Object& other) const { return this->distance == other.distance; }
	bool operator!=(const Object& other) const { return !(*this == other); }
};

int main()
{
	testPriorityQueue<Object>();

	// Additional task
	std::vector<int> vec(20);
	std::cout << "Size: " << vec.size() << std::endl;
	std::generate(vec.begin(), vec.end(), []() -> int
	{
		return rand() % 123;
	});
	for (int& i : vec)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
	std::make_heap(vec.begin(), vec.end());
	for (int& i : vec)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
	HeapSortInplace(vec.begin(), vec.end());
	for (int& i : vec)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
}