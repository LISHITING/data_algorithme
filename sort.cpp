// sort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

void print(const vector<int> &v) {
	for (size_t i = 0; i < v.size(); i++)
		cout << v[i] << " ";
	cout << endl;
}

// Two loop, then O(n^2)
// first loop, set min_index = i
// second loop, loop j and COMPARE [j] and [min_index]
// if violate, then swap
void select_sort(vector<int> &v) {
	for (size_t i = 0; i < v.size(); i++){
		int min_index = i;
		for (size_t j = i; j < v.size(); j++){
			if (v[j]<v[min_index]) 
				swap(v[j], v[min_index]);
		}	
	}
};

// if the next is smaller then itself, than swap
// if increase, j always begin with 0, but stop at size-i-1 
// since the highest must be sorted
void bubble_sort(vector<int> &v) {
	for (size_t i = 0; i < v.size(); i++){
		for (size_t j = 0; j < v.size()-i-1; j++){
			if (v[j] > v[j+1])
				swap(v[j], v[j+1]);
		}
	}
};

// just like sorting the poke card
// find next, and compare each of the preveious
// then find right position to insert
// so for each loop, it has to save the current value and compare all the previous one.
void insert_sort(vector<int> &v) {
	for (size_t i = 1; i < v.size(); i++){
		int j = i - 1; //j is the previous one
		int save = v[i]; //save the current value
		while (j>=0 && v[j]>save) { 
			//comapre all the previous value. 
			//move only if the previous bigger than current save value
			v[j + 1] = v[j];
			j--;
		}
		v[j + 1] = save;
	}
};


void shell_sort(vector<int> &v) {
	int size = v.size();
	for (size_t gap = size/2; gap > 0; gap /=2){ //keep spliting into two part notice 1/2 = 0.5 = 0
		for (size_t i = gap; i < size; i++){
			int temp = v[i];
			int j;
			for (j = i; j>=gap; i++){

			}
		}

	}

};

//merge two array
//remember the middle point is belong to the left part
//first: vec[l.....m]
//second vec[m+1...r]
// http://www.geeksforgeeks.org/merge-sort/
// i j used to loop the leftpart and rightpart
// k is the pointer of the orginial vector
// n1 is the leftpart size
// n2 is the rightpart size
// create 2 temp vec => copy value => compare and override => override the rest
void merge(vector<int> &v, int l, int m, int r) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	vector<int> v_left = vector<int> (n1);
	vector<int> v_right = vector<int>(n2);

	for (i = 0; i < n1; i++)
		v_left[i] = v[l + i];
	for (j = 0; j < n2; j++)
		v_right[j] = v[m + 1 + j];

	i = 0;
	j = 0;
	k = l;

	while (i<n1 && j < n2){
		if (v_left[i] <= v_right[j]) {
			v[k] = v_left[i];
			i++;
		}
		else {
			v[k] = v_right[j];
			j++;
		}
		k++;
	}

	//use while, not if
	//remain leftpart
	while (i < n1) {
		v[k] = v_left[i];
		i++;
		k++;
	}

	//use while, not if
	//remain rightpart
	while (j < n2) {
		v[k] = v_right[j];
		j++;
		k++;
	}
};

void merge_sort_recursive(vector<int> &v, int l, int r) {
	//DO NOT FORGET TO CHECK l AND r
	//OTHERWISE RECURSIVE NOT STOP
	if (l < r){
		//get the middle point
		int m = (l + r) / 2;
		//leftpart = l ~ m
		merge_sort_recursive(v, l, m);
		//rightpart = m+1 ~ r
		merge_sort_recursive(v, m + 1, r);
		merge(v, l, m, r);
	}
};

void merge_sort_iterative(vector<int> &v) {};

// partition function will return a int type which is the partition point index
int partition(vector<int> &v, int low, int high) {
	int pivot = v[high]; //the pivot is the most right value of the array
	int i = (low - 1); //???
	for (int j = low; j < high; j++){
		if (v[j] <= pivot) {
			i++;
			swap(v[i], v[j]);
		}
	}
	swap(v[i + 1], high);
	return (i + 1);

};

void quick_sort_recursive(vector<int> &v, int low, int high) {
	if (low < high) {
		//first get the partition point
		int partition_point = partition(v, low, high);
		cout << "current partition point is:" << partition_point << endl;
		//then call itself with partition point
		quick_sort_recursive(v, low, (partition_point - 1));
		quick_sort_recursive(v, (partition_point + 1), high);
	}
};

void quick_sort_iterative(vector<int> &v) {

};


int main(){
	//vector<int> v = { 3,1,4,5,2,8,11,6};
	vector<int> v = { 10, 7, 8, 9, 1, 5 };
	//select_sort(v);
	//bubble_sort(v);
	//insert_sort(v);
	//merge_sort_recursive(v, 0, 7);
	quick_sort_recursive(v, 0, 6);
	print(v);
    return 0;
}

