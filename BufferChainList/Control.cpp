#include "Control.h"

Control::Control()
{
	map_head = NULL;
	pro_id = 0;
	pro_offset = 0;
	pro_data = NULL;
}

void Control::ReceiveDataBag(DataBag data)
{
	pro_id = data.get_id();
	pro_offset = data.get_offset();
	pro_data = data.get_data();
}

void Control::PreHandle()
{
	if (NULL == map_head)
	{
		MapNode *temp;
		temp->pro_id = pro_id;
		temp->pro_addr = new Program(pro_id);
		temp->buffer_head = NULL;
		temp->next = NULL;
		temp->buffer_head = temp->pro_addr->get_buffer_list();
		map_head = map_tail =temp;
		map_head->pro_addr->ReceiveData(pro_offset, pro_data);
	}
	else
	{
		int flag = 0;
		MapNode *temp = map_head;
		while (NULL != temp)
		{
			if (temp->pro_id == pro_id)
			{
				flag = 1;
				temp->pro_addr->ReceiveData(pro_offset, pro_data);
				break;
			}
			else
			{
				temp = temp->next;
			}
		}
		if (!flag)
		{
			temp = new MapNode;
			temp->next = NULL;
			temp->pro_id = pro_id;
			temp->pro_addr = new Program(pro_id);
			temp->buffer_head = NULL;
			map_tail->next = temp;
			map_tail = temp;
			temp->buffer_head = temp->pro_addr->get_buffer_list();
			map_tail->pro_addr->ReceiveData(pro_offset, pro_data);
		}
	}
}