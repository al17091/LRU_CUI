#include "lru.h"

void initialize()
{
    char data[8]={'A','B','C','D','E','F','G','H'};
    int i=0;
    for(i=0;i<HDD_SIZE;i++){
        if(i<8){
            harddisk[i].data=data[i];
        }else{
            break;
        }
    }
    for(i=0;i<fMemory_SIZE;i++){
        LRU[i]=i;
    }
    for(i=0;i<vMemory_SIZE;i++){
        page_table[i].fMemory_number=-1;
        virtualMemory[i].data=harddisk[i].data;
    }
}

void access(char data)
{
    if((data=getHDD(data))=='\0'){
        printf("Data is not in HDD.\n");
    }
    int n=getvNum(data);    //アクセスするデータの仮想ページ番号
    if(pagefault(n)==0){    //ページフォルトする
        int fM_number=fMemorycheck();//物理アドレスの空き番号を返す
        if(fM_number==-1){ //物理アドレス空間に空きがない。
            fM_number=pageOut(&n);//ページアウトした物理アドレスを返す。
        }else{
            n=-1;//ページアウトしなかった場合
        }
        int InNum=pageIn(fM_number,data);//ページイン
        registTable(n,InNum,fM_number);//ページテーブルに登録
    }else{              //ページフォルトしない
        sort_LRU(n);     //LRUを並び変える
    }
}

int getvNum(char data)
{
    int i;
    for(i=0;i<vMemory_SIZE;i++){
        if(data==virtualMemory[i].data){
            printf("access %c\n",data);
            return i;
        }
    }
    printf("cat not access\n");
    return -1;
}

int pagefault(int pageNum)
{
    if(page_table[pageNum].exist_bit==0){  //存在しない
        printf("pagefalut\n");
        return 0;
    }else{          //存在する
        return 1;
    }
}

char getHDD(char data)
{
    int i;
    for(i=0;i<HDD_SIZE;i++){
        if(data==harddisk[i].data){
            return data;
        }
    }
    return '\0';
}

int fMemorycheck(){    //空き領域を確認
    int i=0;
    for(i=0;i<fMemory_SIZE;i++){
        if(figicalMemory[i].data=='\0'){ //空き領域
            return i;
        }
    }
    //空き領域がなければ
    return -1;
}

int getvMaddr(char data)
{
    int i;
    for(i=0;i<vMemory_SIZE;i++){
        if(data==virtualMemory[i].data){
            return i;
        }
    }
}

int pageOut(int *vMNum)
{
    printf("pageOut\n");
    int i=0,j=0;
    for(i=0;i<HDD_SIZE;i++){
        if(harddisk[i].data=='\0'){  //HDDの空いてるところ退避
            for(j=0;j<fMemory_SIZE;j++){
                //もともと入っていたデータの仮想アドレス
                if(LRU[j]==fMemory_SIZE-1){//LRU末尾
                    *vMNum=getvMaddr(figicalMemory[j].data);
                    break;
                }
            }
            //harddisk[i].data=figicalMemory[j].data;
            figicalMemory[j].data='\0';
            return j;
        }
    }
    //HDD空いていないのはないと思うが強制終了
    printf("HDDエラー\n");
    exit(0);
}

int pageIn(int fMNum,char data)
{   
    printf("pageIn\n");
    int i=0;
    figicalMemory[fMNum].data=data;
    for(i=0;i<fMemory_SIZE;i++){
        LRU[i]+=1;
    }
    LRU[fMNum]=0;
    for(i=0;i<vMemory_SIZE;i++){
        if(virtualMemory[i].data==data){
            return i;
        }
    }
}

void registTable(int outNum,int inNum,int fM_number)  
/*
    ページアウトした仮想アドレスとページインした仮想アドレスと物理アドレスを引数
*/
{
    //ページアウトしたページはbit=0でページ番号なし
    if(outNum!=-1){
        page_table[outNum].exist_bit=0;
        page_table[outNum].fMemory_number=-1;
    }
    //ページインしたページはbit=1でページ番号記載
    if(inNum!=-1){
        page_table[inNum].exist_bit=1;
        page_table[inNum].fMemory_number=fM_number;
    }
}

void sort_LRU(int vMNum)
{
    int i=0;
    if(LRU[page_table[vMNum].fMemory_number]==0){
        return;
    }
    for(i=0;i<fMemory_SIZE;i++){
        if(LRU[page_table[vMNum].fMemory_number]>LRU[i])
            LRU[i]+=1;
    }
    LRU[page_table[vMNum].fMemory_number]=0;
}

void show()
{
    int i=0;
    printf("\n");
    for(i=0;i<vMemory_SIZE;i++){
        printf("%c,(%d,%d)\n",
        virtualMemory[i].data,
        page_table[i].exist_bit,
        page_table[i].fMemory_number);
    }
    printf("\n");
    for(i=0;i<fMemory_SIZE;i++){
        printf("%c,LRU=%d\n",figicalMemory[i].data,LRU[i]);
    }
    printf("\n");
}

void showHDD()
{
    int i;
    printf("disk data\n");
    for(i=0;i<HDD_SIZE;i++){
        printf("%c ",harddisk[i].data);
    }
    printf("\n");
}
