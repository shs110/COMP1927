// main.c - manipulate Lists

#include <stdlib.h>
#include <stdio.h>
#include "List.h"

int main(int argc, char *argv[])
{
	List myList = scan(stdin);
	printf("List: ");
	show(myList);
	List longest = flas(myList);
	printf("FLAS: ");
	showAscending(longest);
	return 0;
}
