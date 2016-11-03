#pragma once
#include "stdafx.h"
#include <windows.h>
#define SUCCESS_T           1 // ִ�гɹ�											
#define ERROR_T            -1 // ִ��ʧ��											
#define INDEX_IS_ERROR   -2 // �����������											
#define BUFFER_IS_EMPTY  -3 // �������ѿ�	
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
	BOOL  IsEmpty();						//�ж������Ƿ�Ϊ�� �շ���1 �ǿշ���0				
	void  Clear();						//�������				
	DWORD GetElement(IN DWORD dwIndex, OUT T_ELE& Element);						//����������ȡԪ��				
	DWORD GetElementIndex(IN T_ELE& Element);						//����Ԫ�ػ�ȡ�����е�����				
	DWORD Insert(IN T_ELE Element);						//����Ԫ��				
	DWORD Insert(IN DWORD dwIndex, IN T_ELE Element);						//������������Ԫ��				
	DWORD Delete(IN DWORD dwIndex);						//��������ɾ��Ԫ��				
	DWORD GetSize();						//��ȡ������Ԫ�ص�����				
private:
	
	_NODE<T_ELE> * GetIndexCurrentNode(DWORD dwIndex);						//��ȡ����ΪdwIndex��ָ��				
	_NODE<T_ELE> * GetIndexPreviousNode(DWORD dwIndex);						//��ȡ����ΪdwIndex��ǰһ���ڵ�ָ��				
	_NODE<T_ELE> * GetIndexNextNode(DWORD dwIndex);						//��ȡ����ΪdwIndex�ĺ�һ���ڵ�ָ��				
