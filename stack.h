#ifndef STACK_H
#define STACK_H

#include "node.h"
#include <stdlib.h>

typedef struct SNode {
    Node* batch;
    struct SNode* next;
} SNode;

typedef struct {
    SNode* top;
} Stack;

static inline void initStack(Stack* s) {
    s->top = NULL;
}

static inline void push(Stack* s, Node* b) {
    SNode* temp = (SNode*)malloc(sizeof(SNode));
    temp->batch = b;
    temp->next = s->top;
    s->top = temp;
}

static inline Node* pop(Stack* s) {
    if (s->top == NULL) return NULL;
    SNode* temp = s->top;
    Node* b = temp->batch;
    s->top = s->top->next;
    free(temp);
    return b;
}

#endif