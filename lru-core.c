#include "lru.h"

char weekName[7][4] = {
    "Sun",
    "Mon",
    "Tue",
    "Wed",
    "Thu",
    "Fri",
    "Sat"
};

char Data[vMemory_SIZE]={'A','B','C','D','E','F','G','H'};

void initialize()
{
    int i=0;
    struct timeval now;
    gettimeofday(&now, NULL);
    for(i=0;i<fMemory_SIZE;i++){
        figicalMemory[i].access_time=now;
    }
    for(i=0;i<vMemory_SIZE;i++){
        page_table[i].fMemory_number=-1;
        virtualMemory[i].data=Data[i];
    }
}

void accessData(char data)
{
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
        refresh_LRU(n);     //access_timeを最新にする。
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
    return -1;
}

int pageOut(int *vMNum)
{
    printf("pageOut\n");
    int i=0;
    for(i=0;i<fMemory_SIZE;i++){
        //もともと入っていたデータの仮想アドレス
        int pull_number=getOld();   //最古のアクセスのアドレス
        if(i==pull_number){
            *vMNum=getvMaddr(figicalMemory[i].data);
            break;
        }
    }
    figicalMemory[i].data='\0';
    figicalMemory[i].access_time.tv_sec=0;
    figicalMemory[i].access_time.tv_usec=0;
    return i;
}

int getOld()
{
    int i=0;
    int pull_number=0;
    struct timeval t;
    struct timeval result;
    gettimeofday(&t, NULL);
    for(i=0;i<fMemory_SIZE;i++){
        timersub(&t,&figicalMemory[i].access_time,&result);
        if(result.tv_sec>0){
            pull_number=i;
            t=figicalMemory[i].access_time;
        }
    }
    return pull_number; 
}

int pageIn(int fMNum,char data)
{   
    printf("pageIn\n");
    int i=0;
    struct timeval now;
    gettimeofday(&now, NULL);
    figicalMemory[fMNum].data=data;
    figicalMemory[fMNum].access_time=now;
    for(i=0;i<vMemory_SIZE;i++){
        if(virtualMemory[i].data==data){
            return i;
        }
    }
    return -1;
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

void refresh_LRU(int vMNum)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    figicalMemory[page_table[vMNum].fMemory_number].access_time=now;
}

void showVM()
{
    int i=0;
    printf("virtualMemory\n");
    for(i=0;i<vMemory_SIZE;i++){
        printf("(%d),%c ",i,virtualMemory[i].data);
    }
    printf("\n");
}

void showPT()
{
    printf("\n");
    int i=0;
    printf("PageTable_number,(exist_bit,fMemory_number)\n");
    for(i=0;i<vMemory_SIZE;i++){
        printf("%d,(%d,%d)\n",
        i,page_table[i].exist_bit,page_table[i].fMemory_number);
    }
    printf("\n");
}

void showFM()
{
    int i=0;
    for(i=0;i<fMemory_SIZE;i++){
        struct tm *time_st;
        time_st = localtime(&figicalMemory[i].access_time.tv_sec);
        printf("Data:%c(AccessTime:%d/%02d/%02d(%s) %02d:%02d:%02d.%06ld)\n",     // 現在時刻
                figicalMemory[i].data,
                time_st->tm_year+1900,     // year
                time_st->tm_mon+1,         // month
                time_st->tm_mday,          // day
                weekName[time_st->tm_wday],// weekName
                time_st->tm_hour,          // hour
                time_st->tm_min,           // min
                time_st->tm_sec,           // sec
                figicalMemory[i].access_time.tv_usec            // micro sec
                );
    }
    printf("\n");
}
