#include "Program.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

Program::Program(int id)
{
	program_id = id;
	buffer_list = new BufferNode;
	buffer_list->addr = NULL;
	buffer_list->next = NULL;
}

void Program::ReceiveData(unsigned int offset, char* data)
{
	if (NULL == buffer_list->addr)
	{
		buffer_list->addr = new StreamBuffer();
		if (offset < BUFFER_LEN)
		{
			buffer_list->begin_offset = 0;
		}
		else
		{
			buffer_list->begin_offset = offset;
		}
		buffer_list->next = NULL;
		buffer_list->addr->ReceiveDate(offset, strlen(data), data);
	}
	else
	{
		BufferNode* temp = buffer_list;
		int flag = 0;
		while (NULL != temp->addr)
		{
			if (offset >= temp->addr->GetHeadOffset() && offset + strlen(data) < temp->addr->GetHeadOffset() + BUFFER_LEN)
			{
				flag = 1;
				temp->addr->ReceiveDate(offset, strlen(data), data);
				break;
			}
			else
			{
				temp = temp->next;
			}
		}
		if (!flag)
		{
			temp = new BufferNode;
			temp->begin_offset = offset;
			temp->next = NULL;
			temp->addr->ReceiveDate(offset, strlen(data), data);
			BufferNode* t = buffer_list;
			while (NULL != t->next)
			{
				t = t->next;
			}
			t->next = temp;
		}
	}
	WriteToHardDisk();
}

void Program::WriteToHardDisk()
{
	char dstfileName[500] = "dst.out";
	FILE* fpDstFile = NULL;
	char* pOutData;
	unsigned int iOutDataOffset;
	int iContinueBytes;
	int iUseBytes;

	fpDstFile = fopen(dstfileName, "wb");
	BufferNode* temp = buffer_list;
	while (NULL != temp->addr)
	{
		iContinueBytes = temp->addr->ContinueBytes(iOutDataOffset, pOutData);
		if (iContinueBytes > 1024)
		{
			iUseBytes = iContinueBytes - 100;
			fseek(fpDstFile, iOutDataOffset, SEEK_SET);
			fwrite(pOutData, iUseBytes, 1, fpDstFile);
			temp->addr->RemoveData(iUseBytes);
		}
		temp = temp->next;
	}
	fclose(fpDstFile);
}

void Program::EndToWrite()
{
	char dstfileName[500] = "dst.out";
	FILE* fpDstFile = NULL;
	char* pOutData;
	unsigned int iOutDataOffset;
	int iContinueBytes;
	StreamBuffer* temp;
	BufferNode* t;

	t = buffer_list;
	while (NULL != t->addr)
	{
		temp = t->addr;
		while (NULL != temp->r_GetHead())
		{
			temp->CleanDate(iOutDataOffset, pOutData);
		}
		t = t->next;
		delete temp;
	}
	fclose(fpDstFile);
}