#ifndef INVENTORY_LIST_H
#define INVENTORY_LIST_H

#include "node.h"

// Struct to manage the list state without global variables
typedef struct {
    Node* head;
    Node* tail;
    int nextSeq;
    int count;
} InventoryList;

void initList(InventoryList* list);
void freeList(InventoryList* list);
void insertAtTail(InventoryList* list, int productId, const char* name, int quantity, double price, Date expiry);
void displayList(const InventoryList* list);

void searchById(const InventoryList* list, int id);
void searchByName(const InventoryList* list, const char* name);
// Function pointer type for our comparators
typedef int (*CompareFunc)(Node* a, Node* b, int ascending);

// Comparator functions
int compareByPrice(Node* a, Node* b, int ascending);
int compareByQuantity(Node* a, Node* b, int ascending);
int compareByExpiry(Node* a, Node* b, int ascending);

// Sorting wrapper
void sortList(InventoryList* list, CompareFunc cmp, int ascending);

#endif