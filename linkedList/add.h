#pragma once
#include <iostream>

using  namespace std;

class DoublyLinkedList
{
private:
	struct Node 
	{
		int data;
		Node* prev;
		Node* next;

		Node(int val) : data(val), prev(nullptr), next(nullptr) {}
	};
	
	Node* head;
	Node* tail;
	size_t size;

	void deleteNode(Node* target)
	{
		if (target == nullptr) return;

		if (target == head)
		{
			head = target->next;
			if (head != nullptr) head->prev = nullptr;
		}
		else if (target->prev != nullptr)
		{
			target->prev->next = target->next;
		}

		if (target == tail)
		{
			tail = target->prev;
			if (tail != nullptr) tail->next = nullptr;
		}
		else if (target->next != nullptr)
		{
			target->next->prev = target->prev;
		}

		delete target;
		size--;
	}

public:
	DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

	~DoublyLinkedList()
	{
		clear();
	}

	bool isEmpty() const
	{
		return head == nullptr;
	}

	size_t getSize()
	{
		return size;
	}

	void pushFront(int val)
	{
		Node* newNode = new Node(val);
		if (isEmpty())
			head = tail = newNode;
		else
		{
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}
		size++;
	}

	void pushBack(int val)
	{
		Node* newNode = new Node(val);
		if (isEmpty())
			head = tail = newNode;
		else
		{
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		size++;
	}

	void print() const 
	{
		if (isEmpty())
			return;
		Node* current = head;
		while (current != nullptr)
		{
			cout << current->data;
			if (current->next != nullptr)
				cout << " <-> ";
			current = current->next;
		}
		cout << "\n";
	}

	void clear()
	{
		Node* current = head;
		while (current != nullptr)
		{
			Node* nextNode = current->next;
			delete current;
			current = nextNode;
		}
		head = tail = nullptr;
		size = 0;
	}

	void printTransitionTable() const {
		if (isEmpty()) {
			cout << "Список порожній.\n";
			return;
		}
		cout << "--------------------------------------------------------------------------------\n";
		cout << "Адреса вузла\tПопередній\tЗначення\tНаступний\n";
		cout << "--------------------------------------------------------------------------------\n";
		Node* current = head;
		while (current != nullptr) {
			cout << current << "\t"
				<< current->prev << "\t"
				<< current->data << "\t\t"
				<< current->next << "\n";
			current = current->next;
		}
		cout << "------------------------------------------------------------\n";
	}

	// ---------------------------------------------
	//					ЗАВДАННЯ А
	// ---------------------------------------------

	void replaceNegativesWithZero()
	{
		Node* current = head;
		while (current != nullptr)
		{
			int oldVal = current->data;
			if (current->data < 0)
				current->data = 0;
			current = current->next;
		}
	}

	// ---------------------------------------------
	//					ЗАВДАННЯ Б
	// ---------------------------------------------

	void removeMin()
	{
		if (isEmpty())
			return;
		Node* targetNode = head;
		Node* current = head;

		while(current != nullptr)
		{
			if (current->data < targetNode->data)
			{
				targetNode = current;
			}
			current = current->next;
		}
		deleteNode(targetNode);
	}

	void removeMax()
	{
		if (isEmpty())
			return;
		Node* targetNode = head;
		Node* current = head->next;

		while (current != nullptr)
		{
			if (current->data > targetNode->data)
			{
				targetNode = current;
			}
			current = current->next;
		}
		deleteNode(targetNode);
	}

	void removeMinAndMax()
	{
		removeMin();
		removeMax();
	}

	// ---------------------------------------------
	//					ЗАВДАННЯ В
	// ---------------------------------------------

	bool isSortedAscending() const
	{
		if (head == nullptr || head->next == nullptr)
			return true;

		Node* current = head;
		while (current->next != nullptr)
		{
			if (current->data > current->next->data)
				return false;
			current = current->next;
		}
		return true;
	}
};