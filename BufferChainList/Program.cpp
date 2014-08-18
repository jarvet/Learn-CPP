#include "Program.h"

Program::Program(int id)
{
	program_id = id;
	buffer_list = new BufferNode;
	buffer_list->addr = NULL;
	buffer_list->next = NULL;
}