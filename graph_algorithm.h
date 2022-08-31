#ifndef GRAPH_ALGORITHM_H
#define GRAPH_ALGORITHM_H

#define TRUE 1
#define FALSE 0

//vertex
#define VISITED 1
#define	FRESH	0
//edge
#define	TREE	1
#define	BACK	2

#include <stdlib.h>
typedef char Data;

typedef struct Edge_ {
   struct Vertex_* startPoint;
   struct Vertex_* endPoint;
   int	label;
   // int weight;
} Edge;

typedef struct EdgeNode_ {
   Edge* edge;
   struct EdgeNode_* next;
   struct EdgeNode_* prev;
} EdgeNode;

typedef struct Vertex_ {
   Data data;
   EdgeNode* edgeList;
   struct VertexNode_* node;
   int	label;
} Vertex;

typedef struct VertexNode_ {
   Vertex* vertex;
   struct VertexNode_* next;
   struct VertexNode_* prev;
} VertexNode;

typedef struct Graph_ {
   int numVertices;
   int numEdges;
   VertexNode* vertices;
   EdgeNode* edges;
} Graph;



//DFS algorithm
void	DFS(Graph * graph);
void	rDFS(Vertex* vertex);


//Graph default method
Graph* newGraph();

void	createGraph(Graph * graph);
void deleteGraph(Graph*);

VertexNode* newVertexNode(Vertex*);

Vertex* newVertex(Data);// newVertexNode 사용예정

void deleteVertexNode(VertexNode *);

EdgeNode* newEdgeNode(Edge*);

Edge	*newEdge(Vertex* , Vertex*);//vertex1, vertex2 묶고 vertexnode생성 하고, 각 vertex에 edgelist에도 추가.  graph에 추가만 하면 됨. 

void deleteEdgeNode(EdgeNode *, int);

EdgeNode* findEdgeNode(EdgeNode*, Edge*);

Vertex* insertVertex(Graph*, Data);

void removeVertex(Graph*, Vertex*);



void insertEdgeToList(EdgeNode *, EdgeNode*);

Edge* insertEdge(Graph*, Vertex*, Vertex* /* weight */);

void removeEdge(Graph*, Edge*);



VertexNode* adjVertices(Graph*, Vertex*);

Vertex* oppositeVertex(Vertex*, Edge*);

int isConnected(Vertex*, Vertex*);


void printGraph(Graph*);
void	vertexNodeAddLast(VertexNode * start, VertexNode *vertexnode);

void	vertexNodeListfree(VertexNode * vertexnode);

void	BFS(Graph *graph);
#endif