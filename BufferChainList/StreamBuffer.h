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
	int CleanDate(unsigned int &iDataoffset, char* &pData); //����׿鲻�������ݲ����صڶ����������ݵĳ���

	Record *r_Find(unsigned int left, unsigned int right);
	Record *r_Insert(unsigned int left, unsigned int right); //head�ĵ�ַ��Ӧʵ������ָ��ָ���ָ��
	void r_CleanUp(Record *start = NULL); //clean up from head;

	private:

	char *m_pData;
	int m_iBufferLen;
	unsigned int head_offset;
	unsigned int start_offset;
	Record *head;
};

#endif