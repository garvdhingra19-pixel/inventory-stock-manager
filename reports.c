#include "reports.h"
#include <stdio.h>

void reportLowStock(const InventoryList* list, int threshold) {
    printf("\n--- Low Stock Report (Threshold: %d) ---\n", threshold);
    if (list->head == NULL) {
        printf("Inventory is empty.\n");
        return;
    }

    int checkedIds[1000]; 
    int checkedCount = 0;
    int foundAny = 0;

    Node* current = list->head;
    while (current != NULL) {
        int id = current->productId;
        
        // Skip if we already calculated the total for this product ID
        int alreadyChecked = 0;
        for (int i = 0; i < checkedCount; i++) {
            if (checkedIds[i] == id) {
                alreadyChecked = 1;
                break;
            }
        }

        if (!alreadyChecked) {
            checkedIds[checkedCount++] = id;
            
            // Sum up the quantities across ALL batches of this product
            int totalQty = 0;
            Node* scanner = current;
            while (scanner != NULL) {
                if (scanner->productId == id) {
                    totalQty += scanner->quantity;
                }
                scanner = scanner->next;
            }

            if (totalQty < threshold) {
                if (!foundAny) {
                    printf("%-8s %-15s %-10s\n", "ID", "Name", "Total Qty");
                    printf("----------------------------------------\n");
                }
                printf("%-8d %-15s %-10d\n", id, current->name, totalQty);
                foundAny = 1;
            }
        }
        current = current->next;
    }
    if (!foundAny) printf("No products are below the low stock threshold.\n");
}

void reportExpiring(const InventoryList* list, Date today, int daysThreshold) {
    printf("\n--- Expiry Report (Threshold: %d days) ---\n", daysThreshold);
    if (list->head == NULL) {
        printf("Inventory is empty.\n");
        return;
    }

    Node* current = list->head;
    int foundAny = 0;

    while (current != NULL) {
        int daysLeft = daysBetween(today, current->expiry);
        
        if (daysLeft <= daysThreshold) {
            if (!foundAny) {
                printf("%-6s %-8s %-15s %-12s %-20s\n", "Seq", "ID", "Name", "Expiry Date", "Status");
                printf("------------------------------------------------------------------\n");
            }
            
            printf("%-6d %-8d %-15s ", current->receivedSeq, current->productId, current->name);
            printDate(current->expiry);

            if (daysLeft < 0) {
                printf("   [EXPIRED by %d days]\n", -daysLeft);
            } else {
                printf("   [Expiring in %d days]\n", daysLeft);
            }
            foundAny = 1;
        }
        current = current->next;
    }
    if (!foundAny) printf("No batches are expired or expiring within %d days.\n", daysThreshold);
}