#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "Profiler.h"
Profiler profiler("BFS");
int oper;

#define NIL NULL
#define INFINIT 99999999
#define MAX_VERTEX 10000
#define MAX_EDGES 40000

struct Node {
	int key;
	int color;
	int distance;
	Node *pred;
};

struct edge {
	int u, v;
};

struct QueueNode {
	Node *v;
	struct QueueNode *next;
};

struct Queue {
	QueueNode *first;
	QueueNode *last;
};

Node **vertices;
edge *edges;
Queue **Adj;


void push(Queue *Q, Node *v)
{
	QueueNode *temp = new QueueNode();
	temp->v = v;
	temp->next = NULL;
	if (Q->first == NULL)
	{
		Q->first = Q->last = temp;
	}
	else
	{
		Q->last->next = temp;
		Q->last = temp;
	}
}

Node* pop(Queue *Q)
{
	QueueNode *temp = Q->first;
	if (temp != NULL)
	{
		Q->first = Q->first->next;
		return temp->v;
	}
	else
		return NULL;
}

void BFS(Node *s, int V, int E)
{
	oper = 0;
		int i;
	for (i = 0; i < V; i++)
	{
		vertices[i]->key = i + 1;
		vertices[i]->color = 0;
		vertices[i]->distance = INFINIT;
		vertices[i]->pred = NIL;
		oper += 4;
	}
	s->color = 1;
	s->distance = 0;
	s->pred = NIL;
	vertices[0] = s;

	Queue *Q = new Queue();
	Q->first = NULL;
	Q->last = NULL;

	push(Q, s);
	Node *u = pop(Q);
	oper += 2;
	Node *v;
	while (u != NULL)
	{
		for (v = pop(Adj[u->key]); v != NULL; v = pop(Adj[u->key]))
		{
				oper += 3;
			if (vertices[v->key - 1]->color == 0)
			{
				vertices[v->key - 1]->color = 1;
				vertices[v->key - 1]->distance = u->distance + 1;
				vertices[v->key - 1]->pred = u;
				push(Q, vertices[v->key - 1]);
					oper += 4;
			}
		}
		u->color = 2;
		printf("Node %d with distance %d\n", u->key, u->distance);
		u = pop(Q);
			oper += 2;
	}
}


bool contains(Queue *Q, int v)
{
	QueueNode *temp = Q->first;
	while (temp != NULL)
	{
		if (temp->v->key == v)
			return true;
		temp = temp->next;
	}
	return false;
}

void generateRandomGraph(int V, int E)
{
	int i;
	for (i = 1; i <= V; i++)
	{
		Adj[i] = new Queue();
		Adj[i]->first = Adj[i]->last = NULL;
	}
	for (i = 1; i <= E; i++)
	{
		edges->u = rand() % V + 1;
		edges->v = rand() % V + 1;
		if (!contains(Adj[edges->u], edges->v)) 
		{
			Node *temp1 = new Node();
			Node *temp2 = new Node();
			temp1->key = edges->v;
			push(Adj[edges->u], temp1);
			temp2->key = edges->u;
			push(Adj[edges->v], temp2);
		}
		else
		{
			--i;
		}
	}
}

void printGraph(int V)
{
	int i;
	for (i = 1; i <= V; i++)
	{
		printf("Node: %d\n", i);
		
		QueueNode *v;
		v = Adj[i]->first;
		while (v != NULL)
		{
			if (i != v->v->key)	printf("%d ", v->v->key);
			v = v->next;
		}
		printf("\n");
	}
}


int main()
{
	int i;
	srand(time(NULL));

	edges = (edge *)malloc(MAX_EDGES * sizeof(edge));
	vertices = (Node **)malloc(MAX_VERTEX * sizeof(Node*));
	Adj = (Queue **)malloc(MAX_VERTEX * sizeof(Queue*));

	Node *s = new Node();
	s->key = 1;

	printf("for demo press 1:/nfor constant V press 2\nfor constant E press 3\n");
	int demo;
	scanf("%d", &demo);
	if (demo == 1)
	{
		for (i = 0; i < 5; i++)
		{
			vertices[i] =(Node*)malloc(sizeof(Node));
		}
		generateRandomGraph(5, 8);
		printGraph(5);
		printf("BFS:\n");
		BFS(s, 5, 8);
		
	}
		int V, E;
		if (demo == 2)
		{
			// V-constant;   E-1000->4950
			V = 100;
			for (E = 1000; E <= 4950; E += 100)
			{
				generateRandomGraph(V, E);
				BFS(s, V, E);
				profiler.countOperation("OpsVset", E, oper);
			}
			profiler.showReport();
		}
		if (demo == 3)
		{
			// V: 100->200;   E-constant
			E = 4900;
			for (V = 100; V <= 200; V += 10)
			{
				generateRandomGraph(V, E);
				BFS(s, V, E);
				profiler.countOperation("OpsEset", V, oper);
			}
			profiler.showReport();
		}
		//profiler.showReport();
		//printf("GATAAAAAA!");
		_getch();
		return 0;
	
}
