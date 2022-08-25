#pragma once


#define TRUE 1
#define FALSE 0

typedef char Data;

typedef struct Edge_ {
   struct Vertex_* startPoint;
   struct Vertex_* endPoint;
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



#include "graph.h"
#include <stdlib.h>



Graph* newGraph();

void deleteGraph(Graph*);

Vertex* insertVertex(Graph *, Data);//임의추가

VertexNode* newVertexNode(Vertex*);

Vertex* newVertex(Data);// newVertexNode 사용예정

void deleteVertexNode(VertexNode *);

EdgeNode* newEdgeNode(Edge*);

Edge	*newEdge(Vertex* , Vertex*);//vertex1, vertex2 묶고 vertexnode생성 하고, 각 vertex에 edgelist에도 추가.  graph에 추가만 하면 됨. 

void deleteEdgeNode(EdgeNode *, int);

//EdgeNode* findEdgeNode(EdgeNode*, Edge*);

Edge	*insertEdge(Graph *, Vertex*, Vertex*);//임의추가. EdgeNode list에 Edge를 추가.

//Vertex* insertVertex(Graph*, Data);

void removeVertex(Graph*, Vertex*);



void insertEdgeToList(EdgeNode *, EdgeNode*);

//Edge* insertEdge(Graph*, Vertex*, Vertex* /* weight */);

void removeEdge(Graph*, Edge*);



VertexNode* adjVertices(Graph*, Vertex*);

Vertex* oppositeVertex(Vertex*, Edge*);

int isConnected(Vertex*, Vertex*);


void printGraph(Graph*);