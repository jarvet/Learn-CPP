#include "StreamBuffer.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>


using namespace std;

StreamBuffer::StreamBuffer()
{
	m_pData = new char[BUFFER_LEN]; 
	m_iBufferLen = 0;
	head_offset = 0;
	start_offset = 0;
	head = NULL;
}

StreamBuffer::~StreamBuffer()
{
	if (NULL != m_pData)
	{
		delete m_pData;
	}
	Record *temp = head;
	Record *t = NULL;
	while (NULL != temp)
	{
		t = temp->get_next();
		delete temp;
		temp = t;
	}
}

Record* StreamBuffer::r_Find(unsigned int left, unsigned int right)
{
	Record *p = head;
	while (NULL != p->get_next())
	{
		if (left >= p->get_left() && left <= (p->get_next())->get_left())
		{
			break;
		}
		else
		{
			p = p->get_next();
		}
	}
	return p;
}

Record* StreamBuffer::r_Insert(unsigned int left, unsigned int right)
{
	if (NULL == head)
	{
		head = new Record(left, right);
		return head;
	}
	if (right + 1 < head->get_left())
	{
		Record *record = new Record(left, right, head);
		head = record;
		return record;
	}
	else if (left < head->get_left())
	{
		head->set_left(left);
		if (head->get_right() < right)
		{
			head->set_right(right);
		}
		return head;
	}
	else
	{
		Record *find = r_Find(left, right);
		if (left <= find->get_right() + 1)
		{
			if (right > find->get_right())
			{
				find->set_right(right);
				return find;
			}
			return find;
		}
		else
		{
			Record *record = new Record(left, right, find->get_next());
			find->set_next(record);
			return find;
		}
	}
}

void StreamBuffer::r_CleanUp(Record *start)
{
	Record *pt = NULL, *temp = NULL;
	pt = start;
	while (NULL != pt->get_next())
	{
		temp = pt->get_next();
		if (temp->get_left() <= pt->get_right() + 1)
		{
			if (temp->get_right() > pt->get_right())
			{
				pt->set_right(temp->get_right());
				pt->set_next(temp->get_next());
				delete temp;
			}
			else
			{
				pt->set_next(temp->get_next());
				delete temp;
			}
		}
		else
		{
			pt = pt->get_next();
		}
	}
}

Record* StreamBuffer::r_GetHead()
{
	return head;
}

void StreamBuffer::ReceiveDate(unsigned int offset, unsigned int bytes, char *pData)
{
	if (NULL == head)
	{
		if (offset < BUFFER_LEN) // 判断是否为文件开始位置的数据包
		{
			start_offset = 0;
			head_offset = 0;
		}
		else
		{
			start_offset = offset;
			head_offset = offset;
		}
	}
	if (m_iBufferLen > 0.8 * BUFFER_LEN)
	{
		ofstream errlog("err.log");
		errlog << head_offset << " to " << head->get_next()->get_left() << " was lost!" << endl;
		errlog.close();
		int move = head->get_next()->get_left();
		head_offset += move;
		m_iBufferLen -= (head->get_right() - head->get_left() + 1);
		Record *temp = head;
		head = head->get_next();
		delete temp;
		memcpy(m_pData, m_pData + head->get_left(), BUFFER_LEN - head->get_left() + 1);
		temp = head;
		while (NULL != temp)
		{
			temp->set_left(temp->get_left() - move);
			temp->set_right(temp->get_right() - move);
			temp->set_next(temp->get_next());
		}
	}
	unsigned int start_offset_of_receive_data;
	start_offset_of_receive_data = offset - head_offset; // 表示出接受到的数据在缓存区的相对偏移量
	memcpy(m_pData + start_offset_of_receive_data, pData, bytes);
	m_iBufferLen += bytes;
	Record *pt = NULL;
	pt = r_Insert(start_offset_of_receive_data, start_offset_of_receive_data + bytes - 1); // 先写insert再写介个以下部分= =b
	r_CleanUp(pt);
}

int StreamBuffer::ContinueBytes(unsigned int &iDataOffset, char* &pData)
{
	int iContinueBytes = 0;
	iContinueBytes = head->get_right() - head->get_left() + 1;
	iDataOffset = head_offset + head->get_left();
	pData = &m_pData[head->get_left()];
	return iContinueBytes;
}

int StreamBuffer::RemoveData(int iBytes)
{
	int iBytesRemoved = 0;
	memcpy(m_pData, m_pData + iBytes, BUFFER_LEN - iBytes);
	m_iBufferLen -= iBytes;
	head_offset += iBytes;
	head->set_right(head->get_right() - iBytes);
	Record *pt = head->get_next();
	while (NULL != pt)
	{
		pt->set_left(pt->get_left() - iBytes);
		pt->set_right(pt->get_right() - iBytes);
		pt = pt->get_next();
	}
	return iBytesRemoved;
}

unsigned int StreamBuffer::GetHeadOffset()
{
	return head_offset;
}
//正能量接口来了= =b
int StreamBuffer::CleanDate(unsigned int &iDataoffset, char* &pData)
{
	//用户可以通过循环调用此接口将缓存区中所有数据取走
	//与continueBytes的区别为去除第一块不完整数据
	ofstream errlog("err.log");
	errlog << head_offset << " to " << head->get_next()->get_next() << " was lost!" << endl;
	int iContinueBytes = 0;
	int move = head->get_next()->get_left();
	head_offset += move;
	m_iBufferLen -= (head->get_right() - head->get_left() + 1);
	Record *temp = head;
	head = head->get_next();
	delete temp;
	memcpy(m_pData, m_pData + head->get_left(), BUFFER_LEN - head->get_left() + 1);
	temp = head;
	while (NULL != temp)
	{
		temp->set_left(temp->get_left() - move);
		temp->set_right(temp->get_right() - move);
		temp->set_next(temp->get_next());
	}
	iContinueBytes = ContinueBytes(iDataoffset, pData);
	return iContinueBytes;
}