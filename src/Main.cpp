#include <iostream>
#include <queue>
#include <PriorityQueue.h>
#include <algorithm>
#include <Sorting.h>
#include <chrono>
#include <random>

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
			// priorityQueue.push(T());
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
	srand(time(nullptr));
	const int iters = 10000;
	PriorityQueue<T> myPriorQueue;
	std::priority_queue<T> stlPriorQueue;
	bool isDataEqual = true;
	for (int i = 0; i < iters; i++)
	{
		int insertDataAmount = rand() % 6 + 5;
		for (int j = 0; j < insertDataAmount; j++)
		{
			T randData = T{static_cast<float>((i + 1) * (rand() % 100))};
			// T randData = T();
			myPriorQueue.push(randData);
			stlPriorQueue.push(randData);
		}
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
	
	std::cout << std::endl;
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
	std::cout << "[Log] Comparing std::priority_queue and PriorityQueue...\n";
	testPriorityQueue<Object>();
	std::cout << "[Log] Comparing std::priority_queue and PriorityQueue - done\n";

	// Additional task
	std::cout << "[Log] Comparing sorting algorithms...\n";
	std::cout << "Additional task:" << std::endl;
	std::vector<int> vec(1000000);
	std::cout << "Created a vector of size " << vec.size() << std::endl;
	std::generate(vec.begin(), vec.end(), []() -> int
	{
		return rand() % 123;
	});

	std::random_device d;
	std::mt19937 g(d());

	auto start = std::chrono::steady_clock::now();
	std::sort(vec.begin(), vec.end());
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<float> elapsed = end - start;
	std::cout << "[Timer] std::sort() time elapsed: " << elapsed << "\n";

	std::shuffle(vec.begin(), vec.end(), g);

	start = std::chrono::steady_clock::now();
	HeapSortInplace(vec.begin(), vec.end());
	end = std::chrono::steady_clock::now();
	elapsed = end - start;
	std::cout << "[Timer] HeapSortInplace() time elapsed: " << elapsed << "\n";
	std::cout << "[Log] Comparing sorting algorithms - done\n";

	std::vector<int> heap(1000);
	std::generate(heap.begin(), heap.end(), []() -> int
	{
		return rand() % 123;
	});
	std::cout << "[Log] Before MakeHeap(): " << (std::is_heap(heap.begin(), heap.end()) ? "Is a heap\n" : "Not a heap\n");
	std::cout << "[Log] Making a heap...\n";
	MakeHeap(heap.begin(), heap.end());
	std::cout << "[Log] Making a heap - done\n";
	std::cout << "[Log] After MakeHeap(): " << (std::is_heap(heap.begin(), heap.end()) ? "Is heap\n" : "Not a heap\n");
}