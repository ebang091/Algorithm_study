#include "graph_algorithm.h"
#include <stdio.h>
void	ft_put_error(int code)
{
	if (code == 1)
		printf("malloc failed.\n");
	else if(code == 2)
		printf("finding edgeNode failed.\n");
	else if(code == 3)
		printf("opposite vetex failed.\n");
	exit(1);
}

Graph *newGraph()
{
	Graph *new = malloc(sizeof(Graph));
	new->numVertices = 0;
	new->numEdges = 0;
	new->vertices = newVertexNode(NULL);
	new->edges = newEdgeNode(NULL);
	return (new);
}

Vertex *newVertex(Data data)
{
	Vertex *vertex = (Vertex *)malloc(sizeof(Vertex));
	vertex->data = data;
	vertex->edgeList =	newEdgeNode(NULL);
	vertex->node = (VertexNode *)malloc(sizeof(VertexNode)); //NULL이 되는 걸 막으려고
	vertex->label = FRESH;
	return (vertex);
}

VertexNode	*newVertexNode(Vertex *vertex)
{
	//할당 받은 후 vertex넣고, 나머지는 초기화 후vertexnode 반환.
	VertexNode *vertexnode = (VertexNode *)malloc(sizeof(VertexNode));
	if (!vertexnode)
		ft_put_error(1);
	if(vertex != NULL)
		vertex->node = vertexnode;
	vertexnode->vertex = vertex;
	vertexnode->prev = NULL;
	vertexnode->next = NULL;
	return(vertexnode);
}

Vertex	*insertVertex(Graph *graph, Data data)//Graph에 vertex를 만들어서 vertexnode까지 추가하는 외부 함수.
{
	Vertex	*vertex = newVertex(data);
	VertexNode * newnode = newVertexNode(vertex);
	VertexNode * vertices = graph->vertices;
	while(vertices->next != NULL)
		vertices = vertices->next;
	vertices->next = newnode;
	newnode->prev = vertices;
	graph->numVertices ++;
	return (vertex);
}

void	insertEdgeNodeToList(EdgeNode *startpoint, EdgeNode *edgenode) //startpoint에서 끝으로 가서 새로운 edgenode를 추가.
{
	while(startpoint->next != NULL)
		startpoint = startpoint->next;
	startpoint->next = edgenode;
	edgenode->prev = startpoint;
	edgenode->next = NULL;// 사실 필요 없음
}

