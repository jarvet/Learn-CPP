#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "ex02.h"

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
    char m_data[512*1024];//存数据的buffer，也可以用指针
	unsigned int head_offset; //用于记录缓存区中的第一个字节在文件中的偏移量
	NODE *head;
	//...
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
   // to do： ...
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
   return iBytes;// bytes the buffer saved
}

int StreamBuffer::ContinueBytes(unsigned int &iDataOffset, char* &pData)
{//返回缓冲区中，排好序的数据的长度（单位字节数）。并通过引用参数返回如下信息
 //iDataOffset: 排好序的数据块中第一个字节的偏移量数值
 //pData：数据指针
  int iContinueBytes = 0;
  iContinueBytes = head->right - head->left + 1;
  iDataOffset = head_offset + head->left;
  pData = &m_data[head->left];
  // to do： ...
  return iContinueBytes;
};


int StreamBuffer::RemoveData(int iBytes)
{//从缓冲区中把数据"删除",返回删除的字节数
  int iBytesRemoved=0;

   // to do： ...
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
   //从缓冲区中把数据"删除"
   return iBytesRemoved;
};

void	GenDisOrder(int iSendOrder[],int iPacketNum)
{
    int i,j,k;

    for(i=0;i<iPacketNum;i++)
        iSendOrder[i] = i;

    int n,temp;
    n =  rand()%(iPacketNum/4) +1;    //置乱的次数，最多50%
   for(i=0;i< n; i++)
   {//交换j、k两个数据包的顺序
         j = rand()%(iPacketNum/2);
         k = rand()%( iPacketNum - j);
        temp =  iSendOrder[j];
        iSendOrder[j] = iSendOrder[k];
        iSendOrder[k]=temp;
   }
}

int main()
{
	char srcfileName[500]="E:\\c&c++\\CPP2014\\homework\\2014-7-7\\in.mp3";
	char dstfileName[500] = "E:\\c&c++\\CPP2014\\homework\\2014-7-7\\out.mp3";
	FILE* fpSrcFile = NULL;
	FILE* fpDstFile = NULL;
	const int MTU =  1500;//最大传输单元，网络术语，表示一个数据包大最大尺寸，单位：字节
	unsigned int iOffset=0;
	int iReadBytes = 0, iWantReadBytes;

    int  iContinueBytes;
    int iUseBytes;
	unsigned int iOutDataOffset=0;
	char  *pOutData=NULL;

	StreamBuffer MyBuffer;

	const int iMaxPacketNum = 20;
	unsigned int iPacketOffset[iMaxPacketNum];
	unsigned int iPacketLen[iMaxPacketNum];
	char       (*pDataBuf)[MTU]; //方法1：指向一位数组的指针，下一步会为它申请一个二维数组
	//char     *pDataBuf[iMaxPacketNum];//  方法2
	int   iPacketNum;
	int i;
	int iSendOrder[iMaxPacketNum];
	int iPackNo;

	 pDataBuf = new char[iMaxPacketNum][MTU];//方法1
     srand(100);//用固定值初始化，会生成固定的随机数序列，方便测试程序，否则用srand( (unsigned)time( NULL ) );

	 /*for( i=0;i<iMaxPacketNum;i++)方法2
     {
         pDataBuf[i] = new char[MTU];
     }*/


	fpSrcFile = fopen(srcfileName, "rb");
	if( fpSrcFile == NULL )
	{
	  cout<<"Cann't open file: "<<srcfileName<<endl;
	  return 1;
	}

	fpDstFile = fopen(dstfileName, "wb");
	if( fpDstFile == NULL )
	{
	  cout<<"Cann't create file: "<< dstfileName <<endl;
	  return 2;
	}
	FILE* fpDstFile0 = fpDstFile;

	fseek(fpDstFile, 0, SEEK_SET);
	iWantReadBytes = 1024;

   do
   {
        iPacketNum = 0;
        for( i=0;i<iMaxPacketNum;i++)//初始化数据包长度为0，表示没有读入数据
            iPacketLen[iPacketNum] = 0;
        //	iReadBytes = fread(pDataBuf[iPacketNum], 1, iWantReadBytes, fpSrcFile);
        iPacketOffset[iPacketNum] = ftell(fpSrcFile);
        iReadBytes = fread(&(pDataBuf[iPacketNum][0]), 1, iWantReadBytes, fpSrcFile);
        while( iReadBytes > 0 && iPacketNum < iMaxPacketNum )//读入一组数据包，如果文件结束：iReadBytes<1
        {
            //当前数据包读取成功，记录数据包长度，否则依旧是0
            iPacketLen[iPacketNum] = iReadBytes;
            iPacketNum++;

            //准备读下一个数据包
            iWantReadBytes =  iPacketOffset[iPacketNum]%500+500;
            iPacketOffset[iPacketNum] = ftell(fpSrcFile);
            iReadBytes = fread(&(pDataBuf[iPacketNum][0]), 1, iWantReadBytes, fpSrcFile);
        }

        //把刚刚已经读入一组数据包，乱序下发给排序模块
        GenDisOrder(iSendOrder,iMaxPacketNum);
        for(i=0;i<	iMaxPacketNum;i++)//只要长度不为0，就发给排序模块
        {
            iPackNo = iSendOrder[i];
            if(iPacketLen[iPackNo] > 0 )//有数据，给排序模块
            {
                //MyBuffer.ReceiveDate(iPacketOffset[iPackNo],iPacketLen[iPackNo],pDataBuf[iPackNo]);
				iContinueBytes = 0;// MyBuffer.ContinueBytes(iOutDataOffset, pOutData);
				if (fpDstFile0 != fpDstFile)
					fpDstFile0 = fpDstFile0;

                // if( iContinueBytes  > 1024) //示例数值，可以调整
                {
					iUseBytes = 0;//   iContinueBytes - 100;//假设用了一部分
                   fseek(fpDstFile,iOutDataOffset,SEEK_SET);
                   fwrite(pOutData,iUseBytes,1,fpDstFile);
                   MyBuffer.RemoveData(iUseBytes);
                }
            }
        }
   }while(iReadBytes>0);//说明输入文件还有数据，继续...

	//输入结束，把缓冲区中剩余排好序的数据取出
    iContinueBytes = MyBuffer.ContinueBytes(iOutDataOffset, pOutData);
    fseek(fpDstFile,iOutDataOffset,SEEK_SET);
    fwrite(pOutData,iContinueBytes,1,fpDstFile);

    fclose(fpDstFile);
    fclose(fpSrcFile);



	 delete []pDataBuf;//方法1
	 /*for( i=0;i<iMaxPacketNum;i++)方法2
     {
         delete []pDataBuf[i];
     }*/
   // 通过比较，源文件、程序结果文件是否一致，判断程序的正确性
   //可用的文件比对软件： UltraEdit中带的UltraCompare软件。
     return 0;
	}
