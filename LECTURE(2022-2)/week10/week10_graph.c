#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)

//1. ���� ����Ʈ ǥ��
typedef struct node_ {
	int weight;
	int data;
	struct node_* next;
}node;//����ġ, ���� ��带 �����ϴ� ��� ����(vertex��. )  - �ܹ��� ���Ḯ��Ʈ�� ����.

typedef struct graph_ {
	node* vertex;
}graph;//�迭�ν� node�� ���� ����Ʈ�� ������. 

/*
�Լ� ����
[public]
* push_back : graph�� node1 �� ���� �̿� vertex�� ��ķ� ����. weight�� �Բ� ����.
	
	create_vertex: �� �������� ����.
* change_weight(node1 , node2) : ��  ��� ������ ����ġ �� ����: ã�� ������ �ϳ��� �ٲ��ش�.
	chage_weight_utils�� ���� �ٲ㼭 ����
* print_node(graph)  : ����ü�� �Է¹޾� �ش� ���� ������ ������ ����Ѵ�.
	����ü �迭 �� �ϳ��� ���� ���� ���Ḯ��Ʈ Ž�� , ��� ����
* delete_vertex(graph, node1, node1)
[private]
* newVertex: data, weight ������ vertext node����[�̿�]
* lst_add : ������� �κп��� ��������Ʈ�� ���ϴ� ��ġ�� ����: Ư�� ����Ʈ �ڿ�.
* change_weight_utils(node, vertex, weight) : �ش� node����ü���� vetex ����� ã�Ƽ� weight�� ���� ����.
* create_vertex :  newVertex�� ���� ���� �´� ��ġ[��������]�� lst_add
* delete_vertex_utils : node1 ����node ������ ����.
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


void change_weight(graph* graph, int node1, int node2, int weight) //&graph[1], &graph[2] -> 1,2�� ���� ��� ���� ����. 
{
	if (weight != 0)
	{
		change_weight_utils(graph, node1, node2, weight);
		change_weight_utils(graph, node2, node1, weight);
	}
	else //���� ����. 
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

//data(�̸�), weight������ ���� node�� ����
node* newVertex(int vertex, int weight)
{
	node* newnode = (node*)malloc(sizeof(node));
	newnode->data = vertex;
	newnode->weight = weight;
	newnode->next = NULL;
	return (newnode);
}
//��, ū ������ ��� �ΰ��� ���´ٰ� �� �� ���� ����.


void create_vertex(graph* graph, int vertex, int weight) //graph�ڸ��� vertex����
{
	node* newvertex = newVertex(vertex, weight);
	if (graph->vertex == NULL)//ó�� ���� ��
	{
		graph->vertex = newvertex;
		return;
	}
	node* ptr = graph->vertex;
	if (ptr-> data > vertex)//�� �տ� �����ؾ� �� �� 
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
	//�׷��� ����
	makeGraph(graph);


	char order;
	int n1, n2, w;
	//�޽��
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