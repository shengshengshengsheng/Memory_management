#ifndef FRAMETABLE_H
#define FRAMETABLE_H
#include"PageTable.h"
#include"TLB.h"
#include <list> 
#define ISVALID char

#define MEMORYSIZE 0x00003FFF   // 64 MB 

#define VALID 0x01
#define INVALID 0x00
using namespace std;
class FrameTable
{
private:
	list<long long> FrameList;
	ISVALID *Table;
	long long length;
	long long ValCount;
	void init(long long _length);
public:
	FrameTable();
	FrameTable(long long _length);
	ISVALID isThisAvaid(long long index);
	void SetThisInvalid(long long index);
	void SetThisValid(long long index);
	long long FindValframe();
	void FreeMemory(PageTable &pt);
	void AllocMemory(PageTable &pt, long long pn, list<long long> & record, TLB &tlb);
	void AllocMemory(long long pn);
	void updateList(long long FrameNum);
};
#endif