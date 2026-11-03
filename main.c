#include <stdio.h>
#include "inventory_list.h"
#include "reports.h"
#include "billing.h"
#include "storage.h"

void showMenu() {
    printf("\n--- INVENTORY & STOCK MANAGER (Phase 6) ---\n");
    printf("1. Add New Batch\n");
    printf("2. Display Inventory Batches\n");
    printf("3. Search by Product ID\n");
    printf("4. Search by Product Name\n");
    printf("5. Sort Inventory\n");
    printf("6. Low Stock Report\n");
    printf("7. Expiry Report\n");
    printf("8. Process Sale (FIFO/LIFO)\n");
    printf("9. Save and Exit\n");
    printf("Enter your choice: ");
}

void sortMenu(InventoryList* inventory) {
    int attrChoice, orderChoice;
    CompareFunc cmp = NULL;
    
    printf("\nSort by:\n1. Price\n2. Quantity\n3. Expiry Date\nChoose attribute: ");
    if (scanf("%d", &attrChoice) != 1) { 
        while (getchar() != '\n'); 
        return; 
    }
    
    printf("Order:\n1. Ascending\n2. Descending\nChoose order: ");
    if (scanf("%d", &orderChoice) != 1) { 
        while (getchar() != '\n'); 
        return; 
    }
    
    int ascending = (orderChoice == 1) ? 1 : 0;
    
    switch (attrChoice) {
        case 1: cmp = compareByPrice; break;
        case 2: cmp = compareByQuantity; break;
        case 3: cmp = compareByExpiry; break;
        default: printf("Invalid attribute.\n"); return;
    }
    
    sortList(inventory, cmp, ascending);
    displayList(inventory);
}

int main() {
    InventoryList inventory;
    initList(&inventory);
    
    const char* dbFile = "inventory_data.csv";
    
    // Automatically load existing data on startup
    printf("\nInitializing System...\n");
    loadFromFile(&inventory, dbFile);
    
    int choice;

    do {
        showMenu();
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1: {
                int id, qty;
                char name[50];
                double price;
                Date exp;

                printf("Enter Product ID: ");
                scanf("%d", &id);
                printf("Enter Product Name (no spaces): ");
                scanf("%49s", name);
                printf("Enter Quantity: ");
                scanf("%d", &qty);
                printf("Enter Unit Price: ");
                scanf("%lf", &price);
                printf("Enter Expiry Date (DD MM YYYY): ");
                scanf("%d %d %d", &exp.day, &exp.month, &exp.year);

                insertAtTail(&inventory, id, name, qty, price, exp);
                break;
            }
            case 2:
                displayList(&inventory);
                break;
            case 3: {
                int id;
                printf("Enter Product ID to search: ");
                scanf("%d", &id);
                searchById(&inventory, id);
                break;
            }
            case 4: {
                char name[50];
                printf("Enter Product Name to search: ");
                scanf("%49s", name);
                searchByName(&inventory, name);
                break;
            }
            case 5:
                sortMenu(&inventory);
                break;
            case 6: {
                int threshold;
                printf("Enter low stock threshold quantity: ");
                scanf("%d", &threshold);
                reportLowStock(&inventory, threshold);
                break;
            }
            case 7: {
                Date today;
                int daysThreshold;
                printf("Enter today's date for testing (DD MM YYYY): ");
                scanf("%d %d %d", &today.day, &today.month, &today.year);
                printf("Enter days until expiry threshold: ");
                scanf("%d", &daysThreshold);
                reportExpiring(&inventory, today, daysThreshold);
                break;
            }
            case 8: {
                int id, qty, isFifo;
                Date today;
                
                printf("Enter Product ID to sell: ");
                scanf("%d", &id);
                printf("Enter Quantity to sell: ");
                scanf("%d", &qty);
                printf("Billing Mode (1 for FIFO, 0 for LIFO): ");
                scanf("%d", &isFifo);
                printf("Enter today's date (DD MM YYYY): ");
                scanf("%d %d %d", &today.day, &today.month, &today.year);
                
                processSale(&inventory, id, qty, isFifo, today);
                break;
            }
            case 9:
                printf("\nSaving session...\n");
                saveToFile(&inventory, dbFile);
                printf("Cleaning up memory... Exiting.\n");
                freeList(&inventory);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 9);

    return 0;
}