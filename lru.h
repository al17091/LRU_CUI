#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define vMemory_SIZE 8
#define fMemory_SIZE 4
#define STACK_SIZE 8

typedef struct{
    int exist_bit;      //参照ビット
    int fMemory_number; //仮想ページ番号に対応する物理ページ番号
}PageT;

typedef struct{
    char data;
    struct timeval access_time;
}Page;

extern char weekName[7][4];
extern char Data[vMemory_SIZE];

//記録用
extern int PageOutFlag;
extern int PageOutNum;
extern int PageInFlag;
extern int PageInNum;
extern int PageFaultFlag;
extern int FMchangeNum;

Page virtualMemory[vMemory_SIZE];   //仮想メモリ
Page figicalMemory[fMemory_SIZE];   //物理メモリ
PageT page_table[vMemory_SIZE];        //ページテーブル

void initialize();
void accessData(char data);
void showVM();
void showPT();
void showFM();

int getvNum(char data);
int pagefault(int pageNum);
int fMemorycheck();
int getvMaddr(char data);
int pageOut(int *vMNum);
int getOld();
int pageIn(int fMNum,char data);
void registTable(int outNum,int inNum,int fM_number);
void refresh_LRU(int vMNum);
