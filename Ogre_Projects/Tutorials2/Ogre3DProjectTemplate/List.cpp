//=====================================================
//					Filename: List.cpp
//=====================================================


//=====================================================
//				Defined Headers.
//=====================================================
#include "List.h"


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   List

  Summary:  The default constructor for a List.

  Modifies: [none].

  Returns:  List<T>
				the newly created List object containing T objects.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
template<class T>
List<T>::List()
{
	super<T>();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   ~List

  Summary:  The default deconstructor of the List object.

  Modifies: [none].
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
template<class T>
List<T>::~List()
{
}

