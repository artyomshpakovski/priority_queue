#include "PriorityQueue.h"


PriorityQueue::PriorityQueue(PriorityQueue&& pq) noexcept {
	front = std::move(pq.front);
	pq.front = nullptr;
	for (int i = 0; i < 3; i++) {
		size[i] = std::move(pq.size[i]);
		rears[i] = std::move(pq.rears[i]);
		pq.size[i] = 0;
		pq.rears[i] = 0;
	}
}


const PriorityQueue::Node* PriorityQueue::GetFront() {
	return front;
}

PriorityQueue& PriorityQueue::operator=(const PriorityQueue& pq) noexcept
{
	if (this == &pq) {
		return *this;
	}
	Clear();
	Node* current = pq.front;
	while (current != nullptr) {
		Push(current->value, current->priority);
		current = current->ptr_next;
	}
	delete current;
	return (*this);
}

PriorityQueue& PriorityQueue::operator=(PriorityQueue&& pq) noexcept {
	if (this == &pq) {
		return *this;
	}
	Clear();
	front = pq.front;
	for (int i = 0; i < 3; i++) {
		rears[i] = pq.rears[i];
		pq.rears[i] = nullptr;
		size[i] = pq.size[i];
		pq.size[i] = 0;
	}
	return (*this);
}



PriorityQueue::~PriorityQueue() {
	Clear();
}

void PriorityQueue::Clear()
{
	while (!IsEmpty()) {
		Pop();
	}
}

PriorityQueue::PriorityQueue(const PriorityQueue& pq) {
	Node* current = pq.front;
	while (current != nullptr) {
		Push(current->value, current->priority);
		current = current->ptr_next;
	}
}

int PriorityQueue::GetFullSize() const {
	return size[0] + size[1] + size[2];
}

int PriorityQueue::GetSizeFromPriority(int apriority) const {
	if (apriority > 2 || apriority < 0) {
		throw std::exception("Incorrent apriority");
	}
	return size[apriority];
}


bool PriorityQueue::IsEmpty() const {
	return (GetFullSize() == 0);
}

void PriorityQueue::Push(int aval, int apr) { // 0 - low priority = tail, 1 - medium priority, 2 - high priority
	if (apr > 2 || apr < 0) {
		throw std::exception("Invalid priority of the element. Try again.");
	}
	Node* temp = new Node(aval, apr);
	if (GetFullSize() == 0) {
		front = temp;
		size[apr]++;
		rears[apr] = temp;
		return;
	}
	size[apr]++;
	if (apr == 0) {
		if (rears[0] == nullptr) {
			if (rears[1] == nullptr) {
				rears[0] = temp;
				rears[2]->ptr_next = rears[0];
			}
			else {
				rears[0] = temp;
				rears[1]->ptr_next = rears[0];
			}
		}
		else {
			rears[0]->ptr_next = temp;
			rears[0] = temp;
		}
	}
	if (apr == 2) {
		if (rears[2] == nullptr) {
			rears[2] = temp;
			rears[2]->ptr_next = front;
			front = rears[2];
		}
		else {
			if (rears[1] == nullptr) {
				if (rears[0] == nullptr) {
					rears[2]->ptr_next = temp;
					rears[2] = temp;
				}
				else {
					temp->ptr_next = rears[2]->ptr_next;
					rears[2]->ptr_next = temp;
					rears[2] = temp;
				}
			}
			else {
				temp->ptr_next = rears[2]->ptr_next;
				rears[2]->ptr_next = temp;
				rears[2] = temp;
			}
		}
	}
	if (apr == 1) {
		if (rears[1] == nullptr) {
			if (rears[2] == nullptr) {
				temp->ptr_next = front;
				rears[1] = temp;
				front = temp;
			}
			else {
				if (rears[0] == nullptr) {
					rears[2]->ptr_next = temp;
					rears[1] = temp;
				}
				else {
					temp->ptr_next = rears[2]->ptr_next;
					rears[2]->ptr_next = temp;
					rears[1] = temp;
				}
			}
		}
		else {
			if (rears[0] == nullptr) {
				rears[1]->ptr_next = temp;
				rears[1] = temp;
			}
			else {
				temp->ptr_next = rears[1]->ptr_next;
				rears[1]->ptr_next = temp;
				rears[1] = temp;
			}
		}
	}
}

void PriorityQueue::Pop() {
	if (GetFullSize() == 0) {
		std::cout << "The queue is already empty. Try again";
		return;
	}
	if (GetFullSize() == 1) {
		front = nullptr;
		for (int i = 0; i < 3; i++) {
			size[i] = 0;
			rears[i] = nullptr;
		}
		return;
	}
	size[front->priority]--;
	Node* new_front(front->ptr_next);
	delete front;
	front = new_front;
}


void PriorityQueue::WriteToConsole() {
	if (IsEmpty()) {
		std::cout << "The queue is clear ;)" << std::endl;
		return;
	}
	int i = 0;
	Node* current = front;
	while (i < GetFullSize())
	{
		i++;
		std::cout << current << " ";
		current = current->ptr_next;
	}
	delete current;
	std::cout << std::endl;
}


std::ostream& operator<< (std::ostream& out, const PriorityQueue::Node* tmp)
{
	if (tmp == nullptr) {
		out << "this element doesn't exist" << std::endl;
		return out;
	}
	out << "(" << tmp->value << ", " << tmp->priority << ")";
	return out;
}

const PriorityQueue::Node* PriorityQueue::GetRear(int apriority) {
	if (apriority > 2 || apriority < 0) {
		throw std::exception("Incorrent apriority");
	}
	return rears[apriority];
}

