#ifndef BILLING_H
#define BILLING_H

#include "inventory_list.h"
#include "date.h"

void processSale(InventoryList* list, int productId, int saleQty, int isFifo, Date today);

#endif