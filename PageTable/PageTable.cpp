#include"PageTable.h"
#include<iostream>
#include<list>
using namespace std;
PageTable::PageTable()
{

}

PageTable::PageTable(long long _size)
{
	init(_size);
}

PageTable ::~PageTable(){
	if (Table != NULL)
		delete Table;
}

void PageTable::init(long long _size)
{
	PageTable::size = _size;
	PageTable::Table = new long long[size];
	for (int i = 0; i < size; i++)
		Table[i] = -1;
}

void PageTable::setSize(long long _size){
	PageTable::size = _size;
	PageTable::Table = new long long[_size];
	for (int i = 0; i < _size; i++)
		Table[i] = -1;
}
void PageTable::SetFrame(long long index, long long FrameIndex)
{
	if (0 < index &&index< PageTable::size)
		PageTable::Table[index] = FrameIndex;
	else
		cout << "超出范围";
}

long long PageTable::GetFrame(long long index)
{
	if (index >= 0 && index <= size)
		return Table[index];
	return -1;
}

long long PageTable::GetSize()
{
	return size;
}

void PageTable::update(list<long long> & record){
	list<long long>::iterator itor;  //定义迭代器  
	long long k;
	itor = record.begin();
	while (itor != record.end()){
		for (int j = 0; j < size; j++){
			k = -1;
			if (PageTable::GetFrame(j) == *itor){
				
				k = PageTable::GetFrame(j);
				PageTable::Table[j] = -1;
				itor++;
				cout << k;
				record.remove(k);
				break;
			}

		}
		if (k==-1)
		itor++;
		
	}
}

bool PageTable::isVal(long long pn){
	if (Table[pn] != -1)
		return true;
	else
		return false;
}
