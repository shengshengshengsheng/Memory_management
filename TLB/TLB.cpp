#include"TLB.h"
#include<iostream>
using namespace std;
//实现TLB.cpp
TLB::TLB(){
	size = 16;
	valCount = 16;
}

TLB::TLB(long long _size){
	size = _size;
	valCount = _size;
}

TLB::~TLB(){
	
}

void TLB::clear(){
	table.clear();
	valCount = size;
	TLBList.clear();
}


void TLB::insert(long long pn, long long fn){
	if (valCount > 0){
		table.insert(map<long long, long long> ::value_type(pn, fn));
		TLBList.push_back(pn);
		valCount--;
	}
	else{
		table.erase(TLBList.front());
		TLBList.pop_front();
		table.insert(map<long long, long long> ::value_type(pn, fn));
		TLBList.push_back(pn);
	}
}

long long TLB::getFrame(long long pn){
	map<long long, long long>::iterator iter;
	iter = table.find(pn);
	if(iter != table.end()){
		
		TLBList.remove(pn);
		TLBList.push_back(pn);
		return iter->second;
	}
	else{
		return -1;
	}
}

void TLB::showMap(){
	

	map<long long, long long>::reverse_iterator iter;

	for (iter = table.rbegin(); iter != table.rend(); iter++)

		cout << iter->first << "  " << iter->second << endl;

	list<long long>::iterator it;
	for (it = TLBList.begin(); it != TLBList.end(); it++)
	{
		long long tem = *it;
		printf("rr = %d \n", tem);
	}
}
