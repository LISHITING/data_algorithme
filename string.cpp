// string.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int sequence_search(string a, string b) {
	bool found = false;
	for (size_t i = 0; i < a.size(); i++){
		int k = i;   
		for (size_t j = 0; j < b.size(); j++){
			if (a[k] == b[j]) {
				cout << "k:" << k << "j:" << j << endl;
				found = true;
				k++;
			}
			else {
				found = false;
				break; //once found the error, end up this loop
			}
		}
		if (found)
			return i;
	}
	return -1;
}

//PMT: partitial matched table.
//PMV: partitial matched value: get from the PMT
//movestep = words already matched - the PMV of the one before mismatch 
//eg: patterm: ABCD, text ABCC.
//the [3] is mismatched, so get the PMV of [2]
//because has already mathc ABC, so words already matched = 3
//calculate the movestep = 3 - PMV[3]
//new pointer = pointer + movestep

void pmt_builder(vector<int> &PMT, string b) {
	//dont know how to build a PMT from a pattern b in O(n)
	PMT = { 0,0,1,2,0,1,2,3,4 };
}

void pmt_builder2(vector<int> &PMT, string b) {
	PMT[0] = 0;
	int i = 1;
	int len = 0;
	while (i < b.size()) {
		if (b[i] == b[len]){
			len++;
			PMT[i] = len;
			i++;
		}
		else {
			if (len != 0){
				len = PMT[len - 1];
			}
			else {
				PMT[i] = 0;
				i++;
			}	
		}
	}
}

int kmp_search2(string a, string b) {
	int i = 0;
	int j = 0;
	vector<int> PMT(b.size());
	pmt_builder2(PMT, b);

	while (i<a.size()){
		if (a[i] = b[j])
			i++; j++;
		if (j == b.size())
			return i - j;
		else if(i < a.size() && a[i] != b[j] ){ //if i is not over and mismatch occur
			if (j != 0) 
				j = PMT[j - 1]; //if we have more than 0 element satisified
			else 
				i = i + 1; //if even the first element is not equal, just move one more step
		}
	}
}

int kmp_search(string a, string b) {
	
	bool found = false;
	vector<int> PMT(b.size());
	pmt_builder(PMT, b);
	int movestep;
	
	int i = 0;
	int k = 0;
	while (i < a.size()) {
		k = i;
		for (size_t j = 0; j < b.size(); j++) {
			if (a[k] == b[j]) {
				cout << "k:" << k << "j:" << j << endl;
				found = true;
				k++;
			}
			else {
				found = false;
				//the previous one is j-1
				//check the PMT, get the PMV of j-1
				//set the movestep = (j-1) + PMT[j-1]
				// TWO CONDITION: 
				// 1) the first one is alreadt mismatch, then just move 1
				// 2) we matched more than 0,then it should calculate the movestep by PMT
				cout << "FALSE"<<"k:" << k << "j:" << j << endl;
				if (j == 0)
					movestep = 1;
				else 
					movestep = (j - 1) + PMT[j - 1];
				cout << "movestep: " << movestep << endl;
				break; //once found the error, end up this loop
			}
		}
		if (found)
			return i;
		else {
			i = i + movestep;
			cout << "new i:" << i << endl;
		}			
	}
	return -1;
}

int main()
{
	string a = "ABABDABACDABABCABAB";
	string b = "ABABCABAB";
	//cout << sequence_search(a, b) << endl;
	//cout << kmp_search(a, b) << endl;
	cout << kmp_search(a, b) << endl;
	//cout << endl;
	//vector<int> PMTtest(9);
	//pmt_builder2(PMTtest, b);


	return 0;
}

