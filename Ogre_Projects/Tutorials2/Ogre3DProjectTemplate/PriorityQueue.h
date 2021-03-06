//=====================================================
//					Filename: PriorityQueue.h
//=====================================================
#pragma once


//=====================================================
//					Library Includes
//=====================================================
#include <list>


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    PriorityQueue

  Summary:  An extension of std::list<T> providing additional methods for
			checking, queuing and removing elements.

  Methods:	PriorityQueue<T>()
				Default Constructor for a priorityQueue
			~PriorityQueue()
				Default deconstructor for a priorityQueue

			=================== INLINE ===================
			bool Contains(T object)
				Checks whether 'object' appears within the underlying data structure.

			T* DeQueue()
				Remove and return the first element in the priorityQueue
			void EnQueue(const T& element)
				Queue the element specified to the back of the list.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
template <class T> 
class PriorityQueue : public std::list<T>
{
public:
	PriorityQueue<T>();
	~PriorityQueue();

	bool Contains(const T& object);

	T DeQueue();
	void EnQueue(const T& element);
};

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   PriorityQueue

  Summary:  The default constructor of a priorityQueue object.

  Modifies: [none].

  Returns:  PriorityQueue<T>
				the newly created PriorityQueue object containing objects
				of type T.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
template<class T>
inline PriorityQueue<T>::PriorityQueue()
{
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   ~PriorityQueue()

  Summary:  Deconstructs the PriorityQueue object.

  Modifies: [none].
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
template<class T>
inline PriorityQueue<T>::~PriorityQueue()
{
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   Contains

  Summary:  runs through the underlying data structure and tests each
			element for equality to 'object'.
			returns whether or not 'object' is present in the list.

  Args:     T object
				the object to search the list for.

  Modifies: [none].

  Returns:  bool
				true if the element was not found within the list.
				false if the element was not found or the list is empty.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
template<class T>
inline bool PriorityQueue<T>::Contains(const T& object)
{
	// If it's empty then not contained.
	if (this->empty())
		return false;
	else
	{
		// if std find does not return end then it's contained.
		if (std::find(this->begin(), this->end(), object) != this->end())
			return true;
	}
	return false;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   DeQueue

  Summary:  Removes the first element in the list.
			Then returns it.

  Modifies: [underlying data structure].

  Returns:  T*	
				a pointer to the T object dequeued.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
template<class T>
inline T PriorityQueue<T>::DeQueue()
{
	// Temp T storage.
	T back = this->front();

	//Pop the front.
	this->pop_front();

	// Return the temp storage.
	return back;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   EnQueue(const T& element)

  Summary:  Adds the specified element to the PriorityQueue

  Args:     const T& element
				a reference to the T object to be queued.

  Modifies: [underlying data structure].
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
template<class T>
inline void PriorityQueue<T>::EnQueue(const T& element)
{
	this->push_back(element);
}



