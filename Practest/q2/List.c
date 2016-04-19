// List.c ... implementation of simple List ADT

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "List.h"

typedef struct Node *Link;

typedef struct Node {
	int  value;
	Link next;
} Node;

typedef struct ListRep {
	int  nnodes;
	Link first;
	Link last;
} ListRep;

// newList ... make new empty List
List newList()
{
	List new = malloc(sizeof(ListRep));
	assert(new != NULL);
	new->nnodes = 0;
	new->first = NULL;
	new->last = NULL;
	return new;
}

// ListShow ... display List as <a, b, c, d, ...z>
void ListShow(List L)
{
	assert(L != NULL);
	printf("[");
	Link curr = L->first;
	while (curr != NULL) {
		printf("%d",curr->value);
		if (curr->next != NULL) printf(", ");
		curr = curr->next;
	}
	printf("]\n");
}

// ListLength ... number of nodes in List
int ListLength(List L)
{
	assert(L != NULL);
	return (L->nnodes);
}

// ListAppend ... append a new value to List
void ListAppend(List L, int value)
{
	assert(L != NULL);
	Link new = malloc(sizeof(Node));
	assert(new != NULL);
	new->value = value;
	new->next = NULL;
	L->nnodes++;
	if (L->first == NULL)
		L->first = L->last = new;
	else {
		L->last->next = new;
		L->last = new;
	}
}

// ListReverse ... reverse a List
void ListReverse(List L)
{
	Link Lcurr1 = L->first;
	Link Lcurr2 = L->first;
	int j = 0;
	int i = 0;
	//int temp1 = 0;
	if (L->first != NULL){
		j = L->nnodes;
		for (i=0 ; i < j/2 ; i++){
			int count1 = 1;
			int count2 = 1;
			int temp = 0;
			
			Lcurr1 = L->first;
			Lcurr2 = L->first;
			while (count1 != (j-i)){
				Lcurr1 = Lcurr1->next;
				count1 ++;
			}
			while (count2 != (i+1)){
				Lcurr2 = Lcurr2->next;
				count2 ++;
			}
			temp = Lcurr2->value;
			Lcurr2->value = Lcurr1->value;
			Lcurr1->value = temp;
		}
	}
}


/*
new->first->next->value = L->last->value;

		new->nnodes++;
		Link newcurr = new->first;
		while (new->nnodes != L->nnodes){			
			while (Lcurr->next != L->last){
				Lcurr = Lcurr->next;
			}
			newcurr->next = Lcurr;
			L->last = Lcurr;
			new->nnodes++;
		}
		newcurr->next = NULL;
		new->last = newcurr;
		L = new;
		*/