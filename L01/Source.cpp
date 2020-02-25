//bubble sort:
//best: O(n)
//average: O(n^2)
//worst: O(n^2)

//selection
//has O(n^2)

//insertion sort is the best for sorting an array with a few elements...
//best:O(n)
//other: O(n^2)

/*
Insertion sort maintains a sorted sub-array and inserts a new elements into it.
	insertion sort is the best for sorting an array with a few elements...
	best:O(n)
	other: O(n^2)
is a stable sorting algorithm because after sorting, the elements with same value remain in the same order;
in insertion sort we never swap elements, only shif them.
insertion is the fastest algoritgm, efficient and stable..

Bubble sort repetitively compares adjacent pairs of elements and swaps if necessary
is a stable algorithm, but not fast...

Selection sort is to repetitively pick up the smallest element and put it into the right position
is not a stable algorithm, but is faster than bubble sort...
*/


#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdio.h>

#include "Profiler.h";

#define MAX_N 1000

Profiler profiler("three-functions-profiler");

int assignBinary = 0;
int compBinary = 0;
int assign_ins = 0;
int comp_ins = 0;
int assign_bubble = 0;
int assign_sel = 0;
int comp_bubble = 0;
int comp_sel = 0;

int BinarySearch(int a[], int PACATU, int low, int high)
{
	if (high <= low)
	{
		compBinary++;
		if (PACATU > a[low]) return low + 1;
		else return low;
	}

	int mid = (low + high) / 2;
	compBinary++;
	if (PACATU == a[mid])
		return mid + 1;
	compBinary++;
	if (PACATU > a[mid])
		return BinarySearch(a, PACATU, mid + 1, high);
	else
	    return BinarySearch(a, PACATU, low, mid - 1);
}

void BinaryInsertionSort(int a[], int n){
	
	for (int i = 1; i < n; i++)
	{
		int j = i - 1;
		int pos = BinarySearch(a, a[i], 0, j);
		while (j >= pos)
		{
			assignBinary++;
			a[j + 1] = a[j];
			j--;
		}
		assignBinary++;
		a[j + 1] = a[i];
	}	
}

void InsertionSort(int a[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
	int aux = a[i];
	assign_ins++;
	int j = i - 1;

	while (a[j] > aux && j >= 0)
	{
		comp_ins++;
		a[j + 1] = a[j];
		assign_ins++;
		j--;
	}
	comp_ins++;
	a[j + 1] = aux;
	assign_ins++;
}
}

void SelectionSort(int a[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int min_pos = i;
		for (int j = i + 1; j < n; j++)
		{
			comp_sel++;
			if (a[j] < a[min_pos]) min_pos = i;
		}
		//here i have forgot to close the FOR before the swap
		//this is the mistake that i was telling you about
		int buff = a[i];
		a[i] = a[min_pos];
		a[min_pos] = buff;
		assign_sel = assign_sel + 3;
	}
}

void BubbleSort(int a[], int n)
{
	int buff;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			comp_bubble++;
			if (a[j] > a[j + 1])
			{
				buff = a[j + 1];
				a[j + 1] = a[j];
				a[j] = buff;
				assign_bubble = assign_bubble + 3;
			}
		}
	}
}

void best(int maximum)
{
	int n;
	for (n = 100; n < maximum; n += 100)
	{
		int *a = (int *)malloc(n * sizeof(int));
		int *b = (int *)malloc(n * sizeof(int));
		FillRandomArray(a, n, 0, 10000, true, 1);
		for (int i = 0; i < n; i++) b[i] = a[i];//I created another vector to remember the first order of the vector   
		assignBinary = 0;
		compBinary = 0;
		BinaryInsertionSort(a, n);
		profiler.countOperation("Best_BinaryIns_assign", n, assignBinary);
		profiler.countOperation("Best_BinaryIns_comp", n, compBinary);
		
		for (int i = 0; i < n; i++) a[i] = b[i];
		assign_ins = 0;
		comp_ins = 0;
		InsertionSort(a, n);
		profiler.countOperation("Best_ins_assign", n, assign_ins);
		profiler.countOperation("Best_ins_comp", n, comp_ins);
		
		for (int i = 0; i < n; i++) a[i] = b[i];
		assign_bubble = 0;
		comp_bubble = 0;
		BubbleSort(a, n);
		profiler.countOperation("Best_Bubble_assign", n, assign_bubble);
		profiler.countOperation("Best_Bubble_comp", n, comp_bubble);

		for (int i = 0; i < n; i++) a[i] = b[i];
		assign_sel = 0;
		comp_sel = 0;
		SelectionSort(a, n);
		profiler.countOperation("Best_sel_assign", n, assign_sel);
		profiler.countOperation("Best_sel_comp", n, comp_sel);

	}
	profiler.addSeries("Best_BinaryIns_ac", "Best_BinaryIns_assign", "Best_BinaryIns_comp");
	profiler.addSeries("Best_ins_ac", "Best_ins_assign", "Best_ins_comp");
	profiler.addSeries("Best_Bubble_ac", "Best_Bubble_assign", "Best_Bubble_comp");
	profiler.addSeries("Best_sel_ac", "Best_sel_assign", "Best_sel_comp");
}

