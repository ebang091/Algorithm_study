#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

Graph *newGraph()
{
	Graph *new = malloc(sizeof(Graph));
	new->numVertices = 0;
	new->numEdges = 0;
	new->vertices = (VertexNode *)malloc(sizeof(VertexNode));
	new->vertices->prev = NULL;
	new->vertices->next = NULL;
	new->vertices->vertex = NULL;

	new->edges = (EdgeNode *)malloc(sizeof(EdgeNode));
	new->edges->next = NULL;
	new->edges->prev = NULL;
	new->edges->edge = NULL;
	return (new);
}

Vertex *newVertex(Data data)
{
	Vertex *vertex = (Vertex *)malloc(sizeof(Vertex));
	vertex->data = data;
	vertex->edgeList = (EdgeNode *)malloc(sizeof(EdgeNode));
	vertex->edgeList->next = NULL;
	vertex->edgeList->prev = NULL;
	vertex->edgeList->edge = NULL;
	return (vertex);
}

VertexNode	*newVertexNode(Vertex *vertex)
{
	//할당 받은 후 vertex넣고, 나머지는 초기화 후vertexnode 반환.
	VertexNode *vertexnode = (VertexNode *)malloc(sizeof(vertexnode));
	vertexnode->vertex = vertex;
	vertexnode->prev = NULL;
	vertexnode->next = NULL;
	return(vertexnode);
}

void	insertVertex(Graph *graph, VertexNode *vertexnode)//Graph에 vertexnode를 추가.
{
	VertexNode * vertices = graph->vertices;
	while(vertices->next != NULL)
		vertices = vertices->next;
	vertices->next = vertexnode;
	vertexnode->prev = vertices;
	graph->numVertices ++;
}

