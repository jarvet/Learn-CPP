#include<iostream>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StreamBuffer.h"// for Code::Block
//#define BUFFER_LEN 524288

using namespace std;
//-------------------
 StreamBuffer::StreamBuffer()
 {
 //  to do：  some initialization work
   m_pData = new char[524288];
   m_iBufferLen = 0;
   head_offset = 0;
 }
  StreamBuffer::StreamBuffer(int iLen)
 {
 //  to do：  some initialization work
   m_pData = new char[iLen];
   m_iBufferLen = iLen;

 }
StreamBuffer::~StreamBuffer()
 {
 //  to do：  some initialization work
  if( NULL !=  m_pData)
   delete []m_pData;

 }
int StreamBuffer::ReceiveDate(unsigned int offset, unsigned int bytes, char *pData)
{
// receive data: save to your buffer....
   int iBytes = 0;
   NODE *pt = NULL;
   if (head == NULL)
   {
	   head_offset = 0;
   }
   if (m_iBufferLen > 0.8 * 524288)
   {
	   NODE *temp = NULL;
	   int move = head->next->left;
	   head_offset += move;
	   m_iBufferLen -= (head->right - head->left + 1);
	   temp = head;
	   head = head->next;
	   delete temp;
	   memcpy(m_pData, m_pData + head->left, 524288 - head->left + 1);
	   temp = head;
	   while (temp != NULL)
	   {
		   temp->left -= move;
		   temp->right -= move;
		   temp = temp->next;
	   }
   }
   unsigned int start_offset_of_received_data;
   start_offset_of_received_data = offset - head_offset;
   memcpy(m_pData + start_offset_of_received_data, pData, bytes);
   m_iBufferLen += bytes;
   pt = Insert(&head, start_offset_of_received_data, start_offset_of_received_data + bytes - 1);
   CleanUp(pt);
   // to do： ...
   return iBytes;// bytes the buffer saved
}

int StreamBuffer::ContinueBytes(unsigned int &iDataOffset, char* &pData)
{//返回缓冲区中，排好序的数据的长度（单位字节数）。并通过引用参数返回如下信息
 //iDataOffset: 排好序的数据块中第一个字节的偏移量数值
 //pData：数据指针
  int iContinueBytes = 0;
  iContinueBytes = head->right - head->left + 1;
  iDataOffset = head_offset + head->left;
  pData = &m_pData[head->left];
  // to do： ...
  return iContinueBytes;
};


int StreamBuffer::RemoveData(int iBytes)
{//从缓冲区中把数据"删除",返回删除的字节数
  int iBytesRemoved=0;
  memcpy(m_pData, m_pData + iBytes, 512 * 1024 - iBytes);
  m_iBufferLen -= iBytes;
  head_offset += iBytes;
  NODE *pt = NULL;
  head->right -= iBytes;
  pt = head->next;
  while (pt != NULL)
  {
	  pt->left -= iBytes;
	  pt->right -= iBytes;
	  pt = pt->next;
  }
   // to do： ...
   //从缓冲区中把数据"删除"
   return iBytesRemoved;
};

NODE *Find(NODE *head, unsigned int left, unsigned int right)
{
	NODE *p = head;
	while (p->next != NULL)
	{
		if (left >= p->left && left <= (p->next)->left)
		{
			break;
		}
		else
		{
			p = p->next;
		}
	}
	return p;
}

NODE *Insert(NODE **head, unsigned int left, unsigned int right)
{
	if (*head == NULL)
	{
		*head = new NODE;
		(*head)->left = left;
		(*head)->right = right;
		(*head)->next = NULL;
		return *head;
	}
	if (right + 1 < ((*head)->left))
	{
		NODE *node = NULL;
		node = new NODE;
		node->left = left;
		node->right = right;
		node->next = *head;
		*head = node;
		return node;
	}
	else if (left < (*head)->left)
	{
		(*head)->left = left;
		if ((*head)->right < right)
		{
			(*head)->right = right;
		}
		return *head;
	}
	else
	{
		NODE *find = NULL;
		find = Find(*head, left, right);
		if (left <= find->right + 1)
		{
			if (right > find->right)
			{
				find->right = right;
				return find;
			}
			return find;
		}
		else
		{
			NODE *node = NULL;
			node = new NODE;
			node->left = left;
			node->right = right;
			node->next = find->next;
			find->next = node;
			return node;
		}
	}
}

void CleanUp(NODE *start)
{
	NODE *pt = NULL, *temp = NULL;
	pt = start;
	while (pt->next != NULL)
	{
		temp = pt->next;
		if (temp->left <= pt->right + 1)
		{
			if (temp->right > pt->right)
			{
				pt->right = temp->right;
				pt->next = temp->next;
				delete temp;
			}
			else
			{
				pt->next = temp->next;
				delete temp;
			}
		}
		else
		{
			pt = pt->next;
		}
	}
}

int Count(NODE *head)
{
	NODE *temp = NULL;
	int sum = 0;
	temp = head;
	while (temp != NULL)
	{
		sum++;
		temp = temp->next;
	}
	return sum;
}

void Show(NODE *head)
{
	NODE *temp = NULL;
	temp = head;
	while (temp != NULL)
	{
		cout << "[" << temp->left << ", " << temp->right << "]" << endl;
		temp = temp->next;
	}
}
