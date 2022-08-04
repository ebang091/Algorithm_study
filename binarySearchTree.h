#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NO_SUCH_KEY -1

typedef struct _Node {
   struct _Node* parent;
   struct _Node* lChild;
   struct _Node* rChild;
   int key;
} Node;

typedef struct _BST {
   Node* root;
} BST;

BST* createBST(); // 이진탐색트리 생성

Node	*MakeNewnode(int);//이진트리를 이루는 노드 하나 생성

Node	*GetLeftSubtree(Node *node); //왼쪽 서브트리 가져오기

Node  *GetRightSubtree(Node *node);//오른쪽 서브트리 가져오기

Node* treeSearch(Node*, int); // key 값의 노드 위치 반환 (재귀)


//void deleteBST(BST*); // 이진탐색트리 제거

void insertItem(BST*, int); // 삽입

//int removeElement(BST*, int); // 제거

int findElement(BST*, int); // 탐색


void expandExternal(Node*); // 노드의 자식노드로 외부노드 확장 (외부노드->내부노드)

//void reduceExternal(Node*); // 노드의 자식노드인 외부노드 제거 (내부노드->외부노드)

int isExternal(Node*); // 노드의 외부노드 여부 반환
