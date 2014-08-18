#if !define PROGRAM
#define PROGRAM

#include "StreamBuffer.h"

struct BufferNode
{
	StreamBuffer* addr;
	BufferNode* next;
};

class Program
{
	public:
	Program(int id);
	~Program();
	void ReceiveData(unsigned int offset, char* data);
	BufferNode* get_buffer_list();

	private:
	int program_id;
	BufferNode* buffer_list;
};

#endif