#if !define STREAMBUFFER
#define STREAMBUFFER

#include "Record.h"

using namespace std;

class StreamBuffer
{
	public:

	StreamBuffer();
	~StreamBuffer();

	void ReceiveDate(unsigned int offset, unsigned int bytes, char *pData);
	int ContinueBytes(unsigned int &iDataoffset, char* &pData);
	int RemoveData(int iBytes);
	int CleanDate(unsigned int &iDataoffset, char* &pData); //清除首块不连续数据并返回第二块完整数据的长度

	Record *r_Find(unsigned int left, unsigned int right);
	Record *r_Insert(unsigned int left, unsigned int right); //head的地址对应实验三中指向指针的指针
	void r_CleanUp(Record *start = NULL); //clean up from head;

	private:

	char *m_pData;
	int m_iBufferLen;
	unsigned int head_offset;
	unsigned int start_offset;
	Record *head;
};

#endif