/* llistTester.c */


/* Use this module to test the implementation of the functions in
   llist.h.  */


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "llist.h"


int main() {

  int i;
  int a[] = { 5, 1, 10, 6, 9, 2, 7, 8, 3, 4, -1};

  //create an empty list 
  LList* l;
  l = LList_init();

  //testing inserts at head
  for(i=0; a[i] >= 0; i++) {
    LList_insert_at_head(l, a[i]);
    assert(LList_size(l) == i+1);
    printf("insert %d\n", a[i]);
    LList_print(l);
  } 

  //testing deletes at tail
  int n = LList_size(l);
  for (i=0; i<n; i++) {
    Node *node;
    node = LList_delete_at_tail(l);
    assert(node); 
    printf("deleted %d\n", node->value);
    LList_print(l);
    free(node); 
  }
  assert(LList_size(l) == 0);

  //testing inserts in order
  printf("\n");
  for(i=0; a[i] >= 0; i++) {
    LList_insert_in_order(l, a[i]);
    assert(LList_size(l) == i+1);
    printf("insert %d\n", a[i]);
    LList_print(l);
  }

  //there are elements in the list but LList_free() should take care of them 
  LList_free(l);	  
  printf("done.\n");
  return 0;
}
