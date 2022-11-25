#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)

//1. 인접 리스트 표현
typedef struct node_ {
	int weight;
	int data;
	struct node_* next;
}node;//가중치, 인접 노드를 포함하는 노드 정보(vertex임. )  - 단방향 연결리스트로 구현.

typedef struct graph_ {
	node* vertex;
}graph;//배열로써 node를 연결 리스트로 가진다. 

/*
함수 정리
[public]
* push_back : graph에 node1 이 갖는 이웃 vertex를 행렬로 삽입. weight와 함께 삽입.
	
	create_vertex: 를 양쪽으로 수행.
* change_weight(node1 , node2) : 두  노드 사이의 가중치 값 변경: 찾은 다음에 하나씩 바꿔준다.
	chage_weight_utils를 서로 바꿔서 수행
* print_node(graph)  : 구조체를 입력받아 해당 연결 노드들의 정보를 출력한다.
	구조체 배열 중 하나를 받은 다음 연결리스트 탐색 , 출력 수행
* delete_vertex(graph, node1, node1)
[private]
* newVertex: data, weight 가지는 vertext node생성[이웃]
* lst_add : 인접행렬 부분에서 인접리스트에 원하는 위치에 삽입: 특정 리스트 뒤에.
* change_weight_utils(node, vertex, weight) : 해당 node구조체에서 vetex 행렬을 찾아서 weight의 값을 변경.
* create_vertex :  newVertex를 만든 다음 맞는 위치[오름차순]에 lst_add
* delete_vertex_utils : node1 에서node 간선을 삭제.
* 

*/
void ft_put_error(char* str);
void push_back(graph* graph, int vertex1, int vertex2, int weight);
int delete_vertex_utils(graph* graph, int node1, int node2);


void print_node(graph* graph)
{
	node* ptr = graph->vertex;
	if (ptr == NULL)
	{
		printf("-1");
		return;
	}
	while (ptr != NULL)
	{
		printf(" %d %d", ptr->data, ptr-> weight);
		ptr = ptr->next;
	}
	printf("\n");


}

void change_weight_utils(graph * Graph, int node1, int node2, int weight)
{
	node *ptr;

	ptr = Graph[node1].vertex;
                                                                                                 	while (ptr != NULL)
	{
		if (ptr->data == node2)
			break;
		ptr = ptr->next;
	}
	if (ptr == NULL)
	{
		push_back(Graph, node1, node2, weight);
		return;
	}
	ptr->weight = weight;

}

int delete_vertex_utils(graph* graph, int node1, int node2)
{
	node* ptr = graph[node1].vertex;
	if (ptr == NULL)
	{
		printf("-1");
		return -1;
	}
	if (ptr->data == node2)
	{
		graph[node1].vertex = ptr->next;
		free(ptr);
		return 0;
	}
	while (ptr != NULL)
	{
		if (ptr->next == NULL)
		{
			printf("-1");
			return -1;
		}
		if (ptr->next->data == node2)
			break;
		ptr = ptr->next;
	}
	if (ptr == NULL)
		ft_put_error("error in delte_vertex_utils");
	node* rptr = ptr->next;
	if (rptr != NULL)
		ptr->next = rptr->next;
	free(rptr);
	return 0;

}

void delete_vertex(graph* graph, int node1, int node2)
{
	if(delete_vertex_utils(graph, node1, node2) < 0)
		return;
	if (node1 != node2)
		delete_vertex_utils(graph, node2, node1);
}


void change_weight(graph* graph, int node1, int node2, int weight) //&graph[1], &graph[2] -> 1,2에 대한 노드 정보 변경. 
{
	if (weight != 0)
	{
		change_weight_utils(graph, node1, node2, weight);
		change_weight_utils(graph, node2, node1, weight);
	}
	else //간선 삭제. 
	{
		delete_vertex(graph, node1, node2);
	}

}

void ft_put_error(char* str)
{
	printf("%s", str);
	exit(1);
}

void lst_add(node* vertex1, node* vertex2)
{
	if (vertex1 == NULL)
		ft_put_error("vertex1 error in lst_add");
	vertex2->next = vertex1->next;
	vertex1->next = vertex2;
}

//data(이름), weight정보를 가진 node를 생성
node* newVertex(int vertex, int weight)
{
	node* newnode = (node*)malloc(sizeof(node));
	newnode->data = vertex;
	newnode->weight = weight;
	newnode->next = NULL;
	return (newnode);
}
//작, 큰 순서로 노드 두개가 들어온다고 할 때 간선 설정.


void create_vertex(graph* graph, int vertex, int weight) //graph자리에 vertex삽입
{
	node* newvertex = newVertex(vertex, weight);
	if (graph->vertex == NULL)//처음 삽입 시
	{
		graph->vertex = newvertex;
		return;
	}
	node* ptr = graph->vertex;
	if (ptr-> data > vertex)//맨 앞에 삽입해야 할 때 
	{
		newvertex->next = graph->vertex;
		graph->vertex = newvertex;
		return;
	}
	while (ptr->next != NULL)
	{
		if (ptr->next->data > vertex)
			break;
		ptr = ptr->next;
	}
	lst_add(ptr, newvertex);


}

void push_back(graph* graph, int vertex1, int vertex2, int weight)
{

	create_vertex(&graph[vertex1], vertex2, weight);
	if(vertex1 != vertex2)
		create_vertex(&graph[vertex2], vertex1, weight);

	
}

void makeGraph(graph* graph)
{
	push_back(graph, 1, 2, 1);
	push_back(graph, 1, 3, 1);
	push_back(graph, 2, 3, 1);
	push_back(graph, 3, 5, 4);
	push_back(graph, 5, 5, 4);

	push_back(graph, 1, 4, 1);
	push_back(graph, 1, 6, 2);
	push_back(graph, 5, 6, 3);
	
}


int main()
{
	graph graph[7];
	for (int i = 0; i < 7; i++)
		graph[i].vertex = NULL;
	//그래프 생성
	makeGraph(graph);


	char order;
	int n1, n2, w;
	//메쏘드
	while (1)
	{
		//
		scanf("%c", &order);
		//printf("order : %c\n", order);
		if (order == 'a')
		{
			scanf("%d", &n1);
			//printf("%c %d", order, n1);
			if (n1 > 0 && n1 < 7)
			{
				//printf("print %d graph\n", n1);
				print_node(&graph[n1]);
			}
			else
				printf("-1");
		}
		else if (order == 'm')
		{
			scanf("%d %d %d", &n1, &n2, &w);
			if (n1 < 1 || n1 > 6 || n2 < 1 || n2 > 6)
			{
				printf("-1");
			}
			else
				change_weight(graph, n1, n2, w);
		}
		else if (order == 'q')
		{
			return;
		}
		getchar();
	}

}