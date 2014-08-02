#if !defined  SREAM_BUFFER_H_2014_07_07_HIT_CPP
#define SREAM_BUFFER_H_2014_07_07_HIT_CPP
#include<iostream>
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

struct NODE
{
	unsigned int left, right;
	struct NODE *next;
};

NODE *Find(NODE *head, unsigned int left, unsigned int right);
NODE *Insert(NODE **head, unsigned int left, unsigned int right);
void CleanUp(NODE *start);
int Count(NODE *head);
void Show(NODE *head);

class StreamBuffer
{
 public:
    StreamBuffer();
    ~StreamBuffer();
    StreamBuffer(int iLen);
	int ReceiveDate(unsigned int offset, unsigned int bytes, char *pData);
	int ContinueBytes(unsigned int &iDataOffset, char* &pData);
	int RemoveData(int iBytes);
	//...
 private:
    char *m_pData;//存数据的buffer，也可以用指针
    int m_iBufferLen;
	unsigned int head_offset;
	NODE *head;
	//...
};

#endif