private:
	_NODE<T_ELE> * m_pList;						//����ͷָ�룬ָ���һ���ڵ�				
	DWORD m_dwLength;						//Ԫ�ص�����				
};
//�޲ι��캯�� ��ʼ����Ա											
template<class T_ELE> LinkedList<T_ELE>::LinkedList()
	:m_pList(NULL), m_dwLength(0)
{

}
//�������� ���Ԫ��											
template<class T_ELE> LinkedList<T_ELE>::~LinkedList()
{
	Clear();
}
//�ж������Ƿ�Ϊ��											
template<class T_ELE> BOOL LinkedList<T_ELE>::IsEmpty()
{

	if (!m_pList || m_dwLength <= 0)
	{
		return true;
	}
	return false;
}
//�������											
template<class T_ELE> void LinkedList<T_ELE>::Clear()
{
	// 1. �ж������Ƿ�Ϊ��										
	if (!m_pList)
	{
		return;
	}
	// 2. ѭ��ɾ�������еĽڵ�										
	_NODE<T_ELE>* m_tmplist = NULL;	//��ͷָ�����ʱָ��
	while (m_pList)
	{
		m_tmplist = m_pList->pNext;		//�õ��������һ����ַ
		delete m_pList;								//ɾ����ǰ����
		m_pList = m_tmplist;
	}

	// 3. ɾ�����һ���ڵ㲢����������Ϊ0										
	m_dwLength = NULL;
}
//����������ȡԪ��											
template<class T_ELE> DWORD LinkedList<T_ELE>::GetElement(IN DWORD dwIndex, OUT T_ELE& Element)
{
	// 1. �ж������Ƿ���Ч										
	_NODE<T_ELE>* m_pindex = GetIndexCurrentNode(dwIndex);
	if (!m_pindex)
	{
		return INDEX_IS_ERROR;		//���ش����������
	}
	// 2. ȡ������ָ��Ľڵ�										
	Element = m_pindex->Data;
	// 3. ������ָ��ڵ��ֵ���Ƶ�OUT����										

}
//����Ԫ�����ݻ�ȡ����											
template<class T_ELE> DWORD LinkedList<T_ELE>::GetElementIndex(IN T_ELE& Element)
{
	// 1. �ж������Ƿ�Ϊ��										
	if (IsEmpty())
	{
		return BUFFER_IS_EMPTY;
	}
	// 2. ѭ�����������ҵ���Element��ͬ��Ԫ��		
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
//������β�������ڵ�											
template<class T_ELE> DWORD LinkedList<T_ELE>::Insert(IN T_ELE Element)
{
	_NODE<T_ELE>* m_Pbefore = NULL;		//Ҫ����Ľڵ�ǰһ���ڵ�
	_NODE<T_ELE>* m_Pafter = NULL;		//Ҫ����Ľڵ��һ���ڵ�
	_NODE<T_ELE>* m_Ptemp = NULL;		//��ʱ�ڵ�ͷ
	_NODE<T_ELE>* m_Pdata = NULL;		//������ݵ�ָ��
	m_Pdata = new _NODE<T_ELE>;
	memset(m_Pdata, 0, sizeof _NODE<T_ELE>);
	memcpy(&m_Pdata->Data, &Element, sizeof T_ELE);
	// 1. �ж������Ƿ�Ϊ��										
	if (IsEmpty())
	{
		m_pList = m_Pdata;
		m_dwLength++;
	}
	else
	{
		// 2. ����������Ѿ���Ԫ��
		m_Ptemp = GetIndexCurrentNode(m_dwLength);		//���������õ����һ���ڵ�ָ��
		if (!m_Ptemp)
		{
			return BUFFER_IS_EMPTY;		//��Ч�Ľڵ�ָ��
		}
		m_Pdata->Data = Element;
		m_Ptemp->pNext = m_Pdata;
		m_dwLength++;
	}


	return SUCCESS_T;
}
//���ڵ�������ָ��������λ��											
template<class T_ELE> DWORD LinkedList<T_ELE>::Insert(IN DWORD dwIndex, IN T_ELE Element)
{
	_NODE<T_ELE>* m_Pbefore = NULL;		//Ҫ����Ľڵ�ǰһ���ڵ�
	_NODE<T_ELE>* m_Pafter = NULL;		//Ҫ����Ľڵ��һ���ڵ�
	_NODE<T_ELE>* m_Ptemp = NULL;		//��ʱ�ڵ�ͷ
	_NODE<T_ELE>* m_Pdata = NULL;		//������ݵ�ָ��
	m_Pdata = new _NODE<T_ELE>;
	memset(m_Pdata, 0, sizeof _NODE<T_ELE>);
	memcpy(&m_Pdata->Data, &Element, sizeof T_ELE);
	m_Pdata->pNext = NULL;
	//  1. �ж������Ƿ�Ϊ��										
	if (IsEmpty())
	{
		//���ͷָ��Ϊ���Ҳ����������==0
		if (dwIndex == 0)
		{
			m_pList = m_Pdata;
			m_dwLength++;
			return SUCCESS_T;
		}
		return INDEX_IS_ERROR;
	}
	//  2. �ж�����ֵ�Ƿ���Ч										
	if (dwIndex<0 || dwIndex>m_dwLength)
	{
		return INDEX_IS_ERROR;		//������Ч������
	}
	if (dwIndex == 0)			//�������Ϊnull��������λ����0
	{
		m_Pdata->pNext = m_pList;
		m_pList = m_Pdata;
		m_dwLength++;
		return SUCCESS_T;
	}
	//  4. �������Ϊ����β										
	if (dwIndex == m_dwLength)
	{
		m_Pbefore = GetIndexCurrentNode(dwIndex);	//��ǰ����ڵ�ָ��
		if (!m_Pbefore)
			return BUFFER_IS_EMPTY;
		m_Pbefore->pNext = m_Pdata;
		m_dwLength++;
		return SUCCESS_T;
	}
	// 5. �������Ϊ������	
	m_Pbefore = GetIndexPreviousNode(dwIndex);	//ǰһ������ڵ�ָ��
	if (!m_Pbefore)
		return BUFFER_IS_EMPTY;
	m_Ptemp = GetIndexCurrentNode(dwIndex);	//��ȡ����Ϊdwindex�Ľڵ�ָ��
	if (m_Ptemp)
		return BUFFER_IS_EMPTY;
	m_Pdata->pNext = m_Ptemp;		//�Ѳ������һ���ڵ�ָ��ָ��ԭ����
	m_Pbefore->pNext = m_Pdata;		//��ԭ����ǰһ���ڵ��pNextָ�������Ľڵ�
	m_dwLength++;
	return SUCCESS_T;
}
//��������ɾ���ڵ�											
template<class T_ELE> DWORD LinkedList<T_ELE>::Delete(IN DWORD dwIndex)
{
	_NODE<T_ELE>* m_ptemp = NULL;
	_NODE<T_ELE>* m_ptbore = NULL;
	//  1. �ж������Ƿ�Ϊ��										
	if (IsEmpty())
		return BUFFER_IS_EMPTY;
	//  2. �ж�����ֵ�Ƿ���Ч										
	if (dwIndex<0 || dwIndex>m_dwLength)
	{
		return INDEX_IS_ERROR;		//������Ч������
	}
	//  3. ���������ֻ��ͷ�ڵ㣬��Ҫɾ��ͷ�ڵ�										
	if (dwIndex == 0 && m_dwLength == 1)
	{
		delete m_pList;
		m_pList = NULL;
		m_dwLength--;
		return SUCCESS_T;
	}
	//  4. ���Ҫɾ��ͷ�ڵ�										
	if (dwIndex == 0 && m_dwLength > 1)
	{
		m_ptemp = m_pList->pNext;
		delete m_pList;
		m_pList = m_ptemp;
		m_dwLength--;
		return SUCCESS_T;
	}
	//	0 1 2 3 4 5 6 7
	//  5. ������������			
	m_ptemp = GetIndexCurrentNode(dwIndex);
	if (!m_ptemp)
		return INDEX_IS_ERROR;		//������Ч������
	m_ptbore = GetIndexPreviousNode(dwIndex);
	m_ptbore->pNext = m_ptemp->pNext;
	delete m_ptemp;
	m_dwLength--;
	return SUCCESS_T;
}
//��ȡ�����нڵ������											
template<class T_ELE> DWORD LinkedList<T_ELE>::GetSize()
{
	return m_dwLength;
}
//��ȡdwIndexǰ��ڵ�ĵ�ַ											
template<class T_ELE>
_NODE<T_ELE> * LinkedList<T_ELE>::GetIndexPreviousNode(DWORD dwIndex)
{
	if (dwIndex<0 || dwIndex >m_dwLength)
	{
		return  (_NODE<T_ELE>*)INDEX_IS_ERROR;
	}
	//�ж������Ƿ�Ϊ��
	if (IsEmpty())
	{
		return  (_NODE<T_ELE>*)BUFFER_IS_EMPTY;
	}
	_NODE<T_ELE>*m_Pbefore = NULL;			//����ǰ���ָ��
	_NODE<T_ELE>*m_Ptemplist = m_pList;		//��ʼ��ָ��
											//dwIndex-=1;
	for (DWORD i = 0; i < dwIndex - 2; i++)
	{
		m_Ptemplist = m_Ptemplist->pNext;
	}
	m_Pbefore = m_Ptemplist;
	// ����һ��ѭ��										
	return m_Pbefore;
}
//��ȡdwIndex�ڵ�ĵ�ַ											
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
	// ����һ��ѭ��										
	_NODE<T_ELE>* m_pret = m_pList;
	for (DWORD i = 0; i < dwIndex - 1; i++)
	{
		m_pret = m_pret->pNext;
	}
	return m_pret;
}
//��ȡdwIndex����ڵ�ĵ�ַ				
template<class T_ELE>
_NODE<T_ELE> * LinkedList<T_ELE>::GetIndexNextNode(DWORD dwIndex)
{
	if (dwIndex<0 || dwIndex >m_dwLength)
	{
		return  (_NODE<T_ELE>*)INDEX_IS_ERROR;
	}
	// ����һ��ѭ��		
	if (IsEmpty())
	{
		return  (_NODE<T_ELE>*)BUFFER_IS_EMPTY;
	}
	_NODE<T_ELE>*m_Pbefore = NULL;			//����ǰ���ָ��
	_NODE<T_ELE>*m_Ptemplist = m_pList;		//��ʼ��ָ��
											//dwIndex += 1;
	for (DWORD i = 0; i < dwIndex; i++)
	{
		m_Ptemplist = m_Ptemplist->pNext;
	}
	m_Pbefore = m_Ptemplist;
	// ����һ��ѭ��										
	return m_Pbefore;
}


