#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>


#include "Profiler.h"

/**
To improve the time complexity of the algorithm, we have used 2 heuristics: union by rank and path compressions. This way, we reduced the time
complexity from O(n) in worst case for just one operation of FindSet or Union (because in worst case, the sets will be a linear chain of n
nodes), to an almost linear running time in the total number of operations m: O(m * Alpha(n)).
Alpha(n) is the inverse Ackermann function (this function has very small values, smaller than 5 for any n, therefore the complexity is almost
linear). So, using this 2 improvements, the time per operations becomes O(Alpha(n)), making the operations on disjoint sets take place in
essentially constant time.
We can see this on the graph as well, since the function is a linear one. The reason why my graph has those "edges" is because i used a while
in Kruskal Alg, so at every graph the number of operations may differ.
*/

Profiler profiler("Disjoints Sets");

int op = 0;

struct Node
{
	int key;
	int rang;
	Node* p;
};

struct Edge
{
	Node* start;
	Node* end;
	int weight;
};

Node* MakeSet(int x)
{
	Node* pNew = (Node*)malloc(sizeof(Node));
	pNew->key = x;
	pNew->rang = 0;
	pNew->p = pNew;
	op += 4;
	return pNew;
}

Edge* BuildEdge(Node* s, Node* e, int w)
{
	Edge* eNew = (Edge*)malloc(sizeof(Edge));
	eNew->start = s;
	eNew->end = e;
	eNew->weight = w;
	return eNew;
}

Node* FindSet(Node* s)
{
	Node* x;
	op++;
	if (s != s->p)
	{
		op++;
		x = FindSet(s->p);
	}
	else
	{
		return s;
	}
	op++;
	s->p = x;
	return s->p;
}

void Union(Node* S1, Node* S2)
{
	if (S1->rang > S2->rang)
	{
		FindSet(S2)->p = FindSet(S1);
		op++;
	}
	else
	{
		op++;
		FindSet(S1)->p = FindSet(S2);
		if (S1->rang == S2->rang)
		{
			S2->rang++;
		}
	}
}

void swapFunct(Edge** a, Edge** b)
{
	Edge* temp = *a;
	*a = *b;
	*b = temp;
}

int Partition(Edge* arr[], int s, int e)
{
	Edge* x = arr[e];
	int index = s - 1;

	for (int i = s; i < e; i++)
	{
		if (arr[i]->weight <= x->weight)
		{
			index++;
			swapFunct(&arr[i], &arr[index]);
		}
	}
	swapFunct(&arr[e], &arr[index + 1]);

	return index + 1;
}

void quickSort(Edge* arr[], int start, int finish)
{
	if (start < finish)
	{
		int p = Partition(arr, start, finish);
		quickSort(arr, start, p - 1);
		quickSort(arr, p + 1, finish);
	}
}

bool isOk(Edge* e[], int n, int points[2])
{
	for (int i = 0; i < n; i++)
	{
		if ((e[i]->start->key == points[0] && e[i]->end->key == points[1]) || (e[i]->start->key == points[1] && e[i]->end->key == points[0]))
			return false;
	}
	return true;
}

Edge** TestBuildGraph(Node* vertices[], int n)
{
	int* weight = (int*)malloc((2 * n) * sizeof(int));
	Edge** e = (Edge**)malloc((2 * n) * sizeof(Edge*));

	FillRandomArray(weight, 2 * n, 1, 20, true, 0);

	for (int i = 1; i <= n; i++)
	{
		vertices[i] = MakeSet(i);
		if (i == 1)
			continue;
		e[i - 2] = BuildEdge(vertices[i - 1], vertices[i], weight[i - 2]);
	}

	for (int i = n - 1; i < 2 * n; i++)
	{
		int points[2];
		do
		{
			FillRandomArray(points, 2, 1, n, true, 0);
		} while (!isOk(e, i, points));
		e[i] = BuildEdge(vertices[points[0]], vertices[points[1]], weight[i]);
	}

	return e;
}

void printEdge(Edge* e)
{
	printf("\n\t%d, %d, %d", e->start->key, e->end->key, e->weight);
}

void TestKruskal(int n)
{
	Node** vertices = (Node**)malloc((n + 1) * sizeof(Node*));
	Edge** edge = TestBuildGraph(vertices, n);

	quickSort(edge, 0, 2 * n - 1);

	printf("\n\nKruskal Algorithm Test:\n\nvertices are: ");
	for (int i = 1; i <= n; i++)
	{
		printf("%d, ", vertices[i]->key);
	}

	printf("\nedges are: start, end, weight");
	for (int i = 0; i < 2 * n; i++)
	{
		printEdge(edge[i]);
	}

	printf("\nAfter applying Kruskal alg:");
	int cnt = 0;
	int i = 0;
	while (cnt < n - 1)
	{
		if (FindSet(edge[i]->start) != FindSet(edge[i]->end))
		{
			Union(edge[i]->start, edge[i]->end);
			cnt++;
			printEdge(edge[i]);
		}
		i++;
	}
}

Edge** buildGraph(Node* vertices[], int n)
{
	int* weight = (int*)malloc((4 * n) * sizeof(int));
	Edge** e = (Edge**)malloc((4 * n) * sizeof(Edge*));

	FillRandomArray(weight, 4 * n, 10, 100000, true, 0);

	for (int i = 1; i <= n; i++)
	{
		vertices[i] = MakeSet(i);
		if (i == 1)
			continue;
		e[i - 2] = BuildEdge(vertices[i - 1], vertices[i], weight[i - 2]);
	}

	for (int i = n - 1; i < 4 * n; i++)
	{
		int points[2];
		do
		{
			FillRandomArray(points, 2, 1, n, true, 0);
		} while (!isOk(e, i, points));
		e[i] = BuildEdge(vertices[points[0]], vertices[points[1]], weight[i]);
	}

	return e;
}

void Kruskal(int n)
{
	Node** vertices = (Node**)malloc((n + 1) * sizeof(Node*));
	Edge** edge = buildGraph(vertices, n);

	quickSort(edge, 0, 4 * n - 1);

	int cnt = 0;
	int i = 0;
	while (cnt < n - 1)
	{
		if (FindSet(edge[i]->start) != FindSet(edge[i]->end))
		{
			Union(edge[i]->start, edge[i]->end);
			cnt++;
		}
		i++;
	}
}

void performance()
{
	for (int n = 100; n <= 10000; n += 100)
	{
		op = 0;
		Kruskal(n);
		profiler.countOperation("Disjoint Sets Op", n, op);
	}
}

void dumpSets(Node* arr[], int n)
{
	for (int i = 0; i <= n; i++)
	{
		free(arr[i]);
	}
	free(arr);
}

void demo()
{
	Node** demo = (Node**)malloc(11 * sizeof(Node*));
	printf("Disjoint sets: ");
	for (int i = 1; i <= 10; i++)
	{
		demo[i] = MakeSet(i);
		printf("%d, ", demo[i]->key);
	}
	for (int i = 1; i <= 5; i++)
	{
		Union(demo[i], demo[5 + i]);
	}
	printf("\nThe representative: ");
	for (int i = 1; i <= 10; i++)
	{
		Node* aux = FindSet(demo[i]);
		printf("\n\tFor %d: %d ", i, aux->key);
	}
	int kk;
	scanf("kk=%d", &kk);

	dumpSets(demo, 10);
}


int main()
{
	demo();
	int kk;
	scanf("%d", &kk);
	//TestKruskal(5);
	//performance();
	//profiler.showReport();
	_getch();
	return 0;
}
