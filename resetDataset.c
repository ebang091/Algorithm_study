#include "resetDataset.h"
#include <stdio.h>

void resetDataset(int data[], int size, int option)
{
	if (option == REVERSED)
	{
		for (int i = 0; i < size; i++)
			data[i] = size - i - 1;
	}
	else
	{
		for (int i = 0; i < size; i++)
			data[i] = i;
		if (option == RANDOM)
		{
			for (int i = 0; i < SHUFFLE_COUNT; i++)
			{
				int r1 = rand() % size;
				int r2 = rand() % size;
				int tmp = data[r1];
				data[r1] = data[r2];
				data[r2] = tmp;
			}
		}
	}
}
