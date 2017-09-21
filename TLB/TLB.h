#ifndef TLB_H
#define TLB_H
#include<map>
#include<list>
using namespace std;
class TLB{
private:
	long long size;
	long long valCount;
	list<long long> TLBList;
	map <long long, long long> table;
public:
	TLB();
	TLB(long long _size);
	~TLB();
	void clear();
	void insert(long long pn, long long fn);
	long long getFrame(long long pn);
	void showMap();
};
#endif
