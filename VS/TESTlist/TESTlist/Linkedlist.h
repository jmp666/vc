#pragma once
#ifndef LINK_KED_LIST
#define LINK_KED_LIST
//#include "stdafx.h"
#include <windows.h>
template <class T>
struct NODE 
{
	T data;
	NODE<T>* pNext;
	NODE(const T &data, NODE<T>* p = NULL)
	{
		data = data;
		pNext = P;
	}
};
template <class T>
class CLinkedlist
{
public:
	CLinkedlist();
	~CLinkedlist();
private:
	NODE<T>* m_Phead;
	DWORD m_dwlength;
};
template <class T>
CLinkedlist<T>::CLinkedlist()
{
	this->m_dwlength = NULL;
	this->m_Phead = NULL;
}


template <class T>
CLinkedlist<T>::~CLinkedlist()
{
}

#endif // !1



