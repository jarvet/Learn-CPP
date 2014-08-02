#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "ex01.h"

using namespace std;

class StreamBuffer
{
	public:
	StreamBuffer();
	int ReceiveDate(unsigned int offset, unsigned int bytes, char *pData);
	int ContinueBytes(unsigned int &iDataOffset, char* &pData);
	int RemoveData(int iBytes);
	//...
	private:
	char m_data[512 * 1024];//存数据的buffer，也可以用指针
	unsigned int head_offset;
	NODE *head;
};
//-------------------
StreamBuffer::StreamBuffer()
{
	//  to do：  some initialization work
	head_offset = 0;
	NODE *head = NULL;
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
	unsigned int start_offset_of_received_data;
	start_offset_of_received_data = offset - head_offset;
	memcpy(m_data + start_offset_of_received_data, pData, bytes);
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
	iDataOffset = head_offset;
	pData = &m_data[head->left];
	// to do： ...
	return iContinueBytes;
};


int StreamBuffer::RemoveData(int iBytes)
{//从缓冲区中把数据"删除",返回删除的字节数
	int iBytesRemoved = 0;
	memcpy(m_data, m_data + iBytes, 512 * 1024 - iBytes);
	head_offset += iBytes;
	NODE *pt = NULL;
	head->right -= iBytes;
	pt = head->next;
	while (pt != NULL)
	{
		pt->left -= iBytes;
		pt->right -= iBytes;
	}
	// to do： ...
	//从缓冲区中把数据"删除"
	return iBytesRemoved;
};

int main()
{

	char srcfileName[500] = "E:\\c&c++\\CPP2014\\homework\\2014-7-5\\in.mp3";
	char dstfileName[500] = "E:\\c&c++\\CPP2014\\homework\\2014-7-5\\out.mp3";
	FILE* fpSrcFile = NULL;
	FILE* fpDstFile = NULL;
	char Buf[1500 * 2];
	unsigned int iOffset;
	int iReadBytes = 0, iWantReadBytes;

	int  iContinueBytes;
	int iUseBytes;
	unsigned int iOutDataOffset;
	char  *pOutData;

	StreamBuffer MyBuffer;

	fpSrcFile = fopen(srcfileName, "rb");
	if (fpSrcFile == NULL)
	{
		cout << "Cann't open file: " << srcfileName << endl;
		return 1;
	}

	fpDstFile = fopen(dstfileName, "wb");
	if (fpDstFile == NULL)
	{
		cout << "Cann't create file: " << dstfileName << endl;
		return 2;
	}

	iOffset = ftell(fpSrcFile);
	iWantReadBytes = 1024;
	iReadBytes = fread(Buf, 1, iWantReadBytes, fpSrcFile);
	while (iReadBytes > 0)
	{
		MyBuffer.ReceiveDate(iOffset, iReadBytes, Buf);
		iContinueBytes = MyBuffer.ContinueBytes(iOutDataOffset, pOutData);
		if (iContinueBytes  > 1024) //示例数值，可以调整
		{
			iUseBytes = iContinueBytes - 100;//假设用了一部分
			fseek(fpDstFile, iOutDataOffset, SEEK_SET);
			fwrite(pOutData, iUseBytes, 1, fpDstFile);
			MyBuffer.RemoveData(iUseBytes);
		}


		iOffset = ftell(fpSrcFile);
		iWantReadBytes = iOffset % 500 + 500;
		iReadBytes = fread(Buf, 1, iWantReadBytes, fpSrcFile);
	}

	//输入流结束，把缓冲区中所有排好序的数据取出
	iContinueBytes = MyBuffer.ContinueBytes(iOutDataOffset, pOutData);
	fseek(fpDstFile, iOutDataOffset, SEEK_SET);

	fwrite(pOutData, iContinueBytes, 1, fpDstFile);

	fclose(fpDstFile);
	fclose(fpSrcFile);

	// 通过比较，源文件、程序结果文件是否一致，判断程序的正确性
	//可用的文件比对软件： UltraEdit中带的UltraCompare软件。
	return 0;
}
