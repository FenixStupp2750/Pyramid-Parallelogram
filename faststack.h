#pragma once

template<typename T>
struct stack_node {
	T value;
	stack_node* prev = nullptr;
};

template<typename T>
class stack { // стэк для ускорения работы fill
public:
	stack() {}
	stack(T* mas, int length)
	{
		for (int i = 0; i < length; i++)
		{
			push_back(mas[i]);
		}
	}
	stack(const stack<T>& copy)
	{
		int n = copy.length();
		for (int i = 0; i < n; i++)
		{
			push_back(copy[i]);
		}
	}

	~stack()
	{
		clear();
	}

	void push_back(T member)
	{
		if (!tail)
		{
			stack_node<T>* newTail = new stack_node<T>;
			newTail->value = member;
			tail = newTail;
			return;
		}
		stack_node<T>* newNode = new stack_node<T>;
		newNode->value = member;
		stack_node<T>* cntr = tail;
		tail = newNode;
		tail->prev = cntr;
	}
	T pop_back()
	{
		T ret;
		if (!tail)
		{
			throw;
		}
		stack_node<T>* cntr = tail->prev;
		ret = tail->value;
		delete tail;
		tail = cntr;
		return ret;
	}

	stack<T>& operator= (const stack<T>& copy)
	{
		clear();
		int n = copy.length();
		for (int i = 0; i < n; i++)
		{
			push_back(copy[i]);
		}
		return (*this);
	}

	void clear()
	{
		for (int i = 0, l = length(); i < l; i++)
		{
			pop_back();
		}
	}

	int length() const
	{
		if (!tail)
		{
			return 0;
		}
		int i = 1;
		stack_node<T>* cntr = tail;
		while (cntr->prev != nullptr)
		{
			cntr = cntr->prev;
			i++;
		}
		return i;
	}

	bool fast_length() const
	{
		if (!tail)
		{
			return 0;
		}
		return 1;
	}
private:
	stack_node<T>* tail = nullptr;
};
#pragma once
