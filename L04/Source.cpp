#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "Profiler.h"


Profiler profiler("MergeKLists");
#define MAX_INT 10000;

struct Node {
	int value;
	Node* pNext;
};

struct HeapEl {
	int value;
	int pSource;
};

struct List {
	Node* pFirst;
	Node* pLast;
	int index;
};

void afisare(Node *p)
{
	//Node *p = (Node*)malloc(sizeof(Node));
	//p = pFirst;
	while (p != NULL)
	{
		printf("%d ", p->value);
		p = p->pNext;
	}
	printf("\n");
}

int parent(int i)
{
	if (i > 0)
		return (i - 1) / 2;
	else return i;
}

int left(int i)
{
	return 2 * i + 1;
}

int right(int i)
{
	return 2 * i + 2;
}


void minHeapify(HeapEl* a, int index, int size, int n)
{
	int largest;
	HeapEl aux;
	int l = left(index);
	int r = right(index);
	//profiler.countOperation("bottom-up", n);
	if (l < size && a[l].value < a[index].value)
		largest = l;
	else
		largest = index;
	//profiler.countOperation("bottom-up", n);
	if (r < size && a[r].value < a[largest].value)
		largest = r;
	if (largest != index)
	{
		aux.pSource = a[index].pSource;
		aux.value = a[index].value;
		a[index].value = a[largest].value;
		a[index].pSource = a[largest].pSource;
		a[largest].pSource = aux.pSource;
		a[largest].value = aux.value;
		//profiler.countOperation("bottom-up", n, 3);
		minHeapify(a, largest, size, n);
	}
}




List initList(int i)
{
	List pList;
	//pList = (List)malloc(sizeof(List));
	pList.pFirst = NULL;
	pList.pLast = NULL;
	pList.index = i;
	return pList;
}

void insertAtRear(List* pList, int x)
{
	Node *p = (Node*)malloc(sizeof(Node));
	p->value = x;
	p->pNext = NULL;
	if (pList->pFirst != NULL)
	{
		
		//printf("2");
		pList->pLast->pNext=p;
		pList->pLast = p;
		
		//count 4
	}
	else
	{
		//printf("1");
		pList->pFirst = p;
		pList->pFirst->pNext = pList->pLast;
		pList->pLast = p;
		//count 4;
	}
	//printf("\nval=%d     index=%d", pList->pFirst->value, pList->index);
	//printf("\nval=%d     index=%d", pList->pLast->value, pList->index);
}

void delete_first(List* pList)
{
	if (pList->pFirst != NULL) pList->pFirst = pList->pFirst->pNext;
		
}


void build_list(List* pList, int n_2, int key)
{
	
	int *h = (int*)malloc(n_2 * sizeof(int));
	FillRandomArray(h, n_2, 1, 30, true, 1);
	//printf("\n\n\n");
	//for (int i = 0; i < n; i++) printf("%d ",h[i]);
	*pList = initList(key);
	for (int i = 0; i < n_2; i++)
	{		
		insertAtRear(pList, h[i]);
		//printf("\n\n\HOHOHOHOHO\n");

	}
	afisare(pList->pFirst);
	//printf("\n\n");
	//printf("PUSCA=%d", (*pList).pFirst->value);
}


void build_k_list(List *vList, int n, int k)
{
	int items_in_list = n / k;
	int overN = n % k;
	for (int i = 0; i < k; i++)
	{
		if (overN > 0)
		{
		
			build_list(&vList[i], items_in_list+1, i);
			overN--;
		}
		else {
			build_list(&vList[i], items_in_list, i);
		}
	}
	//printf("\NOOOT=%d\n", vList[0].pFirst->value);
}


void mergeKLists(List* vList, HeapEl* a, int k, int finalList[], int n)
{
	
	int heap_size = k;
	for (int i = 0; i < n; i++)
		{
			finalList[i]= a[0].value;
			
			int auxa = a[0].pSource;
			/*if (i < 2)
			{
				//printf("\n\n2:\n");
				//for (int j = 0; j < k; j++) printf("%d ", a[j].value);

				printf("1:\n%d\n", vList[a[0].pSource].pFirst->value);
			}*/
			//delete_first(&vList[a[0].value]);
			if (vList[a[0].pSource].pFirst != NULL) vList[a[0].pSource].pFirst =vList[a[0].pSource].pFirst->pNext;
			//if (i<2) printf("\nsecond=%d\n", vList[a[0].pSource].pFirst->value);
			if (vList[auxa].pFirst != NULL)
			{
				a[0].value = vList[auxa].pFirst->value;
				minHeapify(a, 0, heap_size, n);
				if (i<0)
				{
					//printf("\n\n2:\n");
					//for (int j = 0; j < k; j++) printf("%d ", a[j].value);
				}
			}
			else
			{
				
				a[0].pSource = a[heap_size - 1].pSource;
				a[0].value = a[heap_size - 1].value;
				heap_size--;
				minHeapify(a, 0, heap_size, n);
			}
			//for (int gggg = 0; gggg < heap_size; gggg++) printf("%d ", a[gggg]);
			//printf("\n");
	}
			
}




void buildMinHeap(HeapEl* a, int n)
{
	for (int i=(n/2);i>=0;i--){
		minHeapify(a, i, n, n);
	}

}

void build_listHeap(HeapEl* b) 
{
	b->value=0;
	b->pSource=0;
	//printf("\nbuildheap\n");
}

int main() { 
	int demo;
	int k, n;
	scanf("%d", &demo);
	if (demo == 1) {
		k = 4;
		n = 22;
	}
	else {
		printf("n=");
		scanf("%d", &n);

		printf("k=");
		scanf("%d", &k);
	}
	HeapEl* a= (HeapEl*)malloc(k*sizeof(HeapEl));
	List *vList = (List*)malloc(n*sizeof(List));
	
	build_k_list(vList, n, k);
	//CREATING HEAP ARRAY
	for (int i = 0; i < k; i++)
	{

		build_listHeap(&a[i]);
		//printf("value=%d  source=%d", a[i].value, a[i].pSource);
		//printf("dasdasda=%d", vList[i].pFirst->value);
		a[i].value = vList[i].pFirst->value;
		a[i].pSource = vList[i].index;
		//printf("\n%d     ", a[i].value);
		//printf("%d\n", a[i].pSource);

	}
	buildMinHeap(a, k);

	
	printf("Min-Heap:\n");
	for (int j = 0; j < k; j++) printf("%d  ", a[j].value);
	
	int finalHeapSize = k;
	int i = 0;
	
	//List* finalList=&initList(i);
	int* finalList = (int*)malloc(n * sizeof(int));
	mergeKLists(vList, a, k, finalList, n);
	printf("\n\nvectorul final:\n");
	for (int i = 0; i < n; i++) printf("%d ", finalList[i]);
	//afisare(finalList->pFirst);
	//for (int i = 0; i < k; i++) afisare(vList[i]->pFirst);
	_getch();
	return 0;
}