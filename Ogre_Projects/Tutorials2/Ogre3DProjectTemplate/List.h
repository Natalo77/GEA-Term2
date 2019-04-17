#pragma once

template<class T>
class List : public std::vector<T>
{
public:
	List();
	~List();

	bool Contains(T object);

	
};

template<class T>
inline bool List<T>::Contains(T object)
{
	if (this->empty())
		return false;
	else
	{
		for (std::vector<T*>::iterator iter = this->begin();	//Iterator at start of AStar_Edge list.
			iter != this->end();										//Until iterator reaches end of list.
			iter++)
		{
			if (*object == *iter)
				return true;
		}
	}
	return false;
}

