#include "graph_algorithm.h"
#include <stdio.h>

void	BFS(Graph *graph)
{
	//vertex의 edgelist를 모두 방문.  (level 1)
	//방문했던 level1 vertex에서 edgelist를 방문. 이미 방문햇었다면(같은 레벨이었을 때) edge : cross. 아니면 TREE
	//방문했던 level2 vertex에서 edgelist를 방문. 
/*
while(list != null)
{
	
	while(list -> next)
	{
		edgelist 점검.  , newlst생성
	}
	list = newlst;
*/
	VertexNode * vertexnode = newVertexNode(NULL);
	vertexNodeAddLast(vertexnode, newVertexNode(graph->vertices->next->vertex));//원래는 랜덤 선택
	
	while(vertexnode->next != NULL)
	{
		VertexNode *ptr = newVertexNode(NULL); //새로 만들 level + 1vertex리스트.
		while(vertexnode->next != NULL)
		{
			vertexnode = vertexnode->next;
			printf("VISITED vertex: %c\n", vertexnode->vertex->data);
			EdgeNode* edgenode = vertexnode->vertex->edgeList;
			while(edgenode->next != NULL)
			{
				edgenode = edgenode->next;
				if (oppositeVertex(vertexnode->vertex, edgenode->edge )->label == FRESH)
				{
					printf("TREE edge: %c -%c\n", edgenode->edge->startPoint->data, edgenode->edge->endPoint->data);
					vertexNodeAddLast(ptr, newVertexNode(oppositeVertex(vertexnode->vertex, edgenode->edge)));
					printf("added vertex: %c = %c\n", oppositeVertex(vertexnode->vertex, edgenode->edge)->data, ptr->next->vertex->data);
					edgenode->edge->label = TREE;
				}
				else
				{
					if(edgenode->edge->label == FRESH)	
						{
							printf("BACK edge : %c-%c\n", edgenode->edge->startPoint->data, edgenode->edge->endPoint->data);
							edgenode->edge->label = BACK;
						}
				}	
			}
		}
		printf("ok");
		printf("newly made list: %c", ptr->next->vertex->data;
		vertexnode = ptr;
		vertexNodeListfree(ptr);
	}
}