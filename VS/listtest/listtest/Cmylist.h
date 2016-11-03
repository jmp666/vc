#pragma once
#include "stdafx.h"
#include <windows.h>
#define SUCCESS_T           1 // 执行成功											
#define ERROR_T            -1 // 执行失败											
#define INDEX_IS_ERROR   -2 // 错误的索引号											
#define BUFFER_IS_EMPTY  -3 // 缓冲区已空	
template <class T_ELE>
struct _NODE
{
	T_ELE  Data;
	_NODE *pNext;
};
template <class T_ELE>
class LinkedList
{
public:
	LinkedList();
	~LinkedList();
public:
	BOOL  IsEmpty();						//判断链表是否为空 空返回1 非空返回0				
	void  Clear();						//清空链表				
	DWORD GetElement(IN DWORD dwIndex, OUT T_ELE& Element);						//根据索引获取元素				
	DWORD GetElementIndex(IN T_ELE& Element);						//根据元素获取链表中的索引				
	DWORD Insert(IN T_ELE Element);						//新增元素				
	DWORD Insert(IN DWORD dwIndex, IN T_ELE Element);						//根据索引新增元素				
	DWORD Delete(IN DWORD dwIndex);						//根据索引删除元素				
	DWORD GetSize();						//获取链表中元素的数量				
private:
	
