#pragma once

#include <stdio.h>
#include <stdlib.h>

#define PROG_SIZE 5
#define vMemory_SIZE 8
#define fMemory_SIZE 4
#define STACK_SIZE 8
#define HDD_SIZE 100

typedef struct{
    int exist_bit;      //参照ビット
    int fMemory_number; //仮想ページ番号に対応する物理ページ番号
}PageT;

typedef struct{
    char data;
}Page;

int LRU[fMemory_SIZE];

Page virtualMemory[vMemory_SIZE];   //仮想メモリ
Page figicalMemory[fMemory_SIZE];   //物理メモリ
PageT page_table[vMemory_SIZE];        //ページテーブル
Page harddisk[HDD_SIZE];

void initialize();
int getvNum(char data);
int pagefault(int pageNum);
void access(char data);
int fMemorycheck();
int pageOut();
int pageIn(int fMNum,char data);
void registTable(int outNum,int inNum,int fM_number);
void sort_LRU(int vMNum);
void show();
void showHDD();
char getHDD(char data);
int getvMaddr(char data);