void average(int maximum)
{
	int n;
	for (n = 100; n < maximum; n += 100)
	{
		assignBinary = 0;
		compBinary = 0;
		assign_ins = 0;
		comp_ins = 0;
		assign_bubble = 0;
		assign_sel = 0;
		comp_bubble = 0;
		comp_sel = 0;
		for (int i = 0; i <= 4; i++) {
			int *a = (int *)malloc(n * sizeof(int));
			int *b = (int *)malloc(n * sizeof(int));
			FillRandomArray(a, n, 0, 10000, true, 0);
			
			for (int j = 0; j < n; j++) b[j] = a[j];

			BinaryInsertionSort(a, n);
			
			for (int j = 0; j < n; j++) a[j] = b[j];
			InsertionSort(a, n);
			
			for (int j = 0; j < n; j++) a[j] = b[j];
			BubbleSort(a, n);
			
			for (int j = 0; j < n; j++) a[j] = b[j];
			SelectionSort(a, n);
			
			
		}
		profiler.countOperation("Average_BinaryIns_assign", n, assignBinary / 5);
		profiler.countOperation("Average_BinaryIns_comp", n, compBinary / 5);
		profiler.countOperation("Average_ins_assign", n, assign_ins / 5);
		profiler.countOperation("Average_ins_comp", n, comp_ins / 5);
		profiler.countOperation("Average_Bubble_assign", n, assign_bubble / 5);
		profiler.countOperation("Average_Bubble_comp", n, comp_bubble / 5);
		profiler.countOperation("Average_sel_assign", n, assign_sel / 5);
		profiler.countOperation("Average_sel_comp", n, comp_sel / 5);
	}
	profiler.addSeries("Average_BinaryIns_ac", "Average_BinaryIns_assign", "Average_BinaryIns_comp");
	profiler.addSeries("Average_ins_ac", "Average_ins_assign", "Average_ins_comp");
	profiler.addSeries("Average_Bubble_ac", "Average_Bubble_assign", "Average_Bubble_comp");
	profiler.addSeries("Average_sel_ac", "Average_sel_assign", "Average_sel_comp");
}

void worst(int maximum)
{
	int n;
	for (n = 100; n < maximum; n += 100)
	{
		int *a = (int *)malloc(n * sizeof(int));
		int *b = (int *)malloc(n * sizeof(int));

		FillRandomArray(a, n, 0, 10000, true, 2);
		for (int i = 0; i < n; i++) b[i] = a[i];
		assignBinary = 0;
		compBinary = 0;
		BinaryInsertionSort(a, n);
		profiler.countOperation("Worst_BinaryIns_assign", n, assignBinary);
		profiler.countOperation("Worst_BinaryIns_comp", n, compBinary);
		
		for (int i = 0; i < n; i++) a[i] = b[i];
		assign_ins = 0;
		comp_ins = 0;
		InsertionSort(a, n);
		profiler.countOperation("Worst_ins_assign", n, assign_ins);
		profiler.countOperation("Worst_ins_comp", n, comp_ins);

		for (int i = 0; i < n; i++) a[i] = b[i];
		assign_bubble = 0;
		comp_bubble = 0;
		BubbleSort(a, n);
		profiler.countOperation("Worst_Bubble_assign", n, assign_bubble);
		profiler.countOperation("Worst_Bubble_comp", n, comp_bubble);
		
		for (int i = 0; i < n; i++) a[i] = b[i];
		assign_sel = 0;
		comp_sel = 0;
		SelectionSort(a, n);
		profiler.countOperation("Worst_sel_assign", n, assign_sel);
		profiler.countOperation("Worst_sel_comp", n, comp_sel);
	}
	profiler.addSeries("Worst_BinaryIns_ac", "Worst_BinaryIns_assign", "Worst_BinaryIns_comp");
	profiler.addSeries("Worst_ins_ac", "Worst_ins_assign", "Worst_ins_comp");
	profiler.addSeries("Worst_Bubble_ac", "Worst_Bubble_assign", "Worst_Bubble_comp");
	profiler.addSeries("Worst_sel_ac", "Worst_sel_assign", "Worst_sel_comp");

}

