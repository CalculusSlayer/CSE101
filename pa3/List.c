// -----------------------------------------------------------------------------
//  Nayeel Imtiaz, naimtiaz
//  2022 Spring CSE101 PA3
//  List.c
//  This file contains functions of the List ADT.
// -----------------------------------------------------------------------------
#include "List.h"

// structs

// private Node type
typedef struct NodeObj *Node;

// private NodeObj type
typedef struct NodeObj {
	ListElement data; 
	Node next;
	Node prev;
} NodeObj;

// private ListObj type
typedef struct ListObj {
	Node front;
	Node back;
	ListElement length;
	ListElement index;
	Node cursor;
} ListObj;

// Constructors-Destructors
// Creates and returns new node.
Node newNode(ListElement data) {
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->prev = NULL;

	return N;
}

// Free the node and set it to NULL.
// Pre: pointer not NULL
void freeNode(Node *pN) {
	if (pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}

// Creates and returns new empty list.
List newList(void) {
	List L = malloc(sizeof(ListObj));
	L->front = L->back = NULL;
	L->length = 0;
	L->index = -1;
	L->cursor = NULL;
	return L;
}

// Frees the list and sets pl to NULL.
// Pre: Pointer not NULL
void freeList(List *pL) {
	clear(*pL);
	free(*pL);
	*pL = NULL;
}

// Access Functions
// Return the number of elements.
// Pre: Not NULL
ListElement length(List L) {
	if (L) {
		return L->length;
	}

	else {
		fprintf(stderr, "Error: Called length on NULL reference.\n");
		exit(EXIT_FAILURE);
	}
}

// Return the index of the cursor of List
// Pre: Not NULL
ListElement index(List L) {
	if (L) {
		return L->index;
	}

	else {
		fprintf(stderr, "Error: called index on NULL reference.\n");
		exit(EXIT_FAILURE);
	}
}

// Return the value at the front of list
// Pre: not NULL
ListElement front(List L) {
	if (!L) {
		fprintf(stderr, "Cannot call front on a NULL reference.\n");
		exit(EXIT_FAILURE);
	}
	if (L->length > 0) {
		return L->front->data;
	}
	else {
		fprintf(stderr, "Cannot return front since length <= 0\n");
		freeList(&L);
		exit(EXIT_FAILURE);
	}
}

// Returns the value of the value at the back of list.
// Pre: not NULL
ListElement back(List L) {
	if (!L) {
		fprintf(stderr, "Cannot call back on a NULL reference.\n");
		exit(EXIT_FAILURE);
	}

	if (L->length > 0) {
		return L->back->data;
	}
	else {
		fprintf(stderr, "Cannot return back since length <= 0\n");
		freeList(&L);
		exit(EXIT_FAILURE);
	}
}

// Get the value at the cursor's location.
// Pre: Not NULL
ListElement get(List L) {
	if (!L) {
		fprintf(stderr, "Cannot call get on a NULL reference.\n");
		exit(EXIT_FAILURE);
	}

	if (length(L) <= 0) {
		fprintf(stderr, "The length is not greater than 0.\n");
		freeList(&L);
		exit(EXIT_FAILURE);
	}
	else if (index(L) < 0) {
		fprintf(stderr, "The index is not greater or equal to 0.\n");
		freeList(&L);
		exit(EXIT_FAILURE);
	}
	else {
		return L->cursor->data;
	}
}

// Checks to see if A and B are equal.
// Pre: Not NULL
bool equals(List A, List B) {
   bool eq = false;
   Node N = NULL;
   Node M = NULL;

   if( A==NULL || B==NULL ){
      printf("List Error: calling equals() on NULL List reference.\n");
	  if (A) {	// A = List = ListObj *
		  freeList(&A);
	  }

	  if (B) {
		  freeList(&B);
	  }

      exit(EXIT_FAILURE);
   }

   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eq && N!=NULL){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }

   return eq;
}

// Manipulation Procedures
// Pre: Not NULL
void clear(List L) {
	if (!L) {
		fprintf(stderr, "Error: Cannot clear null list object.\n");
		// freeList(&L);	// CHECK TO SEE IF FUNCTION CAN FREE NULL LIST
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0) {
		return;
	}

	Node temp = L->front;
	Node next = NULL;
	while(temp) {
		next = temp->next;
		freeNode(&temp);
		temp = next;
	}

	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = -1;

}

// Set the value at cursor to x
// Pre: L is not NULL and  len > 0
void set(List L, ListElement x) {
	if (L && length(L) > 0 && index(L) >= 0) {
		L->cursor->data = x;
	}
}

// Move cursor to front
// Pre: L is not NULL and len > 0
void moveFront(List L) {
	if (L && (length(L) > 0)) {
		L->cursor  = L->front;
		L->index = 0;
	}
}

// Move cursor to back
// L is not NULL and len > 0
void moveBack(List L) {
	if (L && (length(L) > 0)) {
		L->cursor = L->back;
		L->index = length(L) - 1;
	}
}

// Move cursor 1 back
// Pre: L is not NULL and index > 0
void movePrev(List L) {
	if (L && L->cursor && L->index > 0 && L->index <= length(L)-1) {
		L->cursor = L->cursor->prev;
		L->index -= 1;
	}

	else if (L && L->cursor && L->index == 0) {
		L->cursor = NULL;
		L->index = -1;
	}
}

// Move cursor 1 forward
// Pre: L is not NULL and index is not -1
void moveNext(List L) {
	if (L && L->cursor && L->index >= 0 && L->index < length(L)-1) {
		L->cursor = L->cursor->next;
		L->index += 1;
	}

	else if (L && L->cursor && L->index == length(L)-1) {
		L->cursor = NULL;
		L->index = -1;
	}
}

