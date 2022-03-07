#include <iostream>
#include "PriorityQueue.h"
int main() {
	// 0 - low priority, 1 - medium priority, 2 - high priority
	PriorityQueue test;
	for (int i = 0; i < 10; i++) {
		int a = rand() % 10000;
		int b = rand() % 3;
		test.Push(a, b);
		std::cout << "(" << a << "," << b << ")" << std::endl;

	}
	std::cout << "New queue from random: " << std::endl;
	test.WriteToConsole();
	std::cout << "Deleting of 3 elements." << std::endl;
	for (int i = 0; i < 3; i++) {
		test.Pop();
	}
	test.WriteToConsole();
	std::cout << "The first element is " << test.GetFront() << std::endl << "The full size of the queue is " << test.GetFullSize() << std::endl;
	std::cout << "High priority: " << test.GetSizeFromPriority(2) << " Medium priority: " << test.GetSizeFromPriority(1) << " Low priority: " << test.GetSizeFromPriority(0) << std::endl;
	PriorityQueue test2 = test;
	PriorityQueue test3(test);
	std::cout << "Clear the queue:" << std::endl;
	test.Clear();
	test.WriteToConsole();
	std::cout << test.GetFront();
	if (test.IsEmpty()) {
		std::cout << "the queue is empty";
	}
	else {
		std::cout << "the queue isn't empty";
	}
	return 0;
}