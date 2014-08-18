#include "DataBag.h"
#include <string.h>

DataBag::DataBag(int id, unsigned int offset, char*data)
{
	p_id = id;
	p_offset = offset;
	memcpy(p_data, data, strlen(data));
}

int DataBag::get_id()
{
	return p_id;
}

unsigned int DataBag::get_offset()
{
	return p_offset;
}

char* DataBag::get_data()
{
	return p_data;
}