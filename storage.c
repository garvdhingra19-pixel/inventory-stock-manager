#include "storage.h"
#include <stdio.h>
#include <stdlib.h>

void saveToFile(const InventoryList* list, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Could not open %s for writing.\n", filename);
        return;
    }
    
    Node* current = list->head;
    while (current != NULL) {
        // Format: ID,Name,Quantity,Price,Day,Month,Year
        fprintf(file, "%d,%s,%d,%.2f,%d,%d,%d\n",
            current->productId, current->name, current->quantity,
            current->price, current->expiry.day, current->expiry.month, current->expiry.year);
        current = current->next;
    }
    
    fclose(file);
    printf("[Success] Inventory saved to %s\n", filename);
}

void loadFromFile(InventoryList* list, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("No existing data file found. Starting with empty inventory.\n");
        return;
    }
    
    int id, qty, day, month, year;
    char name[50];
    double price;

    // Parse the CSV format until End Of File
    while (fscanf(file, "%d,%49[^,],%d,%lf,%d,%d,%d\n", &id, name, &qty, &price, &day, &month, &year) == 7) {
        Date exp = {day, month, year};
        insertAtTail(list, id, name, qty, price, exp);
    }
    
    fclose(file);
    printf("[Success] Inventory loaded from %s\n", filename);
}
