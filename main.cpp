#include<iostream>
#include"FrameTable.h"
#include"PageTable.h"
#include"TLB.h"
#include <list> 
#include <stdlib.h> 
#include <time.h>  
#include <stdio.h>
#include <iostream> 
#include <fstream>
#include<string>
using namespace std;
//main函数的实现
long long*  random(long long size);

int main(){

	PageTable* page = new PageTable[5]();
	page[0].setSize(128);
	page[1].setSize(4096);
	page[2].setSize(8192);
	page[3].setSize(16384);
	page[4].setSize(32768);//五个同时运行的进程
	int tlbCount[5] = { 0, 0, 0, 0, 0 };//tlb counter
	int pageCount[5] = { 0, 0, 0, 0, 0 };//page counter
	long long* addr;
	list<long long> record;
	TLB tlb;
	ofstream out;
	FrameTable* Frame = new FrameTable();
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 5; j++){
			tlb.clear();
			page[j].update(record);
			if (j == 0){
				addr = random(1024 * 1024);
				
				out.open("addr_seq_0.txt", ios::app);
				//freopen("0addr.txt", "w", stdout);
				out << "第"<<i<<"次"<< "地址：";
				for (int i = 0; i < 500; i++){
					out << i << ":" << addr[i] << endl;
				}
				out.close();
			}
			else if (j == 1){
				addr = random(32 * 1024 * 1024);
				
				out.open("addr_seq_1.txt", ios::app);
				//freopen("0addr.txt", "w", stdout);
				out << "地址：";
				for (int i = 500; i < 1000; i++){
					out << i - 500 << ":" << addr[i] << endl;
				}
				out.close();
			}
			else if (j == 2){
				addr = random(64 * 1024 * 1024);
				
				out.open("addr_seq_2.txt", ios::app);
				//freopen("0addr.txt", "w", stdout);
				out << "地址：";
				for (int i = 500; i < 1000; i++){
					out << i - 500 << ":" << addr[i] << endl;
				}
				out.close();
			}
			else if (j == 3){
				addr = random(128 * 1024 * 1024);
				
				out.open("addr_seq_3.txt", ios::app);
				//freopen("0addr.txt", "w", stdout);
				out << "地址：";
				for (int i = 500; i < 1000; i++){
					out << i - 500 << ":" << addr[i] << endl;
				}
				out.close();
			}
			else if (j == 4){
				addr = random(256 * 1024 * 1024);
				
				out.open("addr_seq_4.txt", ios::app);
				//freopen("0addr.txt", "w", stdout);
				out << "地址：";
				for (int i = 500; i < 1000; i++){
					out << i - 500 << ":" << addr[i] << endl;
				}
				out.close();
			}
			else
				addr = random(1);
			
			string fileName;
			switch (j){
			case 0:
				fileName = "visit_seq_0.txt";
				break;
			case 1:
				fileName = "visit_seq_1.txt";
				break;
			case 2:
				fileName = "visit_seq_2.txt";
				break;
			case 3:
				fileName = "visit_seq_3.txt";
				break;
			case 4:
				fileName = "visit_seq_4.txt";
				break;
			}
			
			out.open(fileName, ios::app);
			//freopen("0addr.txt", "w", stdout);

			out << "第" << i << "次" << "VP number PF number TLB hit/no hit  PT hit/no hit：" << endl;
			for (int i = 0; i < 500; i++){
				long long fn = tlb.getFrame(addr[i]);
				//不在TLB
				if (fn == -1){
					fn = page[j].GetFrame(addr[i]);
					if (fn == -1){//不在内存内
						Frame->AllocMemory(page[j], addr[i], record, tlb);
						out << addr[i] << "  " << page[j].GetFrame(addr[i]) << "  " << "TLB no hit  " << "PT no hit" << endl;

					}
					else{//在内存内
						tlb.insert(addr[i], fn);
						out << addr[i] << "  " << fn << "  " << "TLB no hit  " << "PT hit" << endl;
						pageCount[j]++;
					}
				}
				else{//在TLB 中
					out << addr[i] << "  " << fn << "  " << "TLB  hit  " << "PT hit" << endl;
					tlbCount[j]++;
					pageCount[j]++;
				}
			}
			out.close();
		}

	}
	
	
	string fileName;
	for(int i = 0; i < 5; i++){
		switch (i){
		case 0:
			fileName = "page_table_0.txt";
			break;
		case 1:
			fileName = "page_table_1.txt";
			break;
		case 2:
			fileName = "page_table_2.txt";
			break;
		case 3:
			fileName = "page_table_3.txt";
			break;
		case 4:
			fileName = "page_table_4.txt";
			break;
		}
		ofstream out;
		out.open(fileName, ios::app);
		//freopen("0addr.txt", "w", stdout);

		out << "Pagetable:" << endl;
		for (int j = 0; j < page[i].GetSize(); j++)
		{
			out << j << " " << page[i].GetFrame(j) << endl;
		}
		out.close();
	}
	for (int i = 0; i < 5; i++){
		cout << "第" << i << "次的页缺失率：" << (1500-pageCount[i]) / 1500.0 << endl;
		
	}

	system("pause");
}

long long*  random(long long _size){
	srand((unsigned)time(NULL));
	long long *k = new long long[1000];
	int num = 0;
	for (int i = 0; i < 50; i++){
		long long size = 0;
		for (int i = 0; i < 32; i++){
			size *= 2;
			size += rand() % 2;
		}
		k[num] = size%_size;
		num=num+1;
		for (int j = 0; j < 9; j++){
			k[num] = k[num - 1]+1;
			num++;
		}
	}
	for (int i = 500,j=0; i < 1000; i++,j++){
		if (k[j] < _size / 2)
			k[i] = k[j];
		else
			k[i] = 0xFFFFFFFF - (_size - k[j]);
	}

	for (int i = 0; i < 500; i++){
		if (k[i] % 8192 != 0)
			k[i] = k[i] / 8192 + 1;
		else
			k[i] = k[i] / 8192;
	}
	return k;
}
