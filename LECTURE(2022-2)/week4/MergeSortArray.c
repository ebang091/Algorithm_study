#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)
int heap[100];
int numOfData;
//**최대힙으로 구현!**
void upheap(int num);
//insert할 때 가장 아래에 추가하고 위치를 찾으러 올라감.
//void insert(int* heap, int data);
//일단 가장 아래에 추가하고 upheap을 통해 위치를 찾음.
void downheap(int num);
//delete할 때 가장 아래 노드를 루트에 놓고 아래로 위치를 찾으러 감.
void	rbuildheap(int num);
//아래 힙들은 모두 힙이라는 전제하에 수행: 말단 노드일 때 재귀가 종료된다. 
//rbuildheap: 왼쪽 자식

/*void	insert(int data)
{
	heap[++numOfData] = data;
	upheap(numOfData);
}
*/

void	upheap(int num) {
	int parent = num / 2;
	int temp;
	if (num > numOfData || num == 1)
		return;
	if (heap[num] > heap[parent])
	{
		temp = heap[num];
		heap[num] = heap[parent];
		heap[parent] = temp;
		upheap(parent);
	}
}

void	downheap(int num)
{
	int temp;
	int child = num * 2;

	if (num > numOfData)
		return;
	if (child == numOfData)
	{
		if (heap[num] < heap[child])
		{
			temp = heap[num];
			heap[num] = heap[child];
			heap[child] = temp;
			downheap(child);
		}
	}
	else if (child + 1 <= numOfData)
	{
		//오른쪽, 왼쪽 비교한 뒤 최대힙이 되게 조정!!!
		if (heap[child] < heap[child + 1])
			child++;
		if (heap[num] < heap[child])
		{
			temp = heap[num];
			heap[num] = heap[child];
			heap[child] = temp;
			downheap(child);
		}
	}

}

void	buildheap()
{
	for (int i = numOfData / 2; i >= 1; i--)
	{
		downheap(i);
	}
}

void	rbuildheap(int num)
{
	/*
	* <재귀적 힙 생성-> 아직 실패>
	* buildheap : 재귀적으로 힙을 생성하되 downheap을 쓸거다.
	* downheap: 아래 힙은 다 힙구조라고 전제.
	
	//말단 노드일 때 return
	if (num * 2 < numOfData)
		return;
	rbuildheap(num * 2);
	if (num * 2 + 1 <= numOfData)
		rbuildheap(num*2+1);
	downheap(num);*/
	/*
	*
	*			1
	*	    2		3
	*	 4    5	  6
	*
	*
	*/
}

void	sort(int n)
{
	int temp;
	for (int i = n; i >= 1; i--)
	{
		//for (int i = 1; i <= n; i++)
		//{	
		//	printf("in sort:");
		//	printf("%d", heap[i]);
		//}
		printf("\n");
		temp = heap[i];
		heap[i] = heap[1];
		heap[1] = temp;
		numOfData--;
		downheap(1);

	}

}
/*
		1            4
	  4   3       2		3
	2		   1


		1				3
	 2     3		1		2

*/
/*
 5 4 3 2 1
(1 4 3 2 5 -> heap: [1 4 3 2] -> [4 2 3 1] )
 4 2 3 1 5
(1 2 3 4 5) -> heap [1 2 3]  -> [2 1 3] -> [3 1 2]
 2 1 3 4 5
(



*/
int main()
{
	int n;
	//int data;

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &heap[++numOfData]);
	}
	buildheap();
	

	sort(n);
	for (int i = 1; i <= n; i++)
		printf(" %d", heap[i]);
	printf("\n");



}



/*
i 209 ↦ key 209 insert
i 400 ↦ key 400 insert
d ↦ delete
i 77 ↦ key 77 insert
d ↦ delete
p ↦ print
q ↦ quit
*/
