#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "allocator.h"
#include "dlist.h"

int main(int argc, char *argv[]) {

    printf("Init 128 bytes\n\n");
    allocator_init(128);

    printf("allo 28 bytes\n\n");
    allocate(28);

    printf("allo 50 bytes\n\n");
    allocate(50);

    printf("allo 25 bytes\n\n");
    allocate(25);

    printf("allo 122 bytes\n\n");
    allocate(122);

    printf("traverse free list\n\n");
    traverse_forward_free();

    printf("traverse allo list\n\n");
    traverse_forward_allo();

    printf("address at index 0: %d\n\n", (int) get_allo_data(0));
    printf("address at index 1: %d\n\n", (int) get_allo_data(1));
    printf("address at index 2: %d\n\n", (int) get_allo_data(2));
    printf("address at index 3: %d\n\n", (int) get_allo_data(3)); 
    
    printf("remove address of index 1\n\n");
    deallocate(get_allo_data(1));
    
    printf("traverse allo list\n\n");
    traverse_forward_allo();
   
    printf("remove address of index 4\n\n");
    deallocate(get_allo_data(4));
    
    printf("traverse allo list\n\n");
    traverse_forward_allo();

    printf("remove address of index 0\n\n");
    deallocate(get_allo_data(0));
    
    printf("traverse allo list\n\n");
    traverse_forward_allo();

    printf("remove address of index 0\n\n");
    deallocate(get_allo_data(0));
    
    printf("traverse allo list\n\n");
    traverse_forward_allo();
    
    /*
  traverse_forward(mylist);
  traverse_backward(mylist);	
  
  dlist_destroy(mylist);
  printf("\nlist destroyed\n");
  traverse_forward(mylist);
  traverse_backward(mylist);	
  printf("\ntraversal of empty list completed\n");
  
  str1 = malloc(20);
  strncpy(str1, "folly", 20);
  
  str2 = malloc(20);
  strncpy(str2, "gunk", 20);
  
  str3 = malloc(20);
  strncpy(str3, "hospital", 20);
  
  str4 = malloc(20);
  strncpy(str4, "ignorant", 20);
  
  str5 = malloc(20);
  strncpy(str5, "jelly", 20);
  
  printf("\ntesting dlist_add_front\n");
  dlist_add_front(mylist, str1);
  dlist_add_front(mylist, str2);
  dlist_add_front(mylist, str3);
  dlist_add_front(mylist, str4);
  dlist_add_front(mylist, str5);
  
  traverse_forward(mylist);
  traverse_backward(mylist);	
  
  printf("\ntesting remove front\n");
  mystr = dlist_remove_front(mylist);
  printf("removed string = %s\n", mystr);
  free(mystr);
  printf("list length= %d\n\n", dlist_num_elems(mylist));
  traverse_forward(mylist);
  traverse_backward(mylist);	
  
  printf("\ntesting remove back\n");
  mystr = dlist_remove_back(mylist);
  printf("removed string = %s\n", mystr);
  free(mystr);
  printf("list length= %d\n\n", dlist_num_elems(mylist));
  traverse_forward(mylist);
  traverse_backward(mylist);	
  
  printf("\ntesting find_remove\n");
  mystr = dlist_find_remove(mylist, str3);
  printf("removed string = %s\n", mystr);
  free(mystr);
  printf("contents of the list\n");
  traverse_forward(mylist);
  traverse_backward(mylist);
*/
}


