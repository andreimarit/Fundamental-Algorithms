#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include "Profiler.h"

Profiler profiler("HTable");

int a[10] = { 2, 7, 5, 2, 7, 7, -1, 5, 2 };

struct Parent
{
	int count;
	int children_p[10];
};

struct NodeV1
{
	int value;
	NodeV1* children[10];
	int count;
};

struct NodeV2
{
	int value;
	NodeV2* LeftChild;
	NodeV2* RightSiblings;
};

int	T1(NodeV1 **r2, Parent* p)
{
	int root = (*r2)->value;
	for (int i = 0; i < p[root].count; i++)
	{
		(*r2)->children[i] = (NodeV1 *)malloc(sizeof(NodeV1));
		(*r2)->children[i]->count = 0;
		(*r2)->count += 1;
		(*r2)->children[i]->value = p[root].children_p[i];
		T1(&(*r2)->children[i], p);
	}
	//return (0);
}

void afisare_R2(NodeV1 *r2)
{
	int root = r2->value;
	int i = 0; 
	int j = 0;
	if (r2->count !=0)	printf("Nod %d with children:", r2->value + 1);
	while (i < r2->count)
	{
		//if (r2->children[i])
		printf("  %d", r2->children[i]->value + 1);
		i++;
	}
	if (r2->count != 0) printf("\n");
	while (j < r2->count)	
	{
		afisare_R2(r2->children[j]);
		j++;
	}
}

int T2(NodeV2** r3, NodeV1 *r2)
{
	int i = 0;
	NodeV2* buff = (NodeV2*)malloc(sizeof(NodeV2));
	buff->LeftChild = NULL;
	buff->RightSiblings = NULL;
	buff->value = 0;
	
	while (i < r2->count)
	{
		if (i == 0)
		{
			(*r3)->LeftChild = (NodeV2 *)malloc(sizeof(NodeV2));
			(*r3)->LeftChild->value = r2->children[i]->value+1;
			(*r3)->LeftChild->LeftChild = NULL;
			(*r3)->LeftChild->RightSiblings = NULL;
			buff = (*r3)->LeftChild;
			i++;
		}
		else
		{
			buff->RightSiblings = (NodeV2 *)malloc(sizeof(NodeV2));
			buff->RightSiblings->LeftChild = NULL;
			buff->RightSiblings->RightSiblings = NULL;
			buff->RightSiblings->value = r2->children[i]->value+1;
			T2(&buff, r2->children[i - 1]);
			buff = buff->RightSiblings;
			i++;
		}
	}
	return (0);
}

void afisare_R3(NodeV2* r3, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		printf("\t");
		i++;
	}
	printf("%d\n", r3->value);
	if (r3->LeftChild != NULL) afisare_R3(r3->LeftChild, n + 1);
	if (r3->RightSiblings != NULL) afisare_R3(r3->RightSiblings, n);
}

int main() 
{
	
	int n = 9;

	Parent* p = (Parent*)malloc(n * sizeof(Parent));
	int root = 0;
	int x, y;
	for (int i = 0; i < n; i++)
		p[i].count = 0;
	
	for (int i = 0; i < n; i++)
	{
		y = a[i];
		if (a[i] == -1)
			root = i;
		else 
		{
			x=p[y-1].count;
			p[y-1].children_p[x] = i;
			p[y-1].count++;
		}
	}
	
	NodeV1* r2 = (NodeV1*)malloc(sizeof(NodeV1));
	r2->count = 0;
	r2->value = root;
	T1(&r2, p);
	printf("\n\nR2:\n");
	afisare_R2(r2);
	
	NodeV2* r3 = (NodeV2*)malloc(sizeof(NodeV2));
	r3->value = root+1;
	r3->RightSiblings = NULL;
	r3->LeftChild = NULL;
	T2(&r3, r2);
	printf("\n\nR3:\n");
	afisare_R3(r3, 0);
	_getch();
	return 0;
}


