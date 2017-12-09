#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "allocator.h"
#include "dlist.h"
#include <errno.h>
#include <string.h>

struct dlist *free_list;
struct dlist *allocated_list;
int alg;

int allocator_init(size_t size, int algorithm) { 
    if ((algorithm > 2) || (algorithm < 0)) {
        printf("Invalid Algorithm. 0 is first-fit, 1 is best-fit, and 2 is worst fit\n");
        return(-1);
    }
    alg = algorithm;
    free_list = dlist_create();
    allocated_list = dlist_create(); 
    void *base = malloc(size);
    if (base == NULL) {
        perror("Malloc failed\n\n");
        return(-1);
    } 
    struct data_member *data = mnode_create(size);
    data->mem_loc = base; 
    dlist_add_front(free_list, data); 
    return(0);
}


void *allocate(size_t size) {
    struct data_member *oldNode;
    if (alg == 1) {
        oldNode = best_fit(size);
    } else if (alg == 2) {
        oldNode = worst_fit(size);
    } else {
        oldNode = first_fit(size);
    }
    if (oldNode == NULL) { 
        perror("Size too large\n\n"); 
        return(oldNode);
    }  
    struct data_member *aNode = mnode_create(size);
    aNode->mem_loc = oldNode->mem_loc;
    oldNode->mem_loc += size;
    oldNode->size -= size;
    dlist_add_back(allocated_list, aNode); 
    return(aNode->mem_loc);
}

int deallocate(void *ptr) { 
    struct data_member *firstNode = dlist_iter_begin(allocated_list); 
    while (firstNode != NULL) { 
        if ((int) firstNode == (int) ptr) {
            break;
            }
        firstNode = dlist_iter_next(allocated_list);
    }
    if (firstNode == NULL) {
        perror("Memory location not found\n\n");
        return(-1);
    }
    struct data_member *aNode = mnode_create(firstNode->size);
    aNode->mem_loc = firstNode->mem_loc;
    dlist_find_remove(allocated_list, firstNode);
    dlist_add_back(free_list, aNode); 
    return(0);
}

struct data_member *first_fit(size_t size) {  
    struct dnode *firstNode = free_list->front; 
    while (firstNode != NULL) {
        if (firstNode->data->size >=  size) { // first node whose size >= size
            break;
        } 
        firstNode = dlist_iter_next(free_list);
    }
    if (firstNode == NULL) {
        return(NULL);
    } 
    return (firstNode->data);
}

struct data_member *best_fit(size_t size) {
    struct dnode *firstNode = free_list->front;
    struct dnode *bestNode = NULL;
    int bestSize = 0;
    while (firstNode != NULL) {
        if (bestSize == 0) {
            bestSize = firstNode->data->size;
            bestNode = firstNode;
        } 
        if ((firstNode->data->size >= size) && (firstNode->data->size <= bestSize)) {
            bestSize = firstNode->data->size;
            bestNode = firstNode;
        }   
        firstNode = firstNode->next;     
    }
    return(bestNode->data);
}

struct data_member *worst_fit(size_t size) {
    //copied, hence the bestnode and bestsize. but still switched the comparison in the appropriate if statement here. I should probably learn to refactor in vim.
    struct dnode *firstNode = free_list->front;
    struct dnode *bestNode = NULL;
    int bestSize = 0;
    while (firstNode != NULL) {
        if (bestSize == 0) {
            bestSize = firstNode->data->size;
            bestNode = firstNode;
        } 
        if ((firstNode->data->size >= size) && (firstNode->data->size >= bestSize)) {
            bestSize = firstNode->data->size;
            bestNode = firstNode;
        }   
        firstNode = firstNode->next;     
    }
    return(bestNode->data);
}

struct data_member *mnode_create(size_t size) {
    //printf("start mnode create\n");
    struct data_member *node = malloc(sizeof(struct data_member));
    node->size = size;
    //printf("end mnode create\n");
    return(node);
}

void traverse_forward_free() {
  struct dlist *l = free_list;
  int i;
  for (i = (int) dlist_iter_begin(l); i != 0;
       i = (int) dlist_iter_next(l))	{ 
    printf("node = %d\n", (int) i);
  }
}

void traverse_forward_allo() {
  struct dlist *l = allocated_list;
  int i; 
  for (i = (int) dlist_iter_begin(l); i != 0;
       i = (int) dlist_iter_next(l))	{ 
    printf("node = %d\n", (int) i);
  }
}

struct dlist *get_free() {
    return(free_list);
}

struct dlist *get_allo(){
    return(allocated_list);
}

void *get_allo_begin() {
    return(dlist_iter_begin(allocated_list));
}

int *get_allo_data(int n) {
    int *i = dlist_iter_begin(allocated_list);
    while (n > 0){
        i = dlist_iter_next(allocated_list);
        n--;
    }
    return( i);
}

double average_frag() {
    int max = 0;
    int total = 0;
    struct dnode *i = allocated_list->front;
    while (i != NULL) {
        if (i->data->size > max) {
            max = i->data->size;
        }
        total += i->data->size;
        i = i->next;
    }
    return( (double) (total - max) / total);
}


