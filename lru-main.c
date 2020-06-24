/*
    物理アドレス空間にaccess_timeを定義する。
    Enter keyで1clock進む
    q + Enterで停止。
*/

#include "lru.h"
#include "keyboard.h"

int main(void){
    srand((unsigned int)time(NULL));
    initialize();
    showVM();
    int i,n;
    for(i=1;;i++){
        switch (inputKey())
		{
		case Esc:
			printf("end\n");
			return 0;
		case quit:
			printf("end\n");
			return 0;
		default:
            printf("%d clock\n",i);
            if((n=rand()%vMemory_SIZE)>=vMemory_SIZE){
                n=vMemory_SIZE-1;
                printf("rand error\n");
            }
            accessData(virtualMemory[n].data);
            showPT();
            showFM();
            break;
		}
    }
}
