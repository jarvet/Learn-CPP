#if !define CONTROL
#define CONTROL

#include "StreamBuffer.h"
#include "DataBag.h"
#include "Program.h"

struct MapNode
{
	int pro_id;
	Program* pro_addr;
	//用于记录节目buffer的链表
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
	//正在管理的建墓列表（链表）
	MapNode* map_head;
	MapNode* map_tail;
	//当前数据包信息
	int pro_id;
	unsigned int pro_offset;
	char* pro_data;
};

#endif