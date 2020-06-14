/*
    物理アドレス空間はLRUテーブルとともにある。
    Enter keyで1clock進む
*/

#include "lru.h"
#include <time.h>

int main(void){
    srand((unsigned int)time(NULL));
    initialize();
    showHDD();
    show();
    int i;
    char data;
    for(i=1;i<100;i++){
        printf("%d clock\n",i);
        switch(rand()%8)
        {
            case 0:
                access('A');
                break;
            case 1:
                access('B');
                break;
            case 2:
                access('C');
                break;
            case 3:
                access('D');
                break;
            case 4:
                access('E');
                break;
            case 5:
                access('F');
                break;
            case 6:
                access('G');
                break;
            case 7:
                access('H');
                break;
            default:
                break;
        }
        show();
    }
}