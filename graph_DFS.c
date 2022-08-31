#include "./graph_algorithm.h"
#include <stdio.h>

void	DFS(Graph * graph)
{
	//처음 시작할 vertex랜덤으로 고르고
	//드라이브 함수로써 재귀를 시작. 
	Vertex* start = graph->vertices->next->vertex;
	if(start)
		rDFS(start);
}

void	rDFS(Vertex* vertex)
{
	//1. vertex 방문 했으니 visited로 라벨 변경
	//2. vertex의 edgelist에 fresh한 간선이 있는지 확인
		//2-1. fresh한 정점이 있다면 방문(재귀)
		//2-2. VISITED 정점밖에 없다면 edge의 라벨만 변경.
	//3. fresh한 간선이 없다면 종료.
	printf("visited vertex : %c\n", vertex->data);
	vertex->label = VISITED;
	EdgeNode* edgenode = vertex->edgeList->next;
	while(edgenode != NULL)
	{
		if(edgenode->edge->label == FRESH)
			if(oppositeVertex(vertex ,edgenode->edge)->label == FRESH)
				{ 
					edgenode->edge->label = TREE;
					printf("Tree edge: %c- %c\n", edgenode->edge->startPoint->data, edgenode->edge->endPoint->data);
					rDFS(oppositeVertex(vertex, edgenode->edge));
				}
			else
				{
					edgenode->edge->label = BACK;
					printf("Back edge: %c-%c\n", edgenode->edge->startPoint->data, edgenode->edge->endPoint->data);
				}
		edgenode = edgenode->next;
	}

}
