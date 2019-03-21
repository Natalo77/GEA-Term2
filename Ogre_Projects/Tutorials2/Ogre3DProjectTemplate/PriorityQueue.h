#pragma once

#include <queue>

template <class T> class PriorityQueue<T> : public std::priority_queue<T>
{
public:
	PriorityQueue<class T>();
	~PriorityQueue();
};

template<class T>
inline PriorityQueue<T>::~PriorityQueue()
{
	super();
}