Edge	*newEdge(Vertex *vertex1, Vertex *vertex2)
{
	//vertex1, vertex2 를 잇는 edge 생성.
	//vertex1, vertex2가 가리키는 edgelist에 생성된 edge 등록
	Edge *edge = (Edge *)malloc(sizeof(Edge));
	edge->startPoint = vertex1;
	edge->endPoint = vertex2;
	edge->label = FRESH;
	return (edge);
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

Edge	*insertEdge(Graph *graph, Vertex* vertex1, Vertex *vertex2)
{
	//
	Edge *edge = newEdge(vertex1, vertex2);
	insertEdgeNodeToList(vertex1->edgeList, newEdgeNode(edge));
	insertEdgeNodeToList(vertex2->edgeList, newEdgeNode(edge));
	insertEdgeNodeToList(graph->edges, newEdgeNode(edge));
	graph->numEdges++;
	return (edge);
}

void	printGraph(Graph * graph)
{
	printf("num of vertices : %d\n", graph->numVertices);
	printf("num of edges = %d\n", graph->numEdges);
	
	VertexNode *vertexnode = graph->vertices->next;
	EdgeNode *edgenode;
	while(vertexnode != NULL)
	{
		printf("\nvertex : %c",vertexnode->vertex->data );
		edgenode = vertexnode->vertex->edgeList->next;
		printf(" and relative Edgelist: ");
		while(edgenode != NULL )
		{	
			printf("%c-%c. ", edgenode->edge->startPoint->data, edgenode->edge->endPoint->data);
			edgenode = edgenode->next;
		}
		vertexnode = vertexnode->next;
	}
	edgenode = graph->edges->next;
	printf("\nedges: ");
	while(edgenode != NULL)
	{
		printf("%c and %c. ", edgenode->edge->startPoint->data, edgenode->edge->endPoint->data);
		edgenode = edgenode->next;
	}
	
}

void	createGraph(Graph * graph)
{
	//A,B vertex 생성 후 간선 만들기.
	Vertex *A = insertVertex(graph, 'A');
	Vertex *B = insertVertex(graph, 'B');
	Vertex *C = insertVertex(graph, 'C');

	Edge	*a = insertEdge(graph, A, B);
	Edge	*b = insertEdge(graph, B, C);
}


EdgeNode	*findEdgeNode(EdgeNode* startpoint, Edge* edge)
{
	EdgeNode	*ptr = startpoint;//처음엔 NULL

	while (ptr->next != NULL && ptr->next->edge != edge)
		ptr = ptr->next;
	if (ptr == NULL)
		ft_put_error(2);
	return (ptr->next);
}

void	deleteVertexNode(VertexNode* vertexnode)//해당 Vertexnode를 삭제. (다른 것에는 관련 X)
{
	if(vertexnode -> prev != NULL)
		vertexnode->prev->next = vertexnode->next;
	if(vertexnode->next != NULL)
		vertexnode->next->prev = vertexnode->prev;
	free(vertexnode);

}

void	deleteEdgeNode(EdgeNode* edgenode, int code)
{
	if (code == TRUE)//edge도 삭제. 문제: edge를 포함하는 vertex의 edgelist도 삭제할 것인가? 
		free(edgenode->edge);
	if(edgenode->prev != NULL)
		edgenode->prev->next = edgenode->next;
	if(edgenode->next != NULL)
		edgenode->next->prev = edgenode->prev;
	free(edgenode);
}

void	removeEdge(Graph *graph, Edge *edge)
{
	//1.vertex의 edgelist에서 삭제.
	//2. edge 삭제.
	//3. graph에서 삭제.
	//printf("\ndelete edge: %c - %c\n", edge->startPoint->data, edge->endPoint->data);
	deleteEdgeNode(findEdgeNode(edge->startPoint->edgeList, edge), FALSE);
	deleteEdgeNode(findEdgeNode(edge->endPoint->edgeList, edge), FALSE);
	deleteEdgeNode(findEdgeNode(graph->edges, edge), TRUE);
	graph->numEdges--;

}

void	removeVertex(Graph *graph, Vertex *vertex)
{
	//1. EdgeList의 연결된 Edge삭제 +  Edgenode삭제 
		//removeEdge로 해결.
	//2. VertexNode삭제. : vertex가 포인터 갖고 있음!!!
	EdgeNode	*edgenode = vertex->edgeList;
	//printf("delete vertex: %c\n", vertex->data);
	while (edgenode->next != NULL)
		removeEdge(graph, edgenode->next->edge);
	free(vertex->edgeList);
	deleteVertexNode(vertex->node);//Vertexnode삭제. 
	free(vertex);//vertex삭제. 
	graph->numVertices--;
}



void	deleteGraph(Graph *graph)
{
	//1. vertex삭제. 
	//2. graph삭제. 
	VertexNode *vptr = graph->vertices;
	while(vptr->next != NULL)
		removeVertex(graph, vptr->next->vertex);   
	//이렇게 하거나, rvptr를 먼저 남기면서 포인터 이동.
	free(vptr);
	free(graph->edges);
	free(graph);
}

Vertex	*oppositeVertex(Vertex * vertex, Edge * edge)
{
	if(edge->startPoint == vertex)
		return(edge->endPoint);
	else if(edge->endPoint == vertex)
		return(edge->startPoint);
	else
		ft_put_error(3);


}


void	vertexNodeAddLast(VertexNode * start, VertexNode *vertexnode)
{
	while(start->next != NULL)
		start = start->next;
	start->next = vertexnode;
	vertexnode->prev = start;
	vertexnode->next = NULL;//확인차
}
//다시
void	vertexNodeListfree(VertexNode * vertexnode)
{
	if(vertexnode == NULL)
		return;
	while(vertexnode->next != NULL)
		{
			deleteVertexNode(vertexnode->next);
		}
	free(vertexnode);
}
VertexNode* adjVertices(Graph* graph, Vertex* vertex)
{
	VertexNode *vertexnode = newVertexNode(NULL);
	EdgeNode *ptr = vertex->edgeList->next;
	VertexNode *newnode;


	while(ptr != NULL)
	{
		newnode = newVertexNode(oppositeVertex(vertex, ptr->edge));
		vertexNodeAddLast(vertexnode, newnode);
		ptr = ptr->next;
	}
	return (vertexnode);
}