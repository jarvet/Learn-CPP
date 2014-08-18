#if !define CONTROL
#define CONTROL

#include "StreamBuffer.h"
#include "DataBag.h"
#include "Program.h"

struct MapNode
{
	int pro_id;
	Program* pro_addr;
	//���ڼ�¼��Ŀbuffer������
	BufferNode* buffer_head;
	static MapNode* next;
};

class Control
{
	public:
	Control();
	~Control();
	void ReceiveDataBag(DataBag data);
	void PreHandle();

	private:
	//���ڹ���Ľ�Ĺ�б�����
	MapNode* map_head;
	MapNode* map_tail;
	//��ǰ���ݰ���Ϣ
	int pro_id;
	unsigned int pro_offset;
	char* pro_data;
};

#endif