void	insertEdgeToList(Edge *newedge, EdgeNode * edgenodelist)
{
	EdgeNode *ptr = edgenodelist;
	EdgeNode *newedgenode = (EdgeNode *)malloc(sizeof(EdgeNode));
	while(ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = newedgenode;
	newedgenode->edge = newedge;
	newedgenode->next = NULL;
	newedgenode->prev = ptr;
}

EdgeNode	*newEdgeNode(Edge *edge)
{
	//edgeNode 생성해서 edge넣고 나머지 초기화 후 반환
	EdgeNode *edgeNode = (EdgeNode *)malloc(sizeof(EdgeNode));
	edgeNode->edge = edge;
	edgeNode ->prev = NULL;
	edgeNode->next = NULL;
	return (edgeNode);
}

void	insertEdge(Graph *graph, EdgeNode *newedgenode)
{
	EdgeNode *edgeNode = graph->edges;
	//새로 edgenode추가할 edgenode까지 이동
	while(edgeNode->next != NULL)
		edgeNode= edgeNode -> next;
	edgeNode->next  = newedgenode;
	newedgenode->prev = edgeNode;
	graph->numEdges++;
}

EdgeNode	*newEdge(Vertex *vertex1, Vertex *vertex2)
{
	//vertex1, vertex2 를 잇는 edge 생성.
	//vertex1, vertex2가 가리키는 edgelist에 생성된 edge 등록
	Edge *edge = (Edge *)malloc(sizeof(Edge));
	edge->startPoint = vertex1;
	edge->endPoint = vertex2;
	insertEdgeToList(edge, vertex1->edgeList);
	insertEdgeToList(edge, vertex2->edgeList);
	//printf("check1: edge %c to %c\n", vertex1->edgeList->next->edge->startPoint->data,vertex1->edgeList->next->edge->endPoint->data);
	//printf("check2: edge %c to %c\n", vertex2->edgeList->next->edge->startPoint->data,vertex2->edgeList->next->edge->endPoint->data );
	EdgeNode *edgenode = newEdgeNode(edge);
	return (edgenode);
}

void	printGraph(Graph * graph)
{
	printf("num of vertixes : %d\n", graph->numVertices);
	printf("num of edges = %d\n", graph->numEdges);
	
	VertexNode *vertexnode = graph->vertices->next;
	EdgeNode *edgenode;
	while(vertexnode != NULL)
	{
		printf("vertex : %c",vertexnode->vertex->data );
		edgenode = vertexnode->vertex->edgeList->next;
		while(edgenode != NULL )
		{	
			printf(" and Edgelist: %c-%c\n", edgenode->edge->startPoint->data, edgenode->edge->endPoint->data);
			edgenode = edgenode->next;
		}
		vertexnode = vertexnode->next;
	}
	edgenode = graph->edges->next;
	while(edgenode != NULL)
	{
		printf("edges : %c and %c\n", edgenode->edge->startPoint->data, edgenode->edge->endPoint->data);
		edgenode = edgenode->next;
	}
	
}

void	createGraph(Graph * graph)
{
	//A,B vertex 생성 후 간선 만들기.
	Vertex *A = newVertex('A');
	Vertex *B =newVertex ('B');
	Vertex *C = newVertex ('C');
	insertVertex(graph, newVertexNode(A));
	insertVertex(graph, newVertexNode(B));
	insertVertex(graph, newVertexNode(C));

	EdgeNode * a = (newEdge(A, B)); //graph에도 추가완료
	insertEdge(graph, a);

	EdgeNode *b = (newEdge(B, C));
	insertEdge(graph, b);
}


void	deleteEdgeNode(EdgeNode * edgenode, int key)//key가 FALSE일때는 다 처리하고 한 EdgeNode만 삭제할 때 처리.
{
	//Edgenode끼리 제거 노드 제외하고 다시 연결
	EdgeNode *rptr = edgenode;
	if(key == TRUE)
	{
		if(rptr->next != NULL)
			rptr->next->prev = rptr->prev;
		if(rptr->prev != NULL)
			rptr->prev->next = rptr->next;
	//edgelist제거 : 1. 찾기
		EdgeNode *ptr = rptr->edge->startPoint->edgeList;
		while(ptr->edge != rptr->edge)
		ptr = ptr->next;
	//찾은 후 EdgeList의 노드 제거
		if(ptr->next != NULL)
			ptr->next->prev = ptr->prev;
		if(rptr->prev != NULL)
			ptr->prev->next = ptr->next;
		free(ptr);
	}
}


void	deleteVertexNode(Graph *graph, VertexNode  *vertexnode)//vertex 관련 edgeList는 삭제했어도 edgeNode는
{
	VertexNode *rptr = vertexnode;
	VertexNode *ptr;
	EdgeNode *rEptr;
	EdgeNode *Eptr;
	//vertex의 edgelist삭제
	Eptr = rptr->vertex->edgeList->next;
	while (Eptr != NULL)
	{
		rEptr = Eptr->next;
		free(Eptr->edge);
		free(Eptr);
		Eptr = rEptr;
	}
	free(rptr->vertex->edgeList);
	

	//vertex삭제
	free(rptr->vertex);
	//vertexnode연결
	graph->vertices = rptr->next;
	if (rptr->prev != NULL)
		rptr->prev->next = rptr->next;
	if (rptr->next != NULL)
		rptr->next->prev = rptr->prev;
	free(rptr);
}

void	deleteGraph(Graph *graph)
{
	EdgeNode * eptr = graph->edges->next;
	EdgeNode * reptr;
	VertexNode *vptr = graph->vertices->next;
	VertexNode *rvptr;
	
	//VertexNode 삭제. 	
	while(vptr != NULL)
	{
		rvptr = vptr->next;
		deleteVertexNode(graph, vptr);   
		vptr = rvptr;
	}
	printf("\nAfter vertex delete\n");
	printGraph(graph);
	while(eptr != NULL)
	{
		reptr = eptr->next;
		free(eptr);
		eptr = reptr;
	}
	free(graph->vertices);
	free(graph->edges);
	free(graph);

}

int main()
{
	Graph *graph = newGraph();
	createGraph(graph);
	printGraph(graph);
	deleteGraph(graph);
}
