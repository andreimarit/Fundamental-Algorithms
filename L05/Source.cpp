#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "Profiler.h"

Profiler profiler("HTable");

#define MAX__N_INT 10007

#define c1 1
#define c2 2

float countF;
float countN;
int count;

struct Table
{
	int id;
	char name[30];
} hTable;

int hash_function(int a, int i, int size)//retureaza pozitia unde va fii pus
{
		int h = a + c1*i + c2*i*i;
		int f = h % size;
		return f;
}


int hash_insert(Table hTable[], int size, int k)
{
	int i = 0, j;
	do
	{
		j = hash_function(k, i, size);
		if (strcmp(hTable[j].name, "NULL")==0)
		{
			hTable[j].id = k;
			strcpy(hTable[j].name, "busy");
			return j;
		}
		else i++;
	} while (i < size);// || strcmp(hTable[j].name, "NULL") != 0);
	/*if (i == size) 
	{
		i = 0;
		while (strcmp(hTable[i].name, "NULL") != 0) i++;
		hTable[i].id = k;
		strcpy(hTable[i].name, "busy");
		return i;
	}*/
	return -1;
}


int hash_search(Table hTable[], int size, int key, int n)
{
	int i = 0, j; 
	do
	{
		j = hash_function(key, i, size);
		countF++;
		if (hTable[j].id == key)
		{
			count = i + 1;
			return j;
		}
		i++;
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		
	}while (i < size || strcmp(hTable[j].name, "NULL") != 0);
	return -1;
}

int hash_search_not_found(Table hTable[], int size, int key, int n)
{
	int i = 0, j;
	do
	{
		j = hash_function(key, i, size);
		countN++;
		count = i + 1;
		if (hTable[j].id == key)
		{
			return j;
		}
		i++;
		
	} while (i < size || strcmp(hTable[j].name, "NULL") != 0);
	return -1;
}



int main()
{
	printf("for DEMO press 1:");
	int demo;
	scanf("%d", &demo);
	if (demo == 1)
	{
		int sizeHTable;
		printf("\nNOT GREATER THAN 40!\nSize of HTable=");
		scanf("%d", &sizeHTable);
		float FillingFactor;
		printf("\nFilling Factor=");
		scanf("%f", &FillingFactor);
		int n = floor(sizeHTable*FillingFactor);//never greater than SizeHTable
		Table* hTable = (Table*)malloc(sizeHTable * sizeof(Table));
		for (int i = 0; i < sizeHTable; i++)
		{
			hTable[i].id = 0;
			strcpy(hTable[i].name, "NULL");
		}


		int *a = (int *)malloc(n * sizeof(int));
		FillRandomArray(a, n, 1, 50, true, 0);
		printf("\n");
		for (int i = 0; i < n; i++)
		{
			printf("%d ", a[i]);
			hash_insert(hTable, sizeHTable, a[i]);
		}
		printf("\n");

		int i = 0;
		while (i < sizeHTable)
		{
			printf("\nid=%d     name=%s", hTable[i].id, hTable[i].name);
			i++;
		}
		printf("\n-------------------------------\n");
		int x;
		printf("\nElementul cautat este:");
		scanf("%d", &x);
		int pos = hash_search(hTable, sizeHTable, x, n);
		if (pos == -1)
			printf("NU EXISTA!\n");
		else printf("Elementul cautat se afla pe pozitia %d\n", pos);

		_getch();
		return 0;
	}
	else
	{
		float maxii = INT_MIN;
		float maxii2 = INT_MIN;
		
		int sizeHTable = MAX__N_INT;
		float FF[] = { 0.8, 0.85, 0.9, 0.95, 0.99 };
		Table* hTable = (Table*)malloc(sizeHTable * sizeof(Table));
		printf("Filling |\tAVG Effort |\t Max Effort |\t AVG Effort |\t Max Effort \n");
		printf(" factor |\t   found   |\t    found   |\t  not-found |\t  not-found  \n");
		printf("-------------------------------------------------------------------------\n");

		for (int i = 0; i < 5; i++)
		{
			int n = floor(sizeHTable*FF[i]);
			
			for (int i2 = 0; i2 < sizeHTable; i2++)
			{
				hTable[i2].id = 0;
				strcpy(hTable[i2].name, "NULL");
			}

			int *a = (int *)malloc(n * sizeof(int));
			FillRandomArray(a, n, 1, 50000, true, 0);

			for (int i3 = 0; i3 < n; i3++)
				hash_insert(hTable, sizeHTable, a[i3]);
			
			for (int jj =0; jj<5;  jj++) 
			{
				int *b = (int *)malloc(1501 * sizeof(int));
				FillRandomArray(b, 1500, 1, n - 1, true, 0);

				int *c = (int *)malloc(1500 * sizeof(int));
				FillRandomArray(c, 1500, 50001, 100002, true, 0);



				for (int j = 0; j < 1500; j++)
				{
				hash_search(hTable, sizeHTable, a[b[j]], n);
				//countALL = countALL + count;

				if (maxii < count) maxii = count;
				
				count = 0;
				hash_search_not_found(hTable, sizeHTable, c[j], n);
				if (maxii2 < count) maxii2 = count;
				}
			}
			countF = countF / 7500;
			countN = countN / 7500;
			printf(" %f |\t %f|\t %f |\t%f|\t%f\n", FF[i], countF, maxii, countN, maxii2);

		}
	_getch();
	return 0;
	}
return 0;
}