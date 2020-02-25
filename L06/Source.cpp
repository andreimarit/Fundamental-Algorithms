#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "Profiler.h"

Profiler profiler("HTable");

int nrOp;

struct Node
{
	int key;
	int size;
	Node* pLeft;
	Node* pRight;
};

Node* buildTree(int arr[], int left, int right)
{
	if (left <= right)
	{
		Node* p = (Node*)malloc(sizeof(Node));
		
		int mid = (left + right) / 2;
		p->key = arr[mid];
		nrOp += 2;
		p->pLeft = buildTree(arr, left, mid - 1);
		p->pRight = buildTree(arr, mid + 1, right);
		if (p->pLeft == NULL && p->pRight == NULL) p->size = 1;
		else if (p->pLeft != NULL && p->pRight == NULL) p->size = p->pLeft->size + 1;
			 else if (p->pLeft == NULL && p->pRight != NULL) p->size = p->pRight->size + 1;
				  else p->size = p->pLeft->size + p->pRight->size + 1;
		return p;
	}
	else return NULL;
}


void afisare_inorder(Node *p, int level)
{
	if (p != NULL)
	{
		afisare_inorder(p->pRight, level + 1);
		printf("%*s(%d, %d)\n", 5*level, " ",p->key, p->size);
		afisare_inorder(p->pLeft, level + 1);
	}
}

Node* os_Select(Node *p, int i)
{
	int r = 1;
	if (p != NULL) {
		if (p->pLeft != NULL)	r = p->pLeft->size + 1;
		//else if (p->pRight != NULL) r = p->pRight->size + 1;
		if (i == r) return p;
		if (i < r) return os_Select(p->pLeft, i);
		return os_Select(p->pRight, i - r);
	}
	return NULL;
}

/* Given a binary search tree and a key, this function deletes the id
   and returns the new root */

Node * minValueNode(Node* p)
{
	Node* current = p;

	while (current->pLeft != NULL)
		current = current->pLeft;

	return current;
}


//this one is from GeekForGeeks
Node* deleteNode(Node* p, int id)
{
	
	nrOp++;
	if (p == NULL) return p;
	nrOp++;
	if (id < p->key)
		p->pLeft = deleteNode(p->pLeft, id);
	else
	{
		nrOp++;
		if (id > p->key)
			p->pRight = deleteNode(p->pRight, id);

		else
		{
			if (p->pLeft == NULL)// && p->pRight != NULL)
			{
				Node *temp = p->pRight;
				free(p);
				return temp;
			}
			else if (p->pRight == NULL)// && p->pLeft != NULL)
			{
				Node *temp = p->pLeft;
				free(p);
				return temp;
			}

			if (p->pRight != NULL && p->pLeft != NULL)
			{
				Node* temp = minValueNode(p->pRight);
				nrOp++;
				p->key = temp->key;

				p->pRight = deleteNode(p->pRight, temp->key);
			}
			//free(p);
		}
	}
	
	if (p->pLeft == NULL && p->pRight == NULL) p->size = 1;
		else if (p->pLeft != NULL && p->pRight == NULL) p->size = p->pLeft->size + 1;
			else if (p->pLeft == NULL && p->pRight != NULL) p->size = p->pRight->size + 1;
				else p->size = p->pLeft->size + p->pRight->size + 1;

	return p;
}

int main()
{
	int n, x;
	int demo;
	printf("For demo press 1:");
	scanf("%d", &demo);
	if (demo == 1)
	{
		printf("\ninsert n=");
		scanf("%d", &n);
		int *a = (int*)malloc(n * sizeof(int));
		FillRandomArray(a, n, 1, n, true, 1);
		Node* tree = buildTree(a, 0, n - 1);
		afisare_inorder(tree, 0);
		printf("\n");
		/*int b[10];
		FillRandomArray(b, 5, 1, n, true, 2);
		for (int i = 0; i < 5; i++) 
		{
			printf("step %d\n", i);
			x = os_Select(tree, b[i])->key;
			printf("\n x=%d \n", x);
			tree = deleteNode(tree, x);
			afisare_inorder(tree, 0);
			printf("\n\n");
		}*/
		int b[3] = { 9, 7, 2 };
		//9 are 2 copii
		//7 are 1 copil
		//2 nu are copil
		for (int i = 0; i < 3; i++) {
			printf("\n\nnodul selectat este:  %d", os_Select(tree, b[i])->key);
			printf("\n");
			int aux = os_Select(tree, b[i])->key;
			deleteNode(tree, aux);
			afisare_inorder(tree, 0);
		}
		_getch();
	}
	else 
	{
		
		for (n = 100; n < 10000; n += 100)
		{
			nrOp = 0;
			int *a = (int*)malloc(n * sizeof(int));
			FillRandomArray(a, n, 1, n, true, 1);
			for (int j = 0; j < 5; j++)
			{
				Node* tree = buildTree(a, 0, n - 1);
				/*int *b = (int*)malloc(n * sizeof(int));
				FillRandomArray(b, n, 1, n, true, 0);
				*/
				int n2 = n;
				while (n2 > 0)
				{
					int PACATU = rand() % (n2) + 1;
					Node* AA = os_Select(tree, PACATU);
					int PACATU2 = AA->key;
					tree = deleteNode(tree, PACATU2);
					n2--;
				}
				//free(b);
				//profiler
			}
			profiler.countOperation("Number of Operations", n, nrOp / 5);

			//free(a);
		}
		//printf("%d", nrOp);
		profiler.showReport();
	}
	_getch();
	return 0;
}