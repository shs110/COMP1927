//
//  COMP1927 Assignment 1 - Memory Suballocator
//  allocator.c ... implementation
//
//  Created by Liam O'Connor on 18/07/12.
//  Modified by John Shepherd in August 2014
//  Copyright (c) 2012-2014 UNSW. All rights reserved.
//

#include "allocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define HEADER_SIZE    sizeof(struct free_list_header)
#define MAGIC_FREE     0xDEADBEEF
#define MAGIC_ALLOC    0xBEEFDEAD

typedef unsigned char byte;
typedef u_int32_t vlink_t;
typedef u_int32_t vsize_t;
typedef u_int32_t vaddr_t;

typedef struct free_list_header {
    u_int32_t magic;           // ought to contain MAGIC_FREE
    vsize_t size;              // # bytes in this block (including header)
    vlink_t next;              // memory[] index of next free block
    vlink_t prev;              // memory[] index of previous free block
} free_header_t;

free_header_t *idxToPtr (vaddr_t index); //Function to convert a memory[] index to a pointer
vaddr_t ptrToIdx (free_header_t *ptr); //Function to convert a pointer to a memory[] index

// Global data
static byte *memory = NULL;   // pointer to start of suballocator memory
static vaddr_t free_list_ptr; // index in memory[] of first block in free list
static vsize_t memory_size;   // number of bytes malloc'd in memory[]

void sal_init(u_int32_t size)
{
    int i = 1;
	struct free_list_header *first;

	//Checking to see if there were any memory allocated beforehand.
	if (memory != NULL){
		fprintf(stderr, "Block already initialised. Aborting.\n");
		abort();
	}
	//Making sure the user's requested memory is greater than 0.
	assert(size > 0);

    while (size >= i){
        i = i*2;
    }
	//malloc memory
	memory = malloc(i);
	//Checking to make sure memory isn't NULL
	if (memory == NULL){
		printf("ERROR: Out of memory\n");
	}
	first = (struct free_list_header*)memory;

	first->magic = MAGIC_FREE;
	first->next = 0;
	first->prev = 0;
    first->size = i;
	free_list_ptr = 0;
	memory_size = i;
}

void *sal_malloc(u_int32_t n) {
    free_header_t *current = (struct free_list_header*)memory;
	free_header_t *previous = (struct free_list_header*)memory;
	free_header_t *last = (struct free_list_header*)memory;
	previous->size = memory_size;
	current->size = memory_size;
	last = idxToPtr(memory_size/2);

	//Checking the arbitary number in the header is correct.
	if (current->magic != MAGIC_FREE){
		fprintf(stderr, "Memory corruption\n");
		abort();
	}

   //does the first halving
    if (HEADER_SIZE + n < previous->size && HEADER_SIZE + n < previous->size/2) {
		int initialsize = previous->size/2;
		free_list_ptr = previous->size/(2*sizeof(free_header_t));
		previous = idxToPtr(free_list_ptr);
		previous->next = free_list_ptr;
		previous->prev = free_list_ptr;
		previous->size = initialsize;
		previous->magic = MAGIC_FREE;
    } else {
      printf("ERROR: Out of memory\n");
    }
   //does second halving
    if (HEADER_SIZE + n < previous->size && HEADER_SIZE + n < previous->size/2) {
		current = previous;
        free_list_ptr = previous->size/(2*sizeof(free_header_t));
		previous = idxToPtr(free_list_ptr);
		current->next = free_list_ptr;
		current->prev = free_list_ptr;
		previous->next = ptrToIdx(current);
		previous->prev = ptrToIdx(current);
		previous->size = current->size/2;
		previous->magic = MAGIC_FREE;
    }
	//does the rest of the halving
    while (HEADER_SIZE + n < previous->size && HEADER_SIZE + n < previous->size/2) {
		current = previous;
		free_list_ptr = previous->size/(2*sizeof(free_header_t));
		previous = idxToPtr(free_list_ptr);
		previous->next = ptrToIdx(current);
		previous->prev = current->prev;
		previous->magic = MAGIC_FREE;
		previous->size = current->size/2;
		current->prev = free_list_ptr;
		last->next = free_list_ptr;
	}
    free_header_t *start = (free_header_t *)memory;
    start->magic = MAGIC_ALLOC;
    start->next = 0;
    start->prev = 0;
    start->size = previous->size;
	
	return ((void*)(start + HEADER_SIZE));
}

void sal_free(void *object)
{
	//Free
    free_header_t *start = idxToPtr(free_list_ptr);
	free_header_t *last = idxToPtr(memory_size/2);
	free_header_t *first = (struct free_list_header*)memory;
	free_header_t *second;
	free_header_t *third;
	second = ((struct free_list_header*)memory);
	third = ((struct free_list_header*)memory);
	
	//Built in error checking, if passes then free
	if (first->magic == MAGIC_ALLOC) {
        first->next = ptrToIdx(start);
        first->prev = ptrToIdx(last);
        start->prev = ptrToIdx(first);
        last->next = ptrToIdx(first);
        first->magic = MAGIC_FREE;
	} else {
        fprintf(stderr, "Attempt to free non-allocated memory\n");
		abort();
	}

	//Merge
	first = (struct free_list_header*)memory;
    second = idxToPtr(first->next);
    third = idxToPtr(second->next);
	//Loop to merge all free regions together
    while(first != last && first != second) {
        if( first->size == second->size && first->magic == MAGIC_FREE && second->magic == MAGIC_FREE) {
            first->next = ptrToIdx(third);
            third->prev = ptrToIdx(first);
            second = idxToPtr(first->next);
            third = idxToPtr(second->next);
        } else {
            first = idxToPtr(first->next);
            second = idxToPtr(second->next);
            third = idxToPtr(third->next);
        }
        first = idxToPtr(first->next);
    }

}

void sal_end(void)
{
	//Free the memory allocated in sal_init
    free(memory);
}

void sal_stats(void)
{
    //Optional, but useful
	//Written by Clement Ng. Using it with permission to help with code.
    printf("sal_stats:\n");

    printf("   memory size:        %d\n", memory_size);
    printf("   memory assigned to: 0x%x\n", *memory);
    printf("   free_list_ptr:      %d\n", free_list_ptr);

    printf(" all nodes stats:\n");
    free_header_t *curr = (void *)(memory + 0);
    vaddr_t chosen_ptr = 0;
    while(chosen_ptr + curr->size < memory_size) {
        printf("curr:  %d\t", chosen_ptr);
        printf("next:  %d\t", curr->next);
        printf("prev:  %d\t", curr->prev);
        printf("size:  %d\t", curr->size);
        if(curr->magic == MAGIC_FREE) {
            printf("magic: free\n");
        } else {
            printf("magic: allocated\n");
        }

        curr = (void *)(memory + chosen_ptr + curr->size);
        chosen_ptr = (void *)curr - (void *)memory;
        //printf("chosen ptr post %d\n\n", chosen_ptr);
    }
    printf("curr:  %d\t", chosen_ptr);
    printf("next:  %d\t", curr->next);
    printf("prev:  %d\t", curr->prev);
    printf("size:   %d\t", curr->size);
    if(curr->magic == MAGIC_FREE) {
        printf("magic: free\n");
    } else {
        printf("magic: allocated\n");
    }

}

vaddr_t ptrToIdx (free_header_t *ptr) {
    vaddr_t index = (byte *)ptr - memory;
    return index;
}

free_header_t *idxToPtr (vaddr_t index) {
    free_header_t *ptr = (void *)memory + index;
    return ptr;
}