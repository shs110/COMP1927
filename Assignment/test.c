#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

int main(int argc, char *argv[]){
	int i = 1;
    int n = 0;
	int size;
    int *ptr_one;
	int memory_size;
	
	printf("Type: ");
	scanf("%d", &size);
    while (size >= i){
        i = i*2;
        n++;
    }
    memory_size = i;
	if (memory_size == 0)
		{
			fprintf(stderr, "sal_init: insufficient memory");
			abort();
		}
	ptr_one = (int *)malloc(memory_size);
	
	printf("%p\n", ptr_one);


    return EXIT_SUCCESS;
}
