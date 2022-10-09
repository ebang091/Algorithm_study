#include "./binarySearchTree.h"
#include <string.h>
#include <stdlib.h>
BST* createBST() // 이진탐색트리 생성 -> 멤버 변수 초기화 목적 : root 도 초기화 (NULL로 하거나 외부노드로 확장-> 같은원리로동작가능)
{
    BST *newTree = (BST *)malloc(sizeof(BST));
    newTree->root = (Node *)malloc(sizeof(Node)); //root 초기화 , 새로운 변수 사용없이!
    newTree->root->lChild = NULL;
    newTree->root->rChild = NULL;
    newTree->root->parent = NULL;
    return (newTree);
}
/*
                    o = data
         o = data(l)          o = data(r)
    o = (ll) o(lr)      o(rl)   o(rr)
o = dump
o o null
*/
void    deleteBST(BST* tree) // 이진탐색트리 제거
{
    if (isExternal(tree->root))
    {
        free(tree->root);
        return ;
    }
    Node    *ptr;
    Node    *pptr;
    ptr = tree->root;
    while (!isExternal(ptr))
    {
        pptr = ptr;
        ptr = ptr->lChild;
    }
    reduceExternal(pptr); //외부노드를 삭제.
}
/*
GetLeftSubtree대신 포인터 접근 : 없으면 외부노드 반환
if (isExternal(node->lChild))
    return;
~~~환
   o = data
 o = NULL    o = NULL
        o = dump
    o = NULL   o =NULL
            o = data
    o = dump        o = dump
 o null  o  null  o null  o null
*/
Node* treeSearch(Node* node, int key) // key 값의 노드 위치 반환 (재귀)  -> 없으면 위치했어야 하는 노드 위치 반환
//insert를 위해서 있는 함수... findElement....
{
    //if(node == 0)   //NULL까지 도달하면 접근이 힘들다...
    //isExternal(node)....
    if (isExternal(node))
        return node->parent;
    if (node->key == key)
        return node;
    else if(node->key > key)
        return (treeSearch(node->lChild, key));
    else
        return (treeSearch(node->rChild, key));
}
   /***************************** **************************************************
       o = 외부노드 = data X                o = data
 o=NULL  o=NULL [malloc도 안되어있음.]   o = 외부노드 o = 외부노드
*************************************************************************************/
void    expandExternal(Node* node) // 노드의 자식노드로 외부노드 확장 (외부노드->내부노드)
{
    node->lChild = (Node *)malloc(sizeof(Node));
    node->rChild = (Node *)malloc(sizeof(Node));
    node->lChild->key = NULL;
    node->lChild->lChild = NULL;
    node->lChild->rChild = NULL;
    node->lChild->parent= NULL;
    node->lChild->key = NULL;
    node->rChild->lChild = NULL;
    node->rChild->rChild = NULL;
    node->rChild->parent= NULL;
}
void    insertItem(BST* tree, int key) // 삽입
{
    if(isExternal(tree->root))
    {
        tree -> root->key = key;
        expandExternal(tree->root);
    }
    Node *pnode = treeSearch(tree, key);
    //못 찾는 게 정상 -> 외부노드를 반환했을 것..
    //중복 확인
    /*if(!isExternal(newnode->lChild) || !isExternal(newnode->rChild))
        return ;
    */
/*
        o = parent ; -> 반환
        o  = dump
    o = null  o = null
----------------------------------
        o = data
o = lchild      o = rChild
*/
    if(pnode->key > key)//대소비교로 찾는 node의 위치 확인 가능하다.
    {
        pnode->lChild->key = key;
        expandExternal(pnode->lChild);
    }
    else{
            pnode->rChild->key = key;
            expandExternal(pnode->rChild);
    }
}
int removeElement(BST* tree, int key) // 제거
{
    if (isExternal(tree->root))
        return (NO_SUCH_KEY);
    Node    *rnode = treeSearch(tree, key);//제거할 노드.
    Node    *replace = rnode->rChild;
    int rdata = rnode->key; //사실상 key가 아니라 data
//  Node * ptr = tree->root;
    if ()
}
int findElement(BST* tree, int key) // 탐색
{
    if (isExternal(tree->root)) //treeSearch에서 null이 반환되는 것을 방지.
        return NO_SUCH_KEY;
    Node * find= treeSearch(tree, key);
    if(find->key == key)
        return (find->key);
    else
        return (NO_SUCH_KEY);
}
/*
    o = data(parent)
    o = dump (lchild = external node)
o = null  o = null
*/
void reduceExternal(Node* node) // 노드의 자식노드인 외부노드 제거 (내부노드->외부노드)
//본인 노드가 외부노드가 되려고?
{
    Node *dnode;
    if (isExternal(node->lChild))
    {
        dnode = node->lChild;
        free(dnode->lChild);
        free(dnode->rChild);
        dnode->lChild = NULL;
        dnode->rChild = NULL;
        free(dnode);
        node->lChild = NULL;
    }
    if (isExternal(node->rChild))
    {
        dnode = node->rChild;
        free(dnode->lChild);
        free(dnode->rChild);
        dnode->lChild = NULL;
        dnode->rChild = NULL;
        free(dnode);
        node->rChild = NULL;
    }
}
int isExternal(Node* node) // 노드의 외부노드 여부 반환
{
    return (node->lChild == NULL && node->rChild == NULL);
}
