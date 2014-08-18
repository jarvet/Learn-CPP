#if !define RECORD
#define RECORD

#include <stdlib.h>

using namespace std;

class Record
{
	public:

	Record(unsigned int left, unsigned int right, Record *next = NULL);

	unsigned int get_left();
	unsigned int get_right();
	Record *get_next();

	void set_left(unsigned int left);
	void set_right(unsigned int right);
	void set_next(Record *next);

	private:

	unsigned int r_left;
	unsigned int r_right;
	Record *r_next;
};

#endif