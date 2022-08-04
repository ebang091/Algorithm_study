#include "./binarySearchTree.h"

BST* createBST() // 이진탐색트리 생성
{
	BST *newTree = (BST *)malloc(sizeof(BST));
	return (newTree);
}

/*void deleteBST(BST*) // 이진탐색트리 제거
{

}
*/

Node	*Makenewnode(int key)//이진트리를 이루는 노드 하나 생성.
{
	Node *newnode = (Node *)malloc(sizeof(Node));
	newnode->key = key;
	return (newnode);
}

Node	*GetLeftSubtree(Node *node)
{
	if(node->lChild != NULL)
		return(node->lChild);
	else
		return (NULL);
}

Node	*GetRightSubtree(Node *node)
{
	if(node->rChild != NULL)
		return (node->rChild);
	else
		return (NULL);
}

Node* treeSearch(Node* node, int key) // key 값의 노드 위치 반환 (재귀)
{
	if(node == 0)
		return 
		(NULL);

	if(node->key == key)
		return node;
	else if(node->key < key)
		return (treeSearch(GetLeftSubtree(node), key));
	else
		return (treeSearch(GetRightSubtree(node), key));
}

void expandExternal(Node* node) // 노드의 자식노드로 외부노드 확장 (외부노드->내부노드)
{	
	node->lChild = NULL;
	node->rChild = NULL;

}
void insertItem(BST* tree, int key) // 삽입
{
	Node *insertNode = tree->root;
	Node *parentNode = tree->root;

	while(insertNode != NULL)
	{
		if (insertNode->key == key)	//key가 이미 존재하면 return
			return;
		parentNode = insertNode;	//parent를 저장하여, 새로운 노드에 저장할 수 있어야 한다.
		if (insertNode->key > key) 	//찾는 값에 따라 left, right 이동하다가 NULL이 되면 그 위치가 곧 새로운 노드가 위치할 곳
			insertNode = GetLeftSubtree(insertNode);
		else
			insertNode = GetRightSubtree(insertNode);
	}
		
	//새 노드가 위치할 곳이 insertNode의 위치.
	//새 노드가 루트가 되는 경우 고려
	Node 	*newnode = MakeNewnode(key);
	if(parentNode != NULL)
	{
		newnode->parent = parentNode;
		expandExternal(newnode);
	}
	else
	{
		tree->root = newnode;
		expandExternal(newnode);
	}


}

//int removeElement(BST*, int); // 제거

int findElement(BST* tree, int key) // 탐색
{
	Node * find = (treeSearch(tree->root, key));
	if(!find)
		return (find->key);
	return (NO_SUCH_KEY);
		 
}



//void reduceExternal(Node*); // 노드의 자식노드인 외부노드 제거 (내부노드->외부노드)

//int isExternal(Node*); // 노드의 외부노드 여부 반환
