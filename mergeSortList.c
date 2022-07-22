#include "./mergeSortList.h"

node *newnode(int data)
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->data = data;
    newnode->next = 0;
}

node *LInit()
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->next = 0;
    return (newnode);
}
// head는 더미 노드
void listadd_last(node *head, node *newnode)
{
    if (!head)
        return;
    node *ptr = head;
    while (ptr->next != 0)
        ptr = ptr->next;
    ptr->next = newnode;
}

void mergeSortList(node **head, int size)
{
    rmergeSortList(*head, size);
    Lprint(*head);
}

void Lprint(node *head)
{
    if (!head)
        return;
    node *ptr = head->next;

    while (ptr != 0)
    {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
}

int listsize(node *head)
{
    int i;

    i = 0;
    node *ptr = head;
    while (ptr->next != 0)
    {
        ptr = ptr->next;
        i++;
    }
    return (i);
}
//
node *listfind(node *head, int index)
{
    int i;
    node *ptr = head;

    i = -1;
    if (ptr == 0)
        return 0;
    while (ptr != 0 && i != index)
    {
        ptr = ptr->next;
        i++;
    }
    if (i == index)
        return (ptr);
    else
        return 0;
}

node *listcut_half(node **head)
{
    node *ptr;
    node *save;
    if (!head)
        return 0;
    int size = listsize(*head);
    ptr = listfind(*head, (size - 1) / 2);
    save = ptr->next;
    ptr->next = 0;
    //   printf("\nnext start is %d", save->data);
    node *newnode = LInit();
    newnode->next = save;
    return (newnode);
}

void rmergeSortList(node **head, int size)
{

    if (size == 1)
        return;
    node *head1 = *head;
    node *head2 = listcut_half((head));
    if (!head2)
    {
        printf("head2 is null");
        return;
    }
    rmergeSortList(&head1, size / 2);
    rmergeSortList(&head2, size / 2);
    mergeList(&head1, &head2);
}

void mergeList(node **head1, node **head2)
{
    node *ret = LInit();
    node *h1 = *head1;
    node *h2 = *head2;

    while (h1 != 0 && h2 != 0)
    {
        if (h1->data < h2->data)
        {
            listadd_last(ret, newnode(h1->data));
            h1 = h1->next;
        }
        else
        {
            listadd_last(ret, newnode(h2->data));
            h2 = h2->next;
        }
    }
    free(*head2);
    *head1 = ret;
    free(ret);
}

// int main()
// {
//     node *head = LInit();

//     node *half;
//     for (int i = 0; i < 8; i++)
//         listadd_last(head, newnode(i));
//     printf("\nsize = %d\n", listsize(head));
//     printf("%d\n", listfind(head, 3)->data);
//     Lprint(head);
//     printf("\n\n\n");
//     half = listcut_half(&head);
//     if (!half)
//         return;
//     Lprint(head);
//     printf("\n");
//     Lprint(half);
//     printf("\n");
// }
