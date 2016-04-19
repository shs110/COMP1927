// main.c ... Play with trees

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include "Tree.h"

int main(int argc, char **argv)
{
	Tree  myTree;  // binary search tree

	myTree = scan(stdin);
	show(myTree); printf("\n");
	if (isBST(myTree))
		printf("Tree is a binary search tree\n");
	else
		printf("Tree is NOT a binary search tree\n");
	return 0;
}