int main() {
	   //test
/*	int a[10] = { 1, 5, 9, 3, 6, 11, 4 };
	int n = 7;
	InsertionSort(a, n, assign, comp);
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	_getch();*/
	
	
	
	best(MAX_N);
	
	profiler.createGroup("Best_BinaryInsertion_Graph", "Best_BinaryIns_ac", "Best_BinaryIns_assign", "Best_BinaryIns_comp");
	profiler.createGroup("Best_Insertion_Graph", "Best_ins_ac", "Best_ins_assign", "Best_ins_comp");// pentru combinare de linii pe grafic
	profiler.createGroup("Best_BubbleSort_Graph", "Best_Bubble_ac", "Best_Bubble_assign", "Best_Bubble_comp");
	profiler.createGroup("Best_Selection_Graph", "Best_sel_ac", "Best_sel_assign", "Best_sel_comp");
	

	worst(MAX_N);
	
	profiler.createGroup("Worst_BinaryInsertion_Graph", "Worst_BinaryIns_ac", "Worst_BinaryIns_assign", "Worst_BinaryIns_comp");
	profiler.createGroup("Worst_Insertion_Graph", "Worst_ins_ac", "Worst_ins_assign", "Worst_ins_comp");
	profiler.createGroup("Worst_BubbleSort_Graph", "Worst_Bubble_ac", "Worst_Bubble_assign", "Worst_Bubble_comp");
	profiler.createGroup("Worst_Selection_Graph", "Worst_sel_ac", "Worst_sel_assign", "Worst_sel_comp");
	

	average(MAX_N);
	
	profiler.createGroup("Average_BinaryInsertion_Graph", "Average_BinaryIns_ac", "Average_BinaryIns_assign", "Average_BinaryIns_comp");
	profiler.createGroup("Average_Insertion_Graph", "Average_ins_ac", "Average_ins_assign", "Average_ins_comp");
	profiler.createGroup("Average_BubbleSort_Graph", "Average_Bubble_ac", "Average_Bubble_assign", "Average_Bubble_comp");
	profiler.createGroup("Average_Selection_Graph", "Average_sel_ac", "Average_sel_assign", "Average_sel_comp");
	
	
	profiler.createGroup("ALL_BinaryInsertion_Assign_Graph", "Best_BinaryIns_assign", "Worst_BinaryIns_assign", "Average_BinaryIns_assign");
	profiler.createGroup("ALL_BinaryInsertion_Comp_Graph", "Best_BinaryIns_comp", "Worst_BinaryIns_comp", "Average_BinaryIns_comp");
	profiler.createGroup("ALL_BinaryInsertion_Assign&Comp_Graph", "Best_BinaryIns_ac", "Worst_BinaryIns_ac", "Average_BinaryIns_ac");
	
	profiler.createGroup("ALL_Insertion_Assign_Graph", "Best_ins_assign", "Worst_ins_assign", "Average_ins_assign");
	profiler.createGroup("ALL_Insertion_Comp_Graph", "Best_ins_comp", "Worst_ins_comp", "Average_ins_comp");
	profiler.createGroup("ALL_Insertion_Assign&Comp_Graph", "Best_ins_ac", "Worst_ins_ac","Average_ins_ac");
	
	profiler.createGroup("ALL_BubbleSort_Assign_Graph", "Best_Bubble_assign", "Worst_Bubble_assign", "Average_Bubble_assign");
	profiler.createGroup("ALL_BubbleSort_Comp_Graph", "Best_Bubble_comp", "Worst_Bubble_comp", "Average_Bubble_comp");
	profiler.createGroup("ALL_BubbleSort_Assign&Comp_Graph", "Best_Bubble_ac", "Worst_Bubble_ac", "Average_Bubble_ac");

	profiler.createGroup("ALL_Selection_Assign_Graph", "Best_sel_assign", "Worst_sel_assign", "Average_sel_assign");
	profiler.createGroup("ALL_Selection_Comp_Graph", "Best_sel_comp", "Worst_sel_comp", "Average_sel_comp");
	profiler.createGroup("ALL_Selection_Assign&Comp_Graph", "Best_sel_ac", "Worst_sel_ac","Average_sel_ac");
	
	//for comparation
	profiler.createGroup("Compare_Best_of_all_ac", "Best_ins_ac", "Best_sel_ac", "Best_Bubble_ac");
	profiler.createGroup("Compare_Average_of_all_ac", "Average_ins_ac", "Average_sel_ac", "Average_Bubble_ac");
	profiler.createGroup("Compare_Worst_of_all_ac", "Worst_ins_ac", "Worst_sel_ac", "Worst_Bubble_ac");
	
	profiler.createGroup("Compare_Best_of_all_assign", "Best_ins_assign", "Best_sel_assign", "Best_Bubble_assign");
	profiler.createGroup("Compare_Average_of_all_assign", "Average_ins_assign", "Average_sel_assign", "Average_Bubble_assign");
	profiler.createGroup("Compare_Worst_of_all_assign", "Worst_ins_assign", "Worst_sel_assign", "Worst_Bubble_assign");

	profiler.createGroup("Compare_Best_of_all_comp", "Best_ins_comp", "Best_sel_comp", "Best_Bubble_comp");
	profiler.createGroup("Compare_Average_of_all_comp", "Average_ins_comp", "Average_sel_comp", "Average_Bubble_comp");
	profiler.createGroup("Compare_Worst_of_all_comp", "Worst_ins_comp", "Worst_sel_comp", "Worst_Bubble_comp");

	//linear vs binary
	profiler.createGroup("Compare_Best_linear_vs_binary_insertion", "Best_ins_ac", "Best_BinaryIns_ac");
	profiler.createGroup("Compare_Average_linear_vs_binary_insertion", "Average_ins_ac", "Average_BinaryIns_ac");
	profiler.createGroup("Compare_Worst_linear_vs_binary_insertion", "Worst_ins_ac", "Worst_BinaryIns_ac");

	profiler.showReport();
	
	return 0;
}