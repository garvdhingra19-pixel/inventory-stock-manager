#ifndef NODE_H
#define NODE_H

#include "date.h"

typedef struct Node {
    int productId;
    char name[50];
    int quantity;
    double price;
    Date expiry;
    int receivedSeq;   
    struct Node* next;
} Node;

#endif