#ifndef STORAGE_H
#define STORAGE_H

#include "inventory_list.h"

void saveToFile(const InventoryList* list, const char* filename);
void loadFromFile(InventoryList* list, const char* filename);

#endif
