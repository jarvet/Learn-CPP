#if !defined  SREAM_BUFFER_H_2014_07_14_HIT_CPP
#define SREAM_BUFFER_H_2014_07_14_HIT_CPP
struct NODE
{
	unsigned int left, right;
	struct NODE *next;
};

using namespace std;
NODE *Find(NODE *head, unsigned int left, unsigned int right);
NODE *Insert(NODE **head, unsigned int left, unsigned int right);
void CleanUp(NODE *start);
int Count(NODE *head);
void Show(NODE *head);

#endif