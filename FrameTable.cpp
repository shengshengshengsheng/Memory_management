#include"FrameTable.h"
#include<iostream>
using namespace std;
FrameTable::FrameTable()
{
	init(MEMORYSIZE);
}

FrameTable::FrameTable(long long _length)
{
	init(_length);
}

void FrameTable::init(long long _length)
{
	FrameTable::length = _length;
	Table = new ISVALID[_length];
	for (int i = 0; i< _length; i++)
		FrameTable::Table[i] = VALID;
	FrameTable::ValCount = length;
}

ISVALID FrameTable::isThisAvaid(long long index)
{
	return FrameTable::Table[index];
}

void FrameTable::SetThisValid(long long index)
{
	if (Table[index] != VALID)
	{
		Table[index] = VALID;
		ValCount++;
	}
}

void FrameTable::SetThisInvalid(long long index)
{
	if (Table[index] != INVALID)
	{
		Table[index] = INVALID;
		ValCount--;
	}
}

long long FrameTable::FindValframe()
{
	if (ValCount >0)
	for (int i = 0; i < length; i++)
	{
		if (Table[i] == VALID)
			return i;
	}
	else
		throw 1;
	return -1;
}

void FrameTable::FreeMemory(PageTable &pt)
{
	for (int i = 0; i<pt.GetSize(); i++)
	{
		FrameTable::SetThisValid(pt.GetFrame(i));
	}

}

void FrameTable::AllocMemory(PageTable &pt, long long pn, list<long long> &record, TLB &tlb)
{
	try
	{
		
			pt.SetFrame(pn, FrameTable::FindValframe());
			tlb.insert(pn, FrameTable::FindValframe());
			FrameTable::FrameList.push_back(FrameTable::FindValframe());
			SetThisInvalid(FrameTable::FindValframe());
			
	}
	catch (int)
	{
		long long FrameNum = *FrameList.begin();
		FrameTable::FrameList.pop_front();
		pt.SetFrame(pn, FrameNum);
		tlb.insert(pn, FrameNum);
		FrameTable::FrameList.push_back(FrameNum);
		record.push_back(FrameNum);
	}
}

void FrameTable::updateList(long long FrameNum){
	FrameList.remove(FrameNum);
	FrameList.push_back(FrameNum);
}