// Add edge cases for when length is only 1
// Pre: L is not NULL and index is not -1
void prepend(List L, ListElement x) {
	if (L && length(L) > 0) {
		Node to_prepend = newNode(x);
		to_prepend->next = L->front;
		L->front->prev = to_prepend;
		L->front = to_prepend;
		L->length += 1;

		if (L->cursor != NULL) {
			L->index += 1;
		}
	}
	else if (L && length(L) == 0) {
		Node to_prepend = newNode(x);
		L->front = L->back = to_prepend;
		L->length += 1;

		// I don't think you need to update cursor index here.
		// List was empty before prepending, so no chance to
		// initialize cursor.
	}
}

// Append x to the list.
// Pre: L is not NULL and len>0
void append(List L, ListElement x) {
	if (L && length(L) > 0) {
		Node to_append = newNode(x);
		to_append->prev = L->back;
		L->back->next = to_append;
		L->back = to_append;
		L->length += 1;

		// if (L->cursor != NULL) {
		// 	L->index += 1;
		// }
		// cursor index should not change if appended.
	}
	else if (L && length(L) == 0) {
		Node to_append = newNode(x);
		L->front = L->back = to_append;
		L->length += 1;
	}
}

// Insert x before the cursor element.
// Pre: L is not NULL and cursor exists
void insertBefore(List L, ListElement x) {
	if (L && L->cursor && length(L) > 0 && index(L) >= 0) {
		if (L->cursor == L->front) {
			prepend(L, x);
		}
		else {
			Node before_node = newNode(x);
			before_node->next = L->cursor;
			L->cursor->prev->next = before_node;
			before_node->prev = L->cursor->prev;
			L->cursor->prev = before_node;
			L->length += 1;
			L->index += 1;
		}
	}
	// cannot insertBefore when list is empty
}

// Insert x after the cursor
// Pre: L is not NULL and cursor exists
void insertAfter(List L, ListElement x) {
	if (L && L->cursor && length(L) > 0 && index(L) >= 0) {
		if (L->cursor == L->back) {
			append(L, x);
		}

		else {
			Node after_node = newNode(x);
			after_node->prev = L->cursor;
			L->cursor->next->prev = after_node;
			after_node->next = L->cursor->next;
			L->cursor->next = after_node;
			L->length += 1;
		}
	}
	// cannot insertAfter when list is empty
}

// Delete the node at the front
// Pre: L is not NULL and len>0
void deleteFront(List  L) {
	if (L && length(L) > 0) {
		bool is_cursor_deleted = false;
		if (L->cursor == L->front) {
			L->cursor = NULL;
			L->index = -1;
			is_cursor_deleted = true;
		}

		if (length(L) == 1) {
			freeNode(&(L->front));
			L->front = L->back = NULL;
		}

		else {
			L->front = L->front->next;
			freeNode(&(L->front->prev));
			L->front->prev = NULL;
			if (!is_cursor_deleted) {
				L->index -= 1;
			}
		}

		L->length -= 1;
	}
}

// Delete Node at the back.
// Pre: L is not NULL and len > 0
void deleteBack(List L) {
	if (L && length(L) > 0) {
		if (L->cursor == L->back) {
			L->cursor = NULL;
			L->index = -1;
		}

		if (length(L) == 1) {
			freeNode(&(L->back));
			L->front = L->back = NULL;
		}

		else {
			L->back = L->back->prev;
			freeNode(&(L->back->next));
			L->back->next = NULL;
		}

		L->length -= 1;
	}
}

// Delete the cursor node
// Pre: L is not NULL, len > 0, index != -1
void delete(List L) {
	if (length(L) > 0 && index(L) >= 0) {
		if (index(L) == 0) {
			deleteFront(L);
		}
		else if (index(L) == length(L) - 1) {
			deleteBack(L);
		}
		else {
			L->cursor->prev->next = L->cursor->next;
			L->cursor->next->prev = L->cursor->prev;
			freeNode(&(L->cursor));
			L->length -= 1;
			L->index = -1;
			L->cursor = NULL;
		}
	}
}

// Other operations
// Print the list to the outfile.
// Pre: L is not NULL
void printList(FILE *out, List L) {
	if (!L) {
		fprintf(stderr, "List Error: calling printList() on a NULL reference.\n");
		exit(EXIT_FAILURE);
	}

	Node temp = NULL;

	for (temp = L->front; temp; temp = temp->next) {
		fprintf(out, "%" PRINT_ELEMENT_LIST " ", temp->data);
	}
	// printf("\n"); // Does not seem to be required. Will add new line in client program itself
}

// Return the copy of a List
// Pre: List is not NULL
List copyList(List L) {
	if (!L) {
		fprintf(stderr, "List Error: calling copyList() on a NULL reference.\n");
		exit(EXIT_FAILURE);
	}

	List list_copy = newList();

	Node temp = NULL;

	for (temp = L->front; temp; temp = temp->next) {
		append(list_copy, temp->data);
	}

	return list_copy;
}

// Concatenate List B to List A and return combined List
// Pre: A and B are not NULL
List concatList(List A, List B) {
	if (!A || !B) {
		fprintf(stderr, "List Error: calling concatList() on a NULL reference.\n");
		exit(EXIT_FAILURE);
	}
	List cat_list = newList();

	Node temp = NULL;

	for (temp = A->front; temp; temp = temp->next) {
		append(cat_list, temp->data);
	}

	for (temp = B->front; temp; temp = temp->next) {
		append(cat_list, temp->data);
	}

	return cat_list;

}

// Check 1