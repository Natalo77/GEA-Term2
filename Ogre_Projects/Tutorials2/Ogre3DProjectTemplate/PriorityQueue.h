#pragma once

#include <queue>
#include <list>

template <class T> 
class PriorityQueue : public std::list<T>
{
public:
	PriorityQueue<T>();
	~PriorityQueue();

	bool Contains(T object);

	T* DeQueue();
};

template<class T>
inline PriorityQueue<T>::~PriorityQueue()
{
	super();
}

template<class T>
inline bool PriorityQueue<T>::Contains(T object)
{
	if (this->empty())
		return false;
	else
	{
		for (std::queue<T*>::iterator iter = this->begin();	//Iterator at start of AStar_Edge list.
			iter != this->end();										//Until iterator reaches end of list.
			iter++)
		{
			if (*object == *iter)
				return true;
		}
	}
	return false;
}

template<class T>
inline T * PriorityQueue<T>::DeQueue()
{
	T back = this->begin();
	this.;
	return &back;
}



