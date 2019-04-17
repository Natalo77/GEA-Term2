//=====================================================
//					Filename: List.h
//=====================================================
#pragma once


//=====================================================
//					Libraries.
//=====================================================
#include <vector>


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    List

  Summary:  An extension of vector<T> providing additional methods for
			checking and removing elements.

  Methods:  ====================== PUBLIC ======================
			List()
				Default constructor of a List.
			~List()
				Default deconstructor of a list.

			====================== INLINE ======================
			bool Contains(T object)
				does this List contain the specified object.

			void Remove(const T& object)
				if the object is contained within the list, remove it and
				mutate the list accordingly.

			====================== PRIVATE ======================
			====================== INLINE ======================
			vector<T>::iterator IteratorOf(const T& object)
				return the iterator to the object specified in the list.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
template<class T>
class List : public std::vector<T>
{
public:
	List();
	~List();

	bool Contains(T object);

	void Remove(const T& object);

private:

	std::vector<T>::iterator IteratorOf(const T& object);
};

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

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   Remove

  Summary:  If 'object' is present within the underlying data structure,
			remove it and mutate the list accordingly.

  Args:     const T& object
				a reference to the object to remove from the list.

  Modifies: [underlying data structure].
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
template<class T>
inline void List<T>::Remove(const T& object)
{
	std::vector<T>::iterator indexToRemove = IteratorOf(object);
	if (indexToRemove == nullptr)
		return;

	this->erase(indexToRemove);
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   IteratorOf

  Summary:  find and return the iterator pointing to the specified object
			in the list.

  Args:     const T& object
				a reference to the object to search for the iterator of
				within the list.

  Modifies: [none].

  Returns:	vector<T>::iterator
				the iterator according to the underlying data structure
					pointing to 'object'.
				returns nullptr if the object was not found.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
template<class T>
inline std::vector<T>::iterator List<T>::IteratorOf(const T& object)
{
	if (this->empty())
		return nullptr;
	else
	{
		for (std::vector<T*>::iterator iter = this->begin();	//Iterator at start of AStar_Edge list.
			iter != this->end();										//Until iterator reaches end of list.
			iter++)
		{
			if (*object == *iter)
				return iter;
		}
	}
	return nullptr;
}

