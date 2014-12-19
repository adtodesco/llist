/* llist.c */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "llist.h"



/* create and return an empty list */
LList* LList_init() {
	LList *newList = (LList *)malloc(sizeof(LList));
	newList->head = NULL;
	newList->tail = NULL;
	newList->size = 0;
	return newList;
}


/* return size (number of elements)  of list */
int LList_size(LList* l) {

	return l->size; 
} 


/* print all values in the list in order form head to tail  */
void LList_print(LList * l) {
	Node *temp = l->head;
	while(temp != NULL) {
		printf("%d\n", temp->value);
		temp = temp->next;
	}
}

/* return the head of the list */
Node *LList_head(LList *l) {

	return l->head;
}

/* return the tail of the list */
Node *LList_tail(LList *l) {

	return l->tail;
}

/* create a new node with value=key and insert it in the  list at the head */
void LList_insert_at_head(LList *l, int key) {
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->value = key;
	if(l->head == NULL) {
		newNode->next = NULL;
		newNode->prev = NULL;
		l->head = newNode;
		l->tail = newNode;
	}
	else {
		l->head->prev = newNode;
		newNode->next = l->head;
		newNode->prev = NULL;
		l->head = newNode;
	}
	l->size++;
}

/* This operation assumes the list is sorted in increasing order of
   the values.  It create a new node with value=key and insert it in the
   list in the right place (ie before the first node that's larger than
   the key) */
void LList_insert_in_order(LList *l, int key) {
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->value = key;
	if (l->size == 0) {
		LList_insert_at_head(l, key);
	} else if (l->tail->value < key) {
		Node *temp = l->head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newNode;
		newNode->next = NULL;
		newNode->prev = temp;
		l->tail = newNode;
		l->size++;
	} else if (l->head->value >= key) {
		LList_insert_at_head(l, key);
	} else {
		Node *lesser = l->head;
		while (lesser->next->value < key) {
			lesser = lesser->next;
		}
		Node *greater = lesser->next;
		newNode->next = greater;
		newNode->prev = lesser;
		lesser->next = newNode;
		greater->prev = newNode;
		l->size++;
	}
	assert(LList_is_sorted(l));
}


/* this function checks if the list is sorted in incresing order;
   return 1 if list is sorted, 0 otherwise*/
int LList_is_sorted(LList *l) {
	Node *temp = l->head;
	while(temp->next != NULL) {
		if (temp->value > temp->next->value) {
			return 0;
		}
		temp = temp->next;
	}
	return 1; 
}

/* delete the node at the tail from the list and return it. It does
   NOT free the node.  */ 
Node* LList_delete_at_tail(LList *l) {
	Node *delete = l->tail;
	if (l->size == 1) {
		l->head = NULL;
		l->tail = NULL;
	}
	else {
		Node *newEnd = delete->prev;
		newEnd->next = NULL;
		l->tail = newEnd;
	}
	l->size--;
	return delete;
}

Node* LList_delete_at_head(LList *l) {
	Node *delete = l->head;
	if (l->size == 1) {
		l->head = NULL;
		l->tail = NULL;
	}
	else {
		Node *newEnd = delete->next;
		newEnd->prev = NULL;
		l->head = newEnd;
	}
	l->size--;
	return delete;

}

/* assume n is pointing to a node in l; delete it from the list (link
   its predeccor to it's sucessor). It does NOT free the node.  */
void  LList_delete(LList* l, Node* n) {
	Node *delete = l->head;
	while (delete != n && delete->next != NULL) {
		delete = delete->next;
	}
	if (delete->next == NULL) {
		LList_delete_at_tail(l);
	} else if (delete->prev == NULL) {
		LList_delete_at_head(l);
	} else {
		(delete->prev)->next = delete->next;
		(delete->next)->prev = delete->prev;
		l->size--;
	}
}

/* delete and free all nodes in the list */
void LList_delete_all(LList* l) {
	int i;
	Node *deleted;
	for (i = 0; i < l->size; i++) {
		deleted = LList_delete_at_tail(l);
		free(deleted);
	}
}

/* delete and free all nodes in the list and the list  */
void LList_free(LList* l) {
	LList_delete_all(l);
	free(l);
}

