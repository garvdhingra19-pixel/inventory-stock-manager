#include "inventory_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void initList(InventoryList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->nextSeq = 1;
    list->count = 0;
}

void freeList(InventoryList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* nextNode = current->next;
        free(current);
        current = nextNode;
    }
    initList(list);
}

void insertAtTail(InventoryList* list, int productId, const char* name, int quantity, double price, Date expiry) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Error: Memory allocation failed!\n");
        return;
    }
    
    newNode->productId = productId;
    strncpy(newNode->name, name, 49);
    newNode->name[49] = '\0';
    newNode->quantity = quantity;
    newNode->price = price;
    newNode->expiry = expiry;
    newNode->receivedSeq = list->nextSeq++;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->count++;
    printf("[Success] Batch added with Sequence ID #%d\n", newNode->receivedSeq);
}

void displayList(const InventoryList* list) {
    if (list->head == NULL) {
        printf("\nInventory is currently empty.\n");
        return;
    }

    printf("\n=========================================================================\n");
    printf("%-6s %-8s %-15s %-10s %-10s %-12s\n", "Seq", "ID", "Name", "Qty", "Price", "Expiry");
    printf("=========================================================================\n");

    Node* current = list->head;
    while (current != NULL) {
        printf("%-6d %-8d %-15s %-10d $%-9.2f ", 
               current->receivedSeq, current->productId, current->name, 
               current->quantity, current->price);
        printDate(current->expiry);
        printf("\n");
        current = current->next;
    }
    printf("=========================================================================\n");
}

// Helper for case-insensitive partial string matching
int caseInsensitiveMatch(const char* haystack, const char* needle) {
    char h[100], n[100];
    int i;
    for(i = 0; haystack[i] && i < 99; i++) h[i] = tolower(haystack[i]);
    h[i] = '\0';
    for(i = 0; needle[i] && i < 99; i++) n[i] = tolower(needle[i]);
    n[i] = '\0';
    return strstr(h, n) != NULL;
}

void searchById(const InventoryList* list, int id) {
    Node* current = list->head;
    int found = 0;
    
    printf("\n--- Search Results for ID: %d ---\n", id);
    while (current != NULL) {
        if (current->productId == id) {
            if (!found) {
                printf("%-6s %-8s %-15s %-10s %-10s %-12s\n", "Seq", "ID", "Name", "Qty", "Price", "Expiry");
            }
            printf("%-6d %-8d %-15s %-10d $%-9.2f ", 
                   current->receivedSeq, current->productId, current->name, 
                   current->quantity, current->price);
            printDate(current->expiry);
            printf("\n");
            found = 1;
        }
        current = current->next;
    }
    if (!found) printf("No batches found with ID %d.\n", id);
}

void searchByName(const InventoryList* list, const char* name) {
    Node* current = list->head;
    int found = 0;
    
    printf("\n--- Search Results for Name: %s ---\n", name);
    while (current != NULL) {
        if (caseInsensitiveMatch(current->name, name)) {
            if (!found) {
                printf("%-6s %-8s %-15s %-10s %-10s %-12s\n", "Seq", "ID", "Name", "Qty", "Price", "Expiry");
            }
            printf("%-6d %-8d %-15s %-10d $%-9.2f ", 
                   current->receivedSeq, current->productId, current->name, 
                   current->quantity, current->price);
            printDate(current->expiry);
            printf("\n");
            found = 1;
        }
        current = current->next;
    }
    if (!found) printf("No batches found matching '%s'.\n", name);
}

// --- Phase 3: Sorting (Merge Sort) ---

// Split the list into two halves
void frontBackSplit(Node* source, Node** frontRef, Node** backRef) {
    Node* fast;
    Node* slow;
    slow = source;
    fast = source->next;
    
    // Advance 'fast' two nodes, and advance 'slow' one node
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

// Merge two sorted linked lists
Node* sortedMerge(Node* a, Node* b, CompareFunc cmp, int ascending) {
    Node* result = NULL;
    
    if (a == NULL) return b;
    else if (b == NULL) return a;
    
    // Use the function pointer 'cmp' to decide order
    if (cmp(a, b, ascending) <= 0) {
        result = a;
        result->next = sortedMerge(a->next, b, cmp, ascending);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next, cmp, ascending);
    }
    return result;
}

// The core recursive merge sort
void mergeSort(Node** headRef, CompareFunc cmp, int ascending) {
    Node* head = *headRef;
    Node* a;
    Node* b;
    
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
    
    frontBackSplit(head, &a, &b);
    
    mergeSort(&a, cmp, ascending);
    mergeSort(&b, cmp, ascending);
    
    *headRef = sortedMerge(a, b, cmp, ascending);
}

// Wrapper function to initiate sort and fix the tail pointer afterward
void sortList(InventoryList* list, CompareFunc cmp, int ascending) {
    if (list->head == NULL) return;
    
    mergeSort(&(list->head), cmp, ascending);
    
    // Fix the tail pointer since nodes have moved
    Node* current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    list->tail = current;
    
    printf("\n[Success] Inventory sorted successfully.\n");
}

// Comparators
int compareByPrice(Node* a, Node* b, int ascending) {
    if (a->price == b->price) return 0;
    if (ascending) return (a->price < b->price) ? -1 : 1;
    else return (a->price > b->price) ? -1 : 1;
}

int compareByQuantity(Node* a, Node* b, int ascending) {
    if (a->quantity == b->quantity) return 0;
    if (ascending) return (a->quantity < b->quantity) ? -1 : 1;
    else return (a->quantity > b->quantity) ? -1 : 1;
}

int compareByExpiry(Node* a, Node* b, int ascending) {
    int res = compareDates(a->expiry, b->expiry);
    return ascending ? res : -res;
}