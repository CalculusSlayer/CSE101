// -----------------------------------------------------------------------------
//  Nayeel Imtiaz, naimtiaz
//  2022 Spring CSE101 PA4
//  List.h
//  This file contains the function prototypes for the
//  List ADT.
// -----------------------------------------------------------------------------
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// #define PRINT_ELEMENT_LIST "i"    // Change this to change format specifier.
typedef void* ListElement; // Change this to change the type of List.

// Exported type
typedef struct ListObj *List; // Pointer to list object

// Constructors/Destructors
List newList (void); // Creates a new list.
void freeList(List *pL); // Frees a list.

// Access Functions
int length(List L); // Get length of list
int index(List L); // Get index of cursor
ListElement front(List L); // Get front of list
ListElement back(List L); // Get back of list
ListElement get(List L); // Get value at cursor
// bool equals(List A, List B); // Check if List A equals List B

// Manipulation Procedures
void clear(List L); // Clear the list
void set(List L, ListElement x); // Set the cursor value to x
void moveFront(List L); // Move cursor to front
void moveBack(List L); // Move cursor to back
void movePrev(List L); // Move cursor one back
void moveNext(List L); // Move cursor one forward
void prepend(List L, ListElement x); // Add element to the beginning
void append(List L, ListElement x); // Add element to the end
void insertBefore(List L, ListElement x); // Insert element before cursor
void insertAfter(List L, ListElement x); // Insert element after cursor
void deleteFront(List  L); // Delete the front node.
void deleteBack(List L); // Delete the back node.
void delete(List L); // Delete the cursor node.

// Other operations
// void printList(FILE *out, List L); // Print the list
// List copyList(List L); // Copies input list and returns it.
// List concatList(List A, List B); // Concantenates List B to List A and returns result.

// Check List.h