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
	char m_data[512 * 1024];//�����ݵ�buffer��Ҳ������ָ��
	unsigned int head_offset;
	NODE *head;
};
//-------------------
StreamBuffer::StreamBuffer()
{
	//  to do��  some initialization work
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
	// to do�� ...
	return iBytes;// bytes the buffer saved
}

int StreamBuffer::ContinueBytes(unsigned int &iDataOffset, char* &pData)
{//���ػ������У��ź�������ݵĳ��ȣ���λ�ֽ���������ͨ�����ò�������������Ϣ
	//iDataOffset: �ź�������ݿ��е�һ���ֽڵ�ƫ������ֵ
	//pData������ָ��
	int iContinueBytes = 0;
	iContinueBytes = head->right - head->left + 1;
	iDataOffset = head_offset;
	pData = &m_data[head->left];
	// to do�� ...
	return iContinueBytes;
};


int StreamBuffer::RemoveData(int iBytes)
{//�ӻ������а�����"ɾ��",����ɾ�����ֽ���
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
	// to do�� ...
	//�ӻ������а�����"ɾ��"
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
		if (iContinueBytes  > 1024) //ʾ����ֵ�����Ե���
		{
			iUseBytes = iContinueBytes - 100;//��������һ����
			fseek(fpDstFile, iOutDataOffset, SEEK_SET);
			fwrite(pOutData, iUseBytes, 1, fpDstFile);
			MyBuffer.RemoveData(iUseBytes);
		}


		iOffset = ftell(fpSrcFile);
		iWantReadBytes = iOffset % 500 + 500;
		iReadBytes = fread(Buf, 1, iWantReadBytes, fpSrcFile);
	}

	//�������������ѻ������������ź��������ȡ��
	iContinueBytes = MyBuffer.ContinueBytes(iOutDataOffset, pOutData);
	fseek(fpDstFile, iOutDataOffset, SEEK_SET);

	fwrite(pOutData, iContinueBytes, 1, fpDstFile);

	fclose(fpDstFile);
	fclose(fpSrcFile);

	// ͨ���Ƚϣ�Դ�ļ����������ļ��Ƿ�һ�£��жϳ������ȷ��
	//���õ��ļ��ȶ������ UltraEdit�д���UltraCompare�����
	return 0;
}
