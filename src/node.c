#include "node.h"

void create_node(struct Node* node, int value, struct Node* next){
    node->m_Value = value;
    node->m_Next = next;
}