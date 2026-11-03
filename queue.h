#ifndef QUEUE_H
#define QUEUE_H

#include "node.h"
#include <stdlib.h>

typedef struct QNode {
    Node* batch;
    struct QNode* next;
} QNode;

typedef struct {
    QNode *front, *rear;
} Queue;

static inline void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

static inline void enqueue(Queue* q, Node* b) {
    QNode* temp = (QNode*)malloc(sizeof(QNode));
    temp->batch = b; 
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

static inline Node* dequeue(Queue* q) {
    if (q->front == NULL) return NULL;
    QNode* temp = q->front;
    Node* b = temp->batch;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return b;
}

#endif