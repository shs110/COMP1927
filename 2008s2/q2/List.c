// List.c - linked-list implementation

#include <stdlib.h>
#include <stdio.h>
#include <values.h>
#include "assert.h"
#include "List.h"

// data structures representing List

typedef struct ListNode Node;

struct ListNode {
	int   data;  // value of this list item
	Node *next;  // pointer to node containing next element
};

// create a new ListNode with value v
// (this function is local to this ADT)
static Node *newListNode(int v)
{
	Node *n;
	n = malloc(sizeof (Node));
	assert(n != NULL);
	n->data = v;
	n->next = NULL;
	return n;
}

// create a new empty List
List newList()
{
	return NULL;
}

// insert one integer at end of list
List insert(List L, int v)
{
	Node *n, *p, *new = newListNode(v);
	if (L == NULL) return new;
	n = L; p = NULL;
	while (n != NULL) {
		p = n;
		n = n->next;
	}
	p->next = new;
	return L;
}

// return number of elements in a list
int length(List L)
{
	if (L == NULL)
		return 0;
	else
		return 1 + length(L->next);
}

// find longest ascending section of a List
#include "q2.c"

// create an List by reading values from a file
// assume that the file is open for reading
List scan(FILE *inf)
{
	List L; int v;
	L = newList();
	while (fscanf(inf,"%d",&v) != EOF)
		L = insert(L, v);
	return L;
}

// display list on a single line as A -> B -> C -> D ...
void show(List L)
{
	Node *n = L;
	while (n != NULL) {
		printf("%d -> ", n->data);
		n = n->next;
	}
	printf("<END>\n");
}

// display ascending prefix of a list
void showAscending(List L)
{
	Node *n = L;
	int v = MININT;
	while (n != NULL && n->data > v) {
		v = n->data;
		printf("%d -> ", v);
		n = n->next;
	}
	printf("<END>\n");
}
