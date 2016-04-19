// List.h - list-of-integers interface

#ifndef LIST_H
#define LIST_H

#include <stdio.h>

// External view of List
// Implementation given in List.c

typedef struct ListNode *List;

// create a new empty List
List newList();

// insert one integer at end of list
List insert(List, int);

// return number of elements in a list
int length(List);

// find longest ascending sublist of a List
List flas(List L);

// create an List by reading values from a file
// assume that the file is open for reading
List scan(FILE *);

// display list on a single line as A -> B -> C -> D ...
void show(List);

// display ascending prefix of list
void showAscending(List L);

#endif