	_NODE<T_ELE> * GetIndexCurrentNode(DWORD dwIndex);						//获取索引为dwIndex的指针				
	_NODE<T_ELE> * GetIndexPreviousNode(DWORD dwIndex);						//获取索引为dwIndex的前一个节点指针				
	_NODE<T_ELE> * GetIndexNextNode(DWORD dwIndex);						//获取索引为dwIndex的后一个节点指针				
private:
	_NODE<T_ELE> * m_pList;						//链表头指针，指向第一个节点				
	DWORD m_dwLength;						//元素的数量				
};
//无参构造函数 初始化成员											
template<class T_ELE> LinkedList<T_ELE>::LinkedList()
	:m_pList(NULL), m_dwLength(0)
{

}
//析构函数 清空元素											
template<class T_ELE> LinkedList<T_ELE>::~LinkedList()
{
	Clear();
}
//判断链表是否为空											
template<class T_ELE> BOOL LinkedList<T_ELE>::IsEmpty()
{

	if (!m_pList || m_dwLength <= 0)
	{
		return true;
	}
	return false;
}
//清空链表											
template<class T_ELE> void LinkedList<T_ELE>::Clear()
{
	// 1. 判断链表是否为空										
	if (!m_pList)
	{
		return;
	}
	// 2. 循环删除链表中的节点										
	_NODE<T_ELE>* m_tmplist = NULL;	//把头指针给临时指针
	while (m_pList)
	{
		m_tmplist = m_pList->pNext;		//得到链表的下一个地址
		delete m_pList;								//删除当前链表
		m_pList = m_tmplist;
	}

	// 3. 删除最后一个节点并将链表长度置为0										
	m_dwLength = NULL;
}
//根据索引获取元素											
template<class T_ELE> DWORD LinkedList<T_ELE>::GetElement(IN DWORD dwIndex, OUT T_ELE& Element)
{
	// 1. 判断索引是否有效										
	_NODE<T_ELE>* m_pindex = GetIndexCurrentNode(dwIndex);
	if (!m_pindex)
	{
		return INDEX_IS_ERROR;		//返回错误的索引号
	}
	// 2. 取得索引指向的节点										
	Element = m_pindex->Data;
	// 3. 将索引指向节点的值复制到OUT参数										

}
//根据元素内容获取索引											
template<class T_ELE> DWORD LinkedList<T_ELE>::GetElementIndex(IN T_ELE& Element)
{
	// 1. 判断链表是否为空										
	if (IsEmpty())
	{
		return BUFFER_IS_EMPTY;
	}
	// 2. 循环遍历链表，找到与Element相同的元素		
	_NODE<T_ELE>*m_Ptmplist = m_pList;
	DWORD  dwindex = NULL;
	while (m_Ptmplist)
	{
		if (!memcmp(&Element, &m_Ptmplist->Data, sizeof T_ELE))
		{
			break;
		}
		m_Ptmplist = m_Ptmplist->pNext;
		dwindex++;
	}
	return dwindex;

}
//在链表尾部新增节点											
template<class T_ELE> DWORD LinkedList<T_ELE>::Insert(IN T_ELE Element)
{
	_NODE<T_ELE>* m_Pbefore = NULL;		//要插入的节点前一个节点
	_NODE<T_ELE>* m_Pafter = NULL;		//要插入的节点后一个节点
	_NODE<T_ELE>* m_Ptemp = NULL;		//临时节点头
	_NODE<T_ELE>* m_Pdata = NULL;		//存放数据的指针
	m_Pdata = new _NODE<T_ELE>;
	memset(m_Pdata, 0, sizeof _NODE<T_ELE>);
	memcpy(&m_Pdata->Data, &Element, sizeof T_ELE);
	// 1. 判断链表是否为空										
	if (IsEmpty())
	{
		m_pList = m_Pdata;
		m_dwLength++;
	}
	else
	{
		// 2. 如果链表中已经有元素
		m_Ptemp = GetIndexCurrentNode(m_dwLength);		//根据索引得到最后一个节点指针
		if (!m_Ptemp)
		{
			return BUFFER_IS_EMPTY;		//无效的节点指针
		}
		m_Pdata->Data = Element;
		m_Ptemp->pNext = m_Pdata;
		m_dwLength++;
	}


	return SUCCESS_T;
}
//将节点新增到指定索引的位置											
template<class T_ELE> DWORD LinkedList<T_ELE>::Insert(IN DWORD dwIndex, IN T_ELE Element)
{
	_NODE<T_ELE>* m_Pbefore = NULL;		//要插入的节点前一个节点
	_NODE<T_ELE>* m_Pafter = NULL;		//要插入的节点后一个节点
	_NODE<T_ELE>* m_Ptemp = NULL;		//临时节点头
	_NODE<T_ELE>* m_Pdata = NULL;		//存放数据的指针
	m_Pdata = new _NODE<T_ELE>;
	memset(m_Pdata, 0, sizeof _NODE<T_ELE>);
	memcpy(&m_Pdata->Data, &Element, sizeof T_ELE);
	m_Pdata->pNext = NULL;
	//  1. 判断链表是否为空										
	if (IsEmpty())
	{
		//如果头指针为空且插入的索引号==0
		if (dwIndex == 0)
		{
			m_pList = m_Pdata;
			m_dwLength++;
			return SUCCESS_T;
		}
		return INDEX_IS_ERROR;
	}
	//  2. 判断索引值是否有效										
	if (dwIndex<0 || dwIndex>m_dwLength)
	{
		return INDEX_IS_ERROR;		//返回无效的索引
	}
	if (dwIndex == 0)			//如果链表不为null且索引的位置是0
	{
		m_Pdata->pNext = m_pList;
		m_pList = m_Pdata;
		m_dwLength++;
		return SUCCESS_T;
	}
	//  4. 如果索引为链表尾										
	if (dwIndex == m_dwLength)
	{
		m_Pbefore = GetIndexCurrentNode(dwIndex);	//当前链表节点指针
		if (!m_Pbefore)
			return BUFFER_IS_EMPTY;
		m_Pbefore->pNext = m_Pdata;
		m_dwLength++;
		return SUCCESS_T;
	}
	// 5. 如果索引为链表中	
	m_Pbefore = GetIndexPreviousNode(dwIndex);	//前一个链表节点指针
	if (!m_Pbefore)
		return BUFFER_IS_EMPTY;
	m_Ptemp = GetIndexCurrentNode(dwIndex);	//获取索引为dwindex的节点指针
	if (m_Ptemp)
		return BUFFER_IS_EMPTY;
	m_Pdata->pNext = m_Ptemp;		//把插入的下一个节点指针指向原来的
	m_Pbefore->pNext = m_Pdata;		//把原来的前一个节点的pNext指向新增的节点
	m_dwLength++;
	return SUCCESS_T;
}
//根据索引删除节点											
template<class T_ELE> DWORD LinkedList<T_ELE>::Delete(IN DWORD dwIndex)
{
	_NODE<T_ELE>* m_ptemp = NULL;
	_NODE<T_ELE>* m_ptbore = NULL;
	//  1. 判断链表是否为空										
	if (IsEmpty())
		return BUFFER_IS_EMPTY;
	//  2. 判断索引值是否有效										
	if (dwIndex<0 || dwIndex>m_dwLength)
	{
		return INDEX_IS_ERROR;		//返回无效的索引
	}
	//  3. 如果链表中只有头节点，且要删除头节点										
	if (dwIndex == 0 && m_dwLength == 1)
	{
		delete m_pList;
		m_pList = NULL;
		m_dwLength--;
		return SUCCESS_T;
	}
	//  4. 如果要删除头节点										
	if (dwIndex == 0 && m_dwLength > 1)
	{
		m_ptemp = m_pList->pNext;
		delete m_pList;
		m_pList = m_ptemp;
		m_dwLength--;
		return SUCCESS_T;
	}
	//	0 1 2 3 4 5 6 7
	//  5. 如果是其他情况			
	m_ptemp = GetIndexCurrentNode(dwIndex);
	if (!m_ptemp)
		return INDEX_IS_ERROR;		//返回无效的索引
	m_ptbore = GetIndexPreviousNode(dwIndex);
	m_ptbore->pNext = m_ptemp->pNext;
	delete m_ptemp;
	m_dwLength--;
	return SUCCESS_T;
}
//获取链表中节点的数量											
template<class T_ELE> DWORD LinkedList<T_ELE>::GetSize()
{
	return m_dwLength;
}
//获取dwIndex前面节点的地址											
template<class T_ELE>
_NODE<T_ELE> * LinkedList<T_ELE>::GetIndexPreviousNode(DWORD dwIndex)
{
	if (dwIndex<0 || dwIndex >m_dwLength)
	{
		return  (_NODE<T_ELE>*)INDEX_IS_ERROR;
	}
	//判断链表是否为空
	if (IsEmpty())
	{
		return  (_NODE<T_ELE>*)BUFFER_IS_EMPTY;
	}
	_NODE<T_ELE>*m_Pbefore = NULL;			//索引前面的指针
	_NODE<T_ELE>*m_Ptemplist = m_pList;		//开始的指针
											//dwIndex-=1;
	for (DWORD i = 0; i < dwIndex - 2; i++)
	{
		m_Ptemplist = m_Ptemplist->pNext;
	}
	m_Pbefore = m_Ptemplist;
	// 就是一个循环										
	return m_Pbefore;
}
//获取dwIndex节点的地址											
template<class T_ELE>
_NODE<T_ELE> *  LinkedList<T_ELE>::GetIndexCurrentNode(DWORD dwIndex) {
	if (dwIndex<0 || dwIndex >m_dwLength)
	{
		return (_NODE<T_ELE>*)INDEX_IS_ERROR;
	}
	if (IsEmpty())
	{
		return  (_NODE<T_ELE>*)BUFFER_IS_EMPTY;
	}
	// 就是一个循环										
	_NODE<T_ELE>* m_pret = m_pList;
	for (DWORD i = 0; i < dwIndex - 1; i++)
	{
		m_pret = m_pret->pNext;
	}
	return m_pret;
}
//获取dwIndex后面节点的地址				
template<class T_ELE>
_NODE<T_ELE> * LinkedList<T_ELE>::GetIndexNextNode(DWORD dwIndex)
{
	if (dwIndex<0 || dwIndex >m_dwLength)
	{
		return  (_NODE<T_ELE>*)INDEX_IS_ERROR;
	}
	// 就是一个循环		
	if (IsEmpty())
	{
		return  (_NODE<T_ELE>*)BUFFER_IS_EMPTY;
	}
	_NODE<T_ELE>*m_Pbefore = NULL;			//索引前面的指针
	_NODE<T_ELE>*m_Ptemplist = m_pList;		//开始的指针
											//dwIndex += 1;
	for (DWORD i = 0; i < dwIndex; i++)
	{
		m_Ptemplist = m_Ptemplist->pNext;
	}
	m_Pbefore = m_Ptemplist;
	// 就是一个循环										
	return m_Pbefore;
}


