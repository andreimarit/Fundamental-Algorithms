#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdio.h>
#include <iostream>

#include "Profiler.h";

#define MAX_INT 10000;

int operations_heap;
int operations_quicksort;
int DEMO;

Profiler profiler("Quick");

//QUICK SORT
int partition_quicksort(int a[], int low, int high)
{
	int pivot = a[high];
	operations_quicksort++;
	int i = low;
	for (int j = low; j < high; j++)
	{
		operations_quicksort++;
		if (a[j]< pivot)
		{
			if (i != j) 
			{
				int buf = a[i];
				a[i] = a[j];
				a[j] = buf;
				operations_quicksort = operations_quicksort + 3;
			}
			i = i + 1;
		}
	}
	int buf2 = a[i];
	a[i] = a[high];
	a[high] = buf2;
	operations_quicksort = operations_quicksort + 3;
	return i;
}

void  quicksort(int a[], int low, int high, int n)
{
	if (low < high)
	{
		
		int pos = partition_quicksort(a, low, high);
		if (DEMO == 1)
		{
			for (int i = 0; i < n; i++) printf("%d ", a[i]);
			printf("\n");
		}
		quicksort(a, low, pos - 1, n);
		quicksort(a, pos + 1, high, n);
	}
}

int partition_quicksort_best(int a[], int low, int high)
{
	int pivot = a[(high + low) / 2];
	operations_quicksort++;
	int i = low;
	for (int j = low; j < high; j++)
	{
		operations_quicksort++;
		if (a[j] < pivot)
		{
			if (i != j)
			{
				int buf = a[i];
				a[i] = a[j];
				a[j] = buf;
				operations_quicksort = operations_quicksort + 3;
			}
			i = i + 1;
		}
	}
	int buf2 = a[i];
	a[i] = a[high];
	a[high] = buf2;
	operations_quicksort = operations_quicksort + 3;
	return i;
}


void  quicksort_best(int a[], int low, int high)
{
	if (low < high)
	{
		/*int buf3 = a[high - low + 1];
		a[high - low + 1] = a[high];
		a[high] = buf3;*/
		//operations_quicksort = operations_quicksort + 3;
		int pos = partition_quicksort_best(a, low, high);
		quicksort_best(a, low, pos - 1);
		quicksort_best(a, pos + 1, high);
	}
}

//QUICKSELECT

int partition_quickselect(int a[], int left, int right, int pivotIndex)
{
	int pivot = a[pivotIndex];
	int buf = a[pivotIndex];
	a[pivotIndex] = a[right];
	a[right] = buf;
	int storeIndex = left;
	for (int i=left; i<right; i++)
		if(a[i]< pivot)
		{
			int buf2 = a[storeIndex];
			a[storeIndex] = a[i];
			a[i] = buf2;
			storeIndex++;
		}
	int buf3 = a[right];
	a[right] = a[storeIndex];
	a[storeIndex] = buf3;
	return storeIndex;
}


int quickselect(int a[], int left, int right, int k)
{
	if (left == right) return a[left];
	int pivotIndex = left + rand() % (right - left + 1);
	pivotIndex = partition_quickselect(a, left, right, pivotIndex);
	if (k == pivotIndex) return a[k];
	else if (k < pivotIndex) return quickselect(a, left, pivotIndex - 1, k);
	else return quickselect(a, pivotIndex + 1, right, k);
}

//HEAPSORT
void heapify(int a[], int n, int root)
{

	int big = root;
	int leftChild = 2 * root + 1;
	int rightChild = 2 * root + 2;

	if (leftChild < n)
	{
		operations_heap++;
		if (a[leftChild] > a[big])	big = leftChild;
	}
	if (rightChild < n)
	{
		operations_heap++;
		if (a[rightChild] > a[big])	big = rightChild;
	}

	if (big != root)
	{
		int buff = a[root];
		a[root] = a[big];
		a[big] = buff;
		operations_heap = operations_heap + 3;
		heapify(a, n, big);
	}
}

void build_heap_bottom_up(int a[], int n)
{
	for (int i = (n / 2) - 1; i >= 0; i--)
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
		operations_heap = operations_heap + 3;//!!!!!!!!!!!!!!!!!!!!!!!!
		n2--;
		heapify(a, n2, 0);
		/*if (DEMO == 1) {
			for (int j = 0; j < n; j++) printf("%d ", a[j]);
			printf("\n");
		}*/
	}

}

void average(int maxx_n)
{
	for (int n = 100; n <= maxx_n; n += 100)
	{
		operations_heap = 0;
		operations_quicksort = 0;
		for (int i = 0; i <= 4; i++)
		{
			int *a = (int *)malloc(n * sizeof(int));
			int *b = (int *)malloc(n * sizeof(int));
			FillRandomArray(a, n, 0, n, false, 0);
			for (int j = 0; j <= n; j++) b[j] = a[j];
			int n2 = n;
			heap_sort_BOTTOM_UP(a, n, n);
			quicksort(b, 0, n2 - 1, n);
		}
		profiler.countOperation("Average_Operations_Heap", n, operations_heap / 5);
		profiler.countOperation("Average_Operations_Quick-Sort", n, operations_quicksort / 5);
	}
}

void worst(int maxx_n)
{
	for (int n = 100; n <= maxx_n; n += 100)
	{
		operations_quicksort = 0;
		int *a = (int *)malloc(n * sizeof(int));
		FillRandomArray(a, n, 0, n, true, 2);
		quicksort(a, 0, n-1, n);
		profiler.countOperation("Worst_Operations_Quick-Sort", n, operations_quicksort);
	}
}

void best(int maxx_n)
{
	for (int n = 100; n <= maxx_n; n += 100)
	{
		operations_quicksort = 0;
		int *a = (int *)malloc(n * sizeof(int));
		FillRandomArray(a, n, 0, n, true, 1);
		quicksort_best(a, 0, n-1);
		profiler.countOperation("Best_Operations_Quick-Sort", n, operations_quicksort);
	}
}


int main() 
{

	int maxx_n = MAX_INT;
	//demo
	printf("For demo press 1\n");
	scanf("%d", &DEMO);
	printf("\n\n\n");
	if (DEMO == 1)
	{
		int a[15] = { 1, 10, 5, 3, 7, 2, 9, 4, 6, 8 };
		int b[15];
		for (int i = 0; i < 10; i++) b[i] = a[i];
		int value_select = quickselect(b, 0, 9, 5);
		printf("pozitia=%d \n\n\n", value_select);
		quicksort(a, 0, 9, 9);
		for (int i = 0; i < 10; i++) printf("%d ", a[i]);
		_getch();
		return 0;
	}
	else
	{
		average(maxx_n);
		profiler.createGroup("Compare_MethodsA_Average_case", "Average_Operations_Heap", "Average_Operations_Quick-Sort");
		worst(maxx_n);
		best(maxx_n);
		profiler.createGroup("Quick_Sort", "Worst_Operations_Quick-Sort" , "Average_Operations_Quick-Sort", "Best_Operations_Quick-Sort");
		profiler.showReport();
		return 0;

	}
}
