typedef struct IndexNode
{
	unsigned int left, right;
	struct IndexNode *next;
} NODE;

using namespace std;

NODE *Find(NODE *head, unsigned int left, unsigned int right)
{
	NODE *p = head;
	while(p->next != NULL)
	{
		if (left >= p->left && left <= (p->next)->left)
		{
			break;
		}
		else
		{
			p = p->next;
		}
	}
	return p;
}

NODE *Insert(NODE **head, unsigned int left, unsigned int right)
{
	if (*head == NULL)
	{
		*head = new NODE;
		(*head)->left = left;
		(*head)->right = right;
		(*head)->next = NULL;
		return *head;
	}
	if (right + 1 < ((*head)->left))
	{
		NODE *node = NULL;
		node = new NODE;
		node->left = left;
		node->right = right;
		node->next = *head;
		*head = node;
		return node;
	}
	else if (left < (*head)->left)
	{
		(*head)->left = left;
		if ((*head)->right < right)
		{
			(*head)->right = right;
		}
		return *head;
	}
	else
	{
		NODE *find = NULL;
		find = Find(*head, left, right);
		if (left <= find->right + 1)
		{
			if (right > find->right)
			{
				find->right = right;
				return find;
			}
		}
		else
		{
			NODE *node = NULL;
			node = new NODE;
			node->left = left;
			node->right = right;
			node->next = find->next;
			find->next = node;
			return node;
		}
	}
}
void CleanUp(NODE *start)
{
	NODE *pt = NULL, *temp = NULL;
	pt = start;
	while(pt->next != NULL)
	{
		temp = pt->next;
		if (temp->left <= pt->right + 1)
		{
			if (temp->right > pt->right)
			{
				pt->right = temp->right;
				pt->next = temp->next;
				delete temp;
			}
			else
			{
				pt->next = temp->next;
				delete temp;
			}
		}
		else
		{
			pt = pt->next;
		}
	}
}
int Count(NODE *head)
{
	NODE *temp = NULL;
	int sum = 0;
	temp = head;
	while(temp != NULL)
	{
		sum++;
		temp = temp-> next;
	}
	return sum;
}
void Show(NODE *head)
{
	NODE *temp = NULL;
	temp = head;
	while(temp != NULL)
	{
		cout << "[" << temp->left << ", " << temp->right << "]" <<endl;
		temp = temp->next;
	}
}
