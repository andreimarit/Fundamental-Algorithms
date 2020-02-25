#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdio.h>

#include "Profiler.h";


#define MAX_INT 10000;

Profiler profiler("Heap");
int DEMO;
int operations_bottom_up;
int operations_top_down;

//BOTTOM-UP
void heapify(int a[], int n, int root)
{

	int big = root;
	int leftChild = 2 * root + 1; 
	int rightChild = 2 * root + 2;

	if (leftChild < n)
	{
		operations_bottom_up++;
		if (a[leftChild] > a[big])	big = leftChild;
	}
	if (rightChild < n)
	{
		operations_bottom_up++;
		if (a[rightChild] > a[big])	big = rightChild;
	}
		
	if (big != root)
	{
		int buff = a[root];
		a[root] = a[big];
		a[big] = buff;
		operations_bottom_up = operations_bottom_up + 3;
		heapify(a, n, big);
	}
}

void build_heap_bottom_up(int a[], int n)
{
	for (int i = (n / 2) -1 ; i >= 0; i--)
	{
		heapify(a, n, i);
	}
}

void heap_sort_BOTTOM_UP(int a[], int n, int n2)
{
	build_heap_bottom_up(a, n2);
	for (int i = n2 - 1; i > 0; i--)
	{
		int buff = a[0];
		a[0] = a[i];
		a[i] = buff;
		//operations_bottom_up = operations_bottom_up + 3;
		n2--;
		heapify(a, n2, 0);
		if (DEMO == 1) {
			for (int j = 0; j < n; j++) printf("%d ", a[j]);
			printf("\n");
		}
	}
	
}

//TOP-DOWN

void swim(int a[], int pos ) {
	int parent;
	while (pos > 0)
	{
		parent = (pos - 1) / 2;
		operations_top_down++;
		if (a[pos] > a[parent])
		{
			int buf = a[pos];
			a[pos] = a[parent];
			a[parent] = buf;
			pos = parent;
			operations_top_down = operations_top_down + 3;
		}
		else
			break;
	}
}


void build_heap_top_down(int a[], int n)
{
	for (int i = 1; i < n; i++)
	{
		swim(a, i);
		if (DEMO == 1)
		{
			for (int j = 0; j < n; j++) printf("%d ", a[j]);
			printf("\n");
		}
	}
	
}

//COMPARING

void average(int maxx_n)
{
	for (int n = 100; n <= maxx_n; n += 100)
	{
		operations_bottom_up = 0;
		operations_top_down = 0;
		for (int i = 0; i <= 4; i++)
		{
			int *a = (int *)malloc(n * sizeof(int));
			int *b = (int *)malloc(n * sizeof(int));
			FillRandomArray(a, n, 0, n, false, 0);
			for (int j = 0; j <= n; j++) b[j] = a[j];
			int n2 = n;
			build_heap_bottom_up(a, n);
			build_heap_top_down(b, n);
		}
		profiler.countOperation("Average_Operations_Bottom-Up", n, operations_bottom_up / 5);
		profiler.countOperation("Average_Operations_Top-Down", n, operations_top_down / 5);
	}
}

void worst(int maxx_n)
{
	for (int n = 100; n <= maxx_n; n += 100)
	{
		operations_bottom_up = 0;
		operations_top_down = 0;
		int *a = (int *)malloc(n * sizeof(int));
		int *b = (int *)malloc(n * sizeof(int));
		FillRandomArray(a, n, 0, n, false, 1);
		//for (int i = 0; i < n; i++) a[i] = i;
		for (int j = 0; j <= n; j++) b[j] = a[j];
		int n2 = n;
		build_heap_bottom_up(a, n);
		build_heap_top_down(b, n);
		profiler.countOperation("Worst_Operations_Bottom-Up", n, operations_bottom_up);
		profiler.countOperation("Worst_Operations_Top-Down", n, operations_top_down);
	}
}



int main()
{

	int maxx_n = MAX_INT;
	//demo
	printf("For demo press 1\n");
	scanf("%d", &DEMO);
	if (DEMO == 1)
	{
	operations_bottom_up = 0;
		/*int n = 20;
		int *a = (int *)malloc(n * sizeof(int));
		int *b = (int *)malloc(n * sizeof(int));
		FillRandomArray(a, n, 0, 10, false, 0);

		*/
	int b[15];
	int a[15] = { 1 , 5, 2, 6, 8, 4, 11, 17, 7, 10 };
		for (int i = 0; i < 10; i++) b[i] = a[i];
		printf("vectorul nesortat\n");
		for (int i = 0; i < 10; i++) printf("%d ", a[i]);
		heap_sort_BOTTOM_UP(a, 10, 10);
		//heap_sort_BOTTOM_UP(a, 10, 10);
		printf("vectorul sortat after Bottom-up\n");
		for (int i = 0; i < 10; i++)	printf("%d ", a[i]);
		printf("\n\nNumarul de operatii= %d", operations_bottom_up);
		printf("\n\nTOP DOWN");

		build_heap_top_down(b, 10);
		//build_heap_top_down(b, 10);
		for (int i = 0; i < 10; i++)	printf("%d ", b[i]);
		printf("\n\nNumarul de operatii= %d", operations_top_down);
		printf("\n\n");
		//print for demo -  need to do
		_getch();
	}
	
	else
	{
		average(maxx_n);
		worst(maxx_n);
		profiler.createGroup("Compare_MethodsA_Average_case", "Average_Operations_Bottom-Up", "Average_Operations_Top-Down");
		profiler.createGroup("Compare _Methods_Worst_case", "Worst_Operations_Bottom-Up", "Worst_Operations_Top-Down");
	    profiler.showReport();
	}
	
	
	return 0;


}

