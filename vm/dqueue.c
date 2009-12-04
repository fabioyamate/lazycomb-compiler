#include "vm.h"

struct _dqueue
{
	dlist sentinel;
};

dqueue  dq_create(void)
{
	dqueue q = (dqueue)malloc(sizeof(struct _dqueue));
	q -> sentinel = dcons(NULL, NULL, NULL);
	q -> sentinel -> next = q -> sentinel -> prev = q -> sentinel;
	return q;
}

int
dq_empty(dqueue q)
{
	return q -> sentinel -> next == q -> sentinel;
}

void
dq_enq_front(dqueue q, void *element)
{
	create_and_link(element, q -> sentinel, q -> sentinel -> next);
}

void
dq_enq_back(dqueue q, void *element)
{
	create_and_link(element, q -> sentinel -> prev, q -> sentinel);
}

void *
dq_deq_front(dqueue q)
{
	assert(!dq_empty(q));
	return unlink_and_free(q -> sentinel -> next);
}

void *
dq_peek_front(dqueue q)
{
	assert(!dq_empty(q));
	return q -> sentinel -> next -> element;
}

void *
dq_deq_back(dqueue q)
{
	assert(!dq_empty(q));
	return unlink_and_free(q -> sentinel -> prev);
}

void *
dq_peek_back(dqueue q)
{
	assert(!dq_empty(q));
	return q -> sentinel -> prev -> element;
}

//void *
//dq_at(dqueue q, int position)
//{
//	assert(!dq_empty(q)); assert(position > 0);
//	int i = 0;
//	dlist current = dq_peek_back(q);
//	while(i != position)
//	{
//		if(current == q->sentinel->next)
//			return 0;
//	}
//	return current;
//}
