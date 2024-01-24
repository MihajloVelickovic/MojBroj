#ifndef NODE_H
#define NODE_H

struct Node{
    int m_Value;
    struct Node* m_Next;
};

void create_node(struct Node* node, int value, struct Node* next);

#endif