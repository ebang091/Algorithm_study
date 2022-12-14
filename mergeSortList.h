#ifndef MERGESORTLIST_H
#define MERGESORTLIST_H
#include <string.h>
typedef struct _node
{
    int data;
    struct _node *next;
} node;

node *newnode(int data);
node *LInit();
void listadd_last(node *head, node *node);
void mergeSortList(node **head, int size);

int listsize(node *head);
node *listfind(node *head, int index);
node *listcut_half(node **head);
void rmergeSortList(node **head, int size);

void Lprint(node *head);
void mergeList(node **head1, node **head2);
#endif
