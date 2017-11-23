#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include <stdint.h>
#include <stdbool.h>

/*
 * the data member of any given dnode
 */
struct data_member {
    int size; 
    void *mem_loc;
};

/**
 * Create and initalize two doubly linked lists.
 * 
 * @param size the byte size requested for contiguous space.
 * @return -1 if fail otherwise 0.
 */
int allocator_init(size_t size);

/**
 * allocate a contiguous chunk of memory
 *
 * @param size the requested size of memory for the allocation
 * @return NULL if no chunk of memory is large enough for size
 */
void *allocate(size_t size);

/**
 * frees a chunk of memory
 *
 * @param ptr pointer to a node in the allocated_list to be deallocated
 * @return -1 upon failure otherwise 0.
 */
int deallocate(void *ptr);

/**
 * Creates a mnode
 *
 * @param size of the node
 * @return the data_member created
 */
struct data_member *mnode_create(size_t size);

/**
 * finds the first node in the free_list to allocate
 *
 * @param size of the data being allocated
 * @return the struct of the node allocated
 */
struct data_member *first_fit(size_t size);

/**
 * allocate smallest hole which is big enough
 *
 * @param size of the data being allocated
 * @return teh struct of the node allocated
 */
struct data_member *best_fit(size_t size);

/**
 * allocated the largest hole
 *
 * @param size of the data being allocated
 * @return the struct of the node allocated
 */
struct data_member *worst_fit(size_t size);

/**
 * print the free_list addreseses from front to back
 */
void traverse_forward_free();

/**
 * print the allocated_list addresses from front to back
 */
void traverse_forward_allo();

/**
 * get the free_list
 *
 * @return pointer to the free_list
 */
struct dlist *get_free();

/**
 * get the allocated_list
 *
 * @return pointer to the allocated_list
 */
struct dlist *get_allo();

/**
 * get allo iter begin
 *
 * @return pointer to the first node's data in allocated_list
 */
void *get_allo_begin();

/**
 * get allo data
 *
 * @param n integer of index you want the data from
 * @return pointer to the appropriate onde's data in allocated_list
 */
int *get_allo_data(int n);

#endif /* _ALLOCATOR_H_ */
