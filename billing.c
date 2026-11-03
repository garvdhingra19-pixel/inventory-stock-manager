#include "billing.h"
#include "queue.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

// Helper to remove batches whose quantity has reached 0
void cleanEmptyBatches(InventoryList* list) {
    Node* current = list->head;
    Node* prev = NULL;
    while (current != NULL) {
        if (current->quantity <= 0) {
            if (prev == NULL) list->head = current->next;
            else prev->next = current->next;
            
            if (current == list->tail) list->tail = prev;
            
            Node* temp = current;
            current = current->next;
            free(temp);
            list->count--;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

// Comparator to sort batch pointers by received sequence
int cmpSeq(const void* a, const void* b) {
    Node* n1 = *(Node**)a;
    Node* n2 = *(Node**)b;
    return n1->receivedSeq - n2->receivedSeq;
}

void processSale(InventoryList* list, int productId, int saleQty, int isFifo, Date today) {
    Node* arr[1000];
    int count = 0;
    int totalAvailable = 0;

    // 1. Collect valid, unexpired batches for this product ID
    Node* current = list->head;
    while (current != NULL) {
        if (current->productId == productId && current->quantity > 0) {
            if (daysBetween(today, current->expiry) >= 0) { 
                arr[count++] = current;
                totalAvailable += current->quantity;
            }
        }
        current = current->next;
    }

    if (count == 0 || totalAvailable == 0) {
        printf("No valid/unexpired stock available for ID %d.\n", productId);
        return;
    }

    if (saleQty > totalAvailable) {
        printf("Error: Cannot sell %d units. Only %d valid units available.\n", saleQty, totalAvailable);
        return;
    }

    // 2. Sort collected batches by receivedSeq ascending
    qsort(arr, count, sizeof(Node*), cmpSeq);

    // 3. Load into Stack or Queue
    Queue q; initQueue(&q);
    Stack s; initStack(&s);

    for (int i = 0; i < count; i++) {
        if (isFifo) enqueue(&q, arr[i]);
        else push(&s, arr[i]);
    }

    // 4. Process the sale
    int remaining = saleQty;
    double totalPrice = 0.0;
    
    printf("\n--- Bill (ID: %d | Mode: %s) ---\n", productId, isFifo ? "FIFO" : "LIFO");
    printf("%-10s %-10s %-12s %-12s\n", "Seq", "Qty Taken", "Unit Price", "Line Total");
    printf("-------------------------------------------------\n");

    while (remaining > 0) {
        Node* batch = isFifo ? dequeue(&q) : pop(&s);
        if (batch == NULL) break;

        int take = (remaining < batch->quantity) ? remaining : batch->quantity;
        batch->quantity -= take;
        remaining -= take;
        double lineTotal = take * batch->price;
        totalPrice += lineTotal;

        printf("%-10d %-10d $%-11.2f $%-11.2f\n", batch->receivedSeq, take, batch->price, lineTotal);
    }

    printf("-------------------------------------------------\n");
    printf("Total Items: %d | Total Price: $%.2f\n", saleQty, totalPrice);

    // 5. Cleanup nodes that reached 0
    cleanEmptyBatches(list);
}