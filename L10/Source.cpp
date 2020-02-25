#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Profiler.h"

#define MAX_INT_N 300


int times = 0;
bool topological = false;
Profiler profiler("DFS");

struct Node
{
	int val;
	Node* pNext;
};

Node* heads = NULL;
struct AdjList {
	int f;
	int d;
	int parent;
	int color;
	struct Node *root;  
};

struct Graph {
	int count;
	struct AdjList* array_of_children;
};

Graph* createGraph(int x)
{
	Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
	graph->count = x;
	graph->array_of_children = (struct AdjList*) malloc(x * sizeof(struct AdjList));
	for (int i = 0; i < x; ++i)
		graph->array_of_children[i].root = NULL;
	return graph;
}

Node* newNode(int x)
{
	struct Node* pNode = (struct Node*) malloc(sizeof(struct Node));
	pNode->val = x;
	pNode->pNext = NULL;
	return pNode;
}

void addNode(Node* pHead, int num) {

	if (pHead == NULL)
	{
		pHead = newNode(num);
	}
	else
	{
		Node* pNode = newNode(num);
		pNode->pNext = pHead;
		pHead = pNode;
	}
}

void addEdge(struct Graph* graph, int src, int value)
{
	struct Node* pNode = newNode(value);
	pNode->pNext = graph->array_of_children[src].root;
	graph->array_of_children[src].root = pNode;
}


void DFS_visit(Graph* G, int u) {
	printf("%d ", u);
	G->array_of_children[u].color = 1;
	times++;
	G->array_of_children[u].d = times;
	Node* pVertex = G->array_of_children[u].root;
	while (pVertex != NULL) {
		if (G->array_of_children[pVertex->val].color == 0) {
			G->array_of_children[pVertex->val].parent = u;
			DFS_visit(G, pVertex->val);
		}
		pVertex = pVertex->pNext;
	}
	G->array_of_children[u].color = 2;
	times++;
	G->array_of_children[u].f = times;
}



void DFS(Graph* G) {
	int u;
	for (u = 0; u < G->count; u++) {
		G->array_of_children[u].color = 0;
		G->array_of_children[u].parent = NULL;
	}
	times = 0;
	for (u = 0; u < G->count; u++) {
		
		if (G->array_of_children[u].color == 0) {
			DFS_visit(G, u);
		}
	}
}

void DFS_visit_topo(Graph* G, int u) {
	G->array_of_children[u].color = 1;
	times++;
	G->array_of_children[u].d = times;
	Node* pVertex = G->array_of_children[u].root;
	while (pVertex != NULL) {
		if (G->array_of_children[pVertex->val].color == 0) {
			//topological = false;
			G->array_of_children[pVertex->val].parent = u;
			DFS_visit(G, pVertex->val);
		}
		pVertex = pVertex->pNext;
	}
	G->array_of_children[u].color = 2;
	if (topological) addNode(heads, u);
	times++;
	G->array_of_children[u].f = times;
}



void DFS_topo(Graph* G) {
	int u;
	for (u = 0; u < G->count; u++) {
		G->array_of_children[u].color = 0;
		G->array_of_children[u].parent = NULL;
	}
	times = 0;
	for (u = 0; u < G->count; u++) {

		if (G->array_of_children[u].color == 0) {
			DFS_visit_topo(G, u);
		}
	}
}


void generateEdge(Graph* G, int e) 
{
	srand(time(NULL));
	for (int k = 1; k <= e; k++) {
		int q = rand() % e;
		int p = rand() % e;
		while (q == p) p = rand() % e;
		addEdge(G, p, q);
	}
}

void printGraph(struct Graph* graph) {
	int v;
	for (v = 0; v < graph->count; ++v) {
		struct Node* pNode = graph->array_of_children[v].root;
		printf("\n Adjacency list of %d:", v);
		while (pNode) {
			printf("\n\t->   %d", pNode->val);
			pNode = pNode->pNext;
		}
		printf("\n");
	}
}

void topo(Graph* G) {
	topological = true;
	DFS_topo(G);
	//Node* PACATU = (Node*) malloc(sizeof(Node));
	Node* PACATU = heads;
	printf("\nTopological sort\n");
	while (PACATU) {
		printf(" A ");
		printf("%d ", PACATU->val);
		PACATU = PACATU->pNext;
	}
	printf( "\n");
}

int main()
{
	printf("for demo press 1:");
	int demo;
	scanf("%d", &demo);
	if (demo == 1)
	{
		Node* rootALL = (Node*)malloc(sizeof(Node));
		rootALL->pNext = NULL;

		int V = 6;
		Graph* G = createGraph(V);
		addEdge(G, 0, 1);
		addEdge(G, 1, 2);
		addEdge(G, 2, 3);
		addEdge(G, 2, 5);
		addEdge(G, 5, 3);
		addEdge(G, 1, 4);
		addEdge(G, 0, 4);
		addEdge(G, 2, 0);
		printGraph(G);
		printf("after DFS:\n");
		DFS(G);
		topo(G);
		//printGraph(G);
		_getch();
	}
	
	if (demo == 2)
	{

		int V = 100;
		for (int E = 1000; E < 5000; E += 100) {
			Graph* G = createGraph(V);
			generateEdge(G, E);
			DFS(G);
		}
	}
	if(demo==3)
	{
			int E = 4900;
			for (int V = 100; V <= 200; V += 10){
				Graph* G = createGraph(V);
				generateEdge(G, E);
				DFS(G);
				
			}
	}
	return 0;
}