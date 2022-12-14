#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 *  중복 키가 없는 이진트리.
 *  메쏘드:
 *  i : key 입력 받은 후 트리에 삽입
 *  d : key 입력 받은 후 해당 노드가 있다면 노드 삭제, 삭제한 키 출력. 없으면 X 출력
 *  s : key 입력 받은 후 해당 노드가 있다면 키를 출력, 없으면 X 출력
 *  p : 트리를 전위 순회로 인쇄.
 *  q : 종료
 *
 */
#define TRUE 1
#define FALSE 0
#define NO_SUCH_KEY -1

struct node_
{
    int key;
    struct node_ *lchild;
    struct node_ *rchild;
    struct node_ *parent;
};
typedef struct node_ node;

struct tree_ {
    node *root;
};
typedef struct tree_ Tree;

/* 메쏘드 구현
 * [public]
 * findElement(k) : key를 받아서 해당 노드를 찾아 원소를 반환(여기서 원소 = 키)
 * insertItem(k) :  key를 받아서 트리에 해당 키를 가진 노드를 삽입.
 *      treesearch , setnode , expandExternal(left), expandExternal(right).
 * treeSearch(w, k) :  (노드, 키) 트리에서 원하는 키를 가진 노드를 반환하되 없어도 위치할 위치의 외부노드를 반환.
 * removeElement(k) : 키를 입력받아서 해당 위치의 노드를 삭제하고, 원소를 반환 (여기서 원소 = 키)
 *     treeSearch, left right 둘 중 하나라도 외부노드이면 reduce External, 둘다 내부노드이면 inOrderSucc(w), leftchild에 대해 reduceExternal()
 * isExternal(w) :  노드가 외부노드인지 내부노드인지 반환.
 * inOrderSucc(w) : w노드의 중위순위 후계자를 반환(중위순회시 루트 이후에 가장 먼저 방문할 노드. 오른쪽 부트리중 가장 왼쪽 말단의 내부노드)

 * [private]
 *  init_tree : tree 초기화.
 *  expandExternal : 해당 노드를 외부노드로 확장.   부모 설정도 해줘야 함.
 *  leftchild, rightchild(w) : 해당노드의 왼쪽, 오른쪽 자식을 반환
 *  reduceExternal(w)
 *       외부노드인 w를 입력받고 parent를 삭제하되, w의 자식은 grand와 이어주고 나서 삭제한다. (w도 삭제)!
 *  Sibling(w):
 *      w의 형제노드를 반환한다. (외부노드이든 내부노드이든)
 *
 */
void ft_handle_error(char *str)
{
    printf("%s", str );
    exit(1);
}

node *leftChild(node *w)
{
    return w->lchild;
}

node *rightChild(node *w )
{
    return w->rchild;
}

int isExternal(node *w)
{
    if (w->lchild == NULL && w->rchild == NULL)
        return TRUE;
    else
        return FALSE;
}

node *treeSearch(node *w, int key)
{
    if (isExternal(w))
        return w;
    if(w->key == key)
        return w;
    else if(key > w->key)
        return treeSearch(rightChild(w), key);
    else
        return treeSearch(leftChild(w), key);
}
node *get_sibling(node *w)
{
    node *p = w->parent;
    node *ws;
    if (p == NULL)//root이면
        return NULL;//형제가 없다
    if(leftChild(p) == w)
        return rightChild(p);
    else if(rightChild(p) == w)
        return leftChild(p);
    else
        return NULL;
}

node  *reduceExternal(node *w)
{
    node *p  = w->parent;
    node *sibling = get_sibling(w);
    if(p->parent == NULL)//루트라면
    {
        *p = *sibling;
        p->parent = NULL;
    }
    else {
        node *g = p->parent;
        sibling->parent = g;
        if (leftChild(g) == p)
            g->lchild = sibling;
        else if (rightChild(g) == p)
        g->rchild = sibling;
        free(p);
    }
    free(w);

    return sibling;
}

void expandExternal(node *w)
{
    w->lchild = (node *)malloc(sizeof(node));
    if(!w->lchild)
        ft_handle_error("malloc failed.\n");
    w->lchild->lchild = NULL;
    w->lchild->rchild = NULL;
    w->lchild->parent = w;
    w->rchild = (node *)malloc(sizeof(node));
    if(!w->rchild)
        ft_handle_error("malloc failed.\n");
    w->rchild->lchild = NULL;
    w->rchild->rchild = NULL;
    w->rchild->parent = w;
}

void setnode(node *w, int key)
{
    w->key = key;
}

int insertItem(Tree *tree, int key)
{
    node *w = treeSearch(tree->root, key);
    if (!isExternal(w))
       return 0;
    setnode(w, key);
    expandExternal(w);

    return 1;

}

node *inOrderSucc(node *w)
{
    if (isExternal((w)) || isExternal(w->rchild)|| !w)
        ft_handle_error("wrong node input ");
    node *find = w->rchild;
    node *save = find;
    while(!isExternal((find)))
    {
        save = find;
        find = find->lchild;
    }
    return save;

}
int findElement(Tree *tree, int key)
{
    node *w = treeSearch(tree->root, key);
    if (isExternal(w)) {
        return NO_SUCH_KEY;
    }
    else
        return w->key;
}


int removeElement(Tree *tree, int key) {
    node *w = treeSearch(tree->root, key);
    node *z;
    int element;

    if (isExternal(w))
        return NO_SUCH_KEY;
    element = w->key;
    node *v = leftChild(w);
    if(!isExternal(v))
        v = rightChild((w));
    if(isExternal(v))
        reduceExternal(v);
    else
    {
        v = inOrderSucc((w));
        z = leftChild(v);
        setnode(w, v->key);
        reduceExternal(leftChild(v));
    }
    return element;
}

void print_tree(node *w)
{
    if (isExternal(w))
        return ;
    printf("%d ", w->key);
    print_tree(leftChild(w));
    print_tree(rightChild(w));
}

void init_tree(Tree **tree)
{
    *tree = (Tree *)malloc(sizeof(tree));
    (*tree)->root = (node *)malloc(sizeof(node));
    (*tree)->root->parent = NULL;
}

void free_node(node * w)
{
    if(isExternal(w))
        free(w);
    free_node(leftChild(w));
    free_node(rightChild(w));

}
void ft_free(Tree *tree)
{
    free_node(tree->root);
    free(tree);
}

int main()
{
    Tree *tree;
    int key, result;
    char menu;
    node *n;

    init_tree(&tree);
    while(1)
    {
        scanf("%c", &menu);

        switch(menu)
        {
            case 'i' :
                scanf("%d", &key);
                if (!insertItem(tree, key))
                    ft_handle_error("insert failed.\n");

                break;
            case 'd':
                scanf("%d", &key);
                if((result = removeElement(tree, key)) != NO_SUCH_KEY)
                    printf("%d\n", result);
                else
                    printf("X\n");
                break;
            case 's':
                scanf("%d", &key);
                if(!isExternal( n= treeSearch(tree->root, key)))
                   printf("%d\n", n->key);//노드의 데이터 출력
                else
                    printf("X\n");
                break;
            case 'p':
                print_tree(tree->root);
                printf("\n");
                break;
            case 'q':
                //ft_free(tree);
                return 0;

        }
    }
}
