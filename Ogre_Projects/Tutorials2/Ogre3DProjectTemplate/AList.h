//=====================================================
//					Filename: AList.h
//=====================================================
#pragma once


//=====================================================
//					Include Guards.
//=====================================================
#ifndef _LIST_H_
#define _LIST_H_


//=====================================================
//					Libraries.
//=====================================================
#include <vector>


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    AList

  Summary:  An extension of vector<T> providing additional methods for
			checking and removing elements.

  Methods:  ====================== PUBLIC ======================
			AList()
				Default constructor of a AList.
			~AList()
				Default deconstructor of a list.

			====================== INLINE ======================
			bool Contains(T object)
				does this AList contain the specified object.

			void Remove(const T& object)
				if the object is contained within the list, remove it and
				mutate the list accordingly.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
template<typename T>
class AList : public std::vector<T>
{
public:
	AList();
	~AList();

	bool Contains(const T& object);

	void Remove(const T& object);
};

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   AList

  Summary:  The default constructor for a AList.

  Modifies: [none].

  Returns:  AList<T>
				the newly created AList object containing T objects.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
template<class T>
inline AList<T>::AList()
{
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   ~AList

  Summary:  The default deconstructor of the AList object.

  Modifies: [none].
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
template<class T>
inline AList<T>::~AList()
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
template<typename T>
inline bool AList<T>::Contains(const T& object)
{
	if (this->empty())
		return false;
	else
	{
		if (std::find(this->begin(), this->end(), object) != this->end())
			return true;
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
inline void AList<T>::Remove(const T& object)
{
	auto indexToRemove = std::find(this->begin(), this->end(), object);
	if (indexToRemove == this->end())
		return;

	this->erase(indexToRemove);
}

#endif

