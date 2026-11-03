#ifndef REPORTS_H
#define REPORTS_H

#include "inventory_list.h"
#include "date.h"

void reportLowStock(const InventoryList* list, int threshold);
void reportExpiring(const InventoryList* list, Date today, int daysThreshold);

#endif