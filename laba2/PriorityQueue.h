#pragma once
#include <algorithm>
#include <cassert>
#include <iostream>
#include <exception>
#include <utility>
class PriorityQueue
{
private:
	struct Node {
		int value{ 0 };
		int priority{ 0 };
		friend class PriorityQueue;
		Node() = default;
		Node* ptr_next{ nullptr };
		explicit Node(const int& value, const int& priority) : value(value), priority(priority) {}

		explicit Node(int&& new_value, int&& new_priority) : value(std::move(new_value)),
			priority(std::move(new_priority)) {}

		explicit Node(Node* node) : value(node->value), priority(node->priority) {}
	};
	int size[3]{ 0 };
	Node* rears[3]{ nullptr };
	Node* front{ nullptr };

public:
	// основные функции по заданию
	PriorityQueue() = default;
	PriorityQueue(PriorityQueue&& pq) noexcept;
	PriorityQueue(const PriorityQueue& pq);
	PriorityQueue& operator=(const PriorityQueue& pq) noexcept;
	PriorityQueue& operator=(PriorityQueue&& pq) noexcept;
	int GetSizeFromPriority(int apriority) const;
	int GetFullSize() const;
	bool IsEmpty() const;
	void Push(int aval, int apr);
	void Pop();
	const Node* GetFront();
	// вспомогательные функции
	~PriorityQueue();
	void Clear();
	const Node* GetRear(int apriority);
	void WriteToConsole();
	friend std::ostream& operator << (std::ostream& out, const Node* tmp);
};

