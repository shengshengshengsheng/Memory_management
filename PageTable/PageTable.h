#ifndef PAGETABLE_H
#define PAGETABLE_H
#define PAGESIZE 0x00001FFF  // 8 KB
#include<list>
using namespace std;
class PageTable
{
private:
	long long *Table;
	long long size;
	void init(long long _size);
public:
	PageTable();
	~PageTable();
	PageTable(long long _size);
	void setSize(long long _size);
	void SetFrame(long long index, long long FrameIndex);
	long long GetFrame(long long index);
	long long GetSize();
	bool isVal(long long pn);
	void update(list<long long> & record);
};
#endif