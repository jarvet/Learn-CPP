#if !define PROGRAM
#define PROGRAM

#include "StreamBuffer.h"

struct BufferNode
{
	StreamBuffer* addr;
	unsigned int begin_offset;
	BufferNode* next;
};

class Program
{
	public:
	Program(int id);
	~Program();
	void ReceiveData(unsigned int offset, char* data);
	void WriteToHardDisk();
	void EndToWrite();
	BufferNode* get_buffer_list();

	private:
	int program_id;
	BufferNode* buffer_list;
	Record* written;
};

#endif