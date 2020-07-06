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

int PageOutFlag;
int PageOutNum;
int PageInFlag;
int PageInNum;
int PageFaultFlag;
int FMchangeNum;

void initialize()
{
    int i=0;
    struct timeval now;
    gettimeofday(&now, NULL);
    PageOutFlag=0;
    PageOutNum=-1;
    PageInFlag=0;
    PageInNum=-1;
    PageFaultFlag=0;
    FMchangeNum=-1;
    for(i=0;i<fMemory_SIZE;i++){
        physicalMemory[i].access_time=now;
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
        PageFaultFlag=1;
        return 0;
    }else{          //存在する
        PageFaultFlag=0;
        PageInFlag=0;
        PageOutFlag=0;
        return 1;
    }
}

int fMemorycheck(){    //空き領域を確認
    int i=0;
    for(i=0;i<fMemory_SIZE;i++){
        if(physicalMemory[i].data=='\0'){ //空き領域
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
    int i=0;
    for(i=0;i<fMemory_SIZE;i++){
        //もともと入っていたデータの仮想アドレス
        int pull_number=getOld();   //最古のアクセスのアドレス
        if(i==pull_number){
            *vMNum=getvMaddr(physicalMemory[i].data);
            break;
        }
    }
    physicalMemory[i].data='\0';
    physicalMemory[i].access_time.tv_sec=0;
    physicalMemory[i].access_time.tv_usec=0;
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
        timersub(&t,&physicalMemory[i].access_time,&result);
        if(result.tv_sec>0 || (result.tv_sec==0&&result.tv_usec>0)){
            pull_number=i;
            t=physicalMemory[i].access_time;
        }
    }
    return pull_number; 
}

int pageIn(int fMNum,char data)
{   
    int i=0;
    struct timeval now;
    gettimeofday(&now, NULL);
    physicalMemory[fMNum].data=data;
    physicalMemory[fMNum].access_time=now;
    for(i=0;i<vMemory_SIZE;i++){
        if(virtualMemory[i].data==data){
            break;
        }
    }
    return i;
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
        PageOutFlag=1;
        PageOutNum=outNum;
    }else{
        PageOutFlag=0;
    }
    //ページインしたページはbit=1でページ番号記載
    if(inNum!=-1){
        page_table[inNum].exist_bit=1;
        page_table[inNum].fMemory_number=fM_number;
        PageInFlag=1;
        PageInNum=inNum;
        FMchangeNum=fM_number;
    }else{
        PageInFlag=0;
    }
}

void refresh_LRU(int vMNum)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    physicalMemory[page_table[vMNum].fMemory_number].access_time=now;
    FMchangeNum=page_table[vMNum].fMemory_number;
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
    if(PageFaultFlag==1){
        printf("pagefault\n\n");
    }
    printf("PageTable[N],vMemoryData,(exist_bit,fMemory_number)\n");
    for(i=0;i<vMemory_SIZE;i++){
        if(PageOutNum==i&&PageOutFlag==1){
            printf("%d[%c],(%d,%2d) => PageOut\n",i,virtualMemory[i].data,page_table[i].exist_bit,page_table[i].fMemory_number);
            continue;               
        }
        if(PageInNum==i&&PageInFlag==1){
            printf("%d[%c],(%d,%2d) <= PageIn\n",i,virtualMemory[i].data,page_table[i].exist_bit,page_table[i].fMemory_number);  
            continue;             
        }
        printf("%d[%c],(%d,%2d)\n",i,virtualMemory[i].data,page_table[i].exist_bit,page_table[i].fMemory_number);
    }
    printf("\n");
}

void showFM()
{
    int i=0;
    for(i=0;i<fMemory_SIZE;i++){
        struct tm *time_st;
        time_st = localtime(&physicalMemory[i].access_time.tv_sec);
        if(FMchangeNum==i){
            printf("Data:%c(AccessTime:%d/%02d/%02d(%s) %02d:%02d:%02d.%06ld)　<changed>\n",     // 現在時刻
                    physicalMemory[i].data,
                    time_st->tm_year+1900,     // year
                    time_st->tm_mon+1,         // month
                    time_st->tm_mday,          // day
                    weekName[time_st->tm_wday],// weekName
                    time_st->tm_hour,          // hour
                    time_st->tm_min,           // min
                    time_st->tm_sec,           // sec
                    physicalMemory[i].access_time.tv_usec            // micro sec
                    );            
        }else{
            printf("Data:%c(AccessTime:%d/%02d/%02d(%s) %02d:%02d:%02d.%06ld)\n",     // 現在時刻
                    physicalMemory[i].data,
                    time_st->tm_year+1900,     // year
                    time_st->tm_mon+1,         // month
                    time_st->tm_mday,          // day
                    weekName[time_st->tm_wday],// weekName
                    time_st->tm_hour,          // hour
                    time_st->tm_min,           // min
                    time_st->tm_sec,           // sec
                    physicalMemory[i].access_time.tv_usec            // micro sec
                    );
        }
    }
    printf("\n");
}
