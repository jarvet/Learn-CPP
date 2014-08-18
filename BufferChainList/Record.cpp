#include "Record.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

Record::Record(unsigned int left, unsigned int right, Record *next)
{
	r_left = left;
	r_right = right;
	r_next = next;
}

unsigned int Record::get_left()
{
	return r_left;
}

unsigned int Record::get_right()
{
	return r_right;
}

Record* Record::get_next()
{
	return r_next;
}

void Record::set_left(unsigned int left)
{
	r_left = left;
}

void Record::set_right(unsigned int right)
{
	r_right = right;
}

void Record::set_next(Record *next)
{
	r_next = next;
}