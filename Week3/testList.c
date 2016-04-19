// testList.c - testing List data type
// Written by John Shepherd, March 2013
/*
	Ran tests for myed.
	Completed John Shepherd's tests

*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "List.h"

int main(int argc, char *argv[])
{
	char *item0 = "0";
	char *item1 = "1";
	char *item2 = "2";
	char *item3 = "3";
	char *item4 = "4";
	
	List myList;
	//create
	myList = newList();

	ListDelete(myList);//tests ListDelete for empty list
    printf ("Showing list...\n");
    showList(stdout,myList);
    printf ("List should be:   \n");
	validList(myList);
    
	ListBefore(myList,item0);//tests ListBefore() for empty list
	printf ("Showing list...\n");
    showList(stdout,myList);
    printf ("List should be: 0\n");
    validList(myList);
    
	ListBefore(myList,item1);//tests ListBefore
	ListBefore(myList,item2);
    printf ("Showing list...\n");
    showList(stdout,myList);
    printf ("List should be: 2 1 0\n");
    validList(myList);
 
        
	ListAfter(myList,item3);//tests ListAfter for empty list
    printf ("Showing list...\n");
    showList(stdout,myList);
    printf ("List should be: 2 3 1 0\n");
    validList(myList);

	ListAfter(myList,item4);//tests ListAfter
    printf ("Showing list...\n");
    showList(stdout,myList);
    printf ("List should be: 2 3 4 1 0\n");
    validList(myList);
    
    ListDelete(myList);//tests current correctly changes with ListDelete
    printf ("Showing list...\n");
    showList(stdout,myList);
    printf ("List should be: 2 3 1 0\n");
  	validList(myList);

    

	return 0;
}
