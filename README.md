# LRU_CUI
LRUアルゴリズムによって物理メモリ空間上のデータを入れ替えるデモ。 

## Data
- lru.hに物理メモリ、仮想メモリのサイズを定義。  
- lru-core.cでデータを格納。  

## Operate
- Enter keyで1回ずつアクセスする。
- 1回のアクセスで仮想メモリにあるデータを無作為に取ってくる。

## Compile
以下のどちらかでコンパイルしてください。
1. makeが使える場合、binディレクトリが作成されbinに実行ファイルが出力されます。  
```make```
2. makeが使えない場合  
```gcc -g -O2 -Wall -Werror *.c -o lru```  

## Run
引数はありません。
1. ```bin/lru```
2. ```./lru```

# Example
実行結果から抜粋
```
...  
virtualMemory  
(0),A (1),B (2),C (3),D (4),E (5),F (6),G (7),H   
...  
108 clock    
access B  
  
PageTable_number,(exist_bit,fMemory_number)  
0,(0,-1)  
1,(1,0)  
2,(1,2)  
3,(1,1)  
4,(0,-1)  
5,(1,3)  
6,(0,-1)  
7,(0,-1)  
  
Data:B(AccessTime:2020/06/24(Wed) 20:40:55.704924)  
Data:D(AccessTime:2020/06/24(Wed) 20:40:55.335953)  
Data:C(AccessTime:2020/06/24(Wed) 20:40:54.112912)  
Data:F(AccessTime:2020/06/24(Wed) 20:40:54.496609)  
  
  
109 clock  
access B  
  
PageTable_number,(exist_bit,fMemory_number)  
0,(0,-1)  
1,(1,0)  
2,(1,2)  
3,(1,1)  
4,(0,-1)  
5,(1,3)  
6,(0,-1)  
7,(0,-1)  
  
Data:B(AccessTime:2020/06/24(Wed) 20:40:56.071572)  
Data:D(AccessTime:2020/06/24(Wed) 20:40:55.335953)  
Data:C(AccessTime:2020/06/24(Wed) 20:40:54.112912)  
Data:F(AccessTime:2020/06/24(Wed) 20:40:54.496609)  
  
  
110 clock  
access F  
  
PageTable_number,(exist_bit,fMemory_number)  
0,(0,-1)  
1,(1,0)  
2,(1,2)  
3,(1,1)  
4,(0,-1)  
5,(1,3)  
6,(0,-1)  
7,(0,-1)  
  
Data:B(AccessTime:2020/06/24(Wed) 20:40:56.071572)  
Data:D(AccessTime:2020/06/24(Wed) 20:40:55.335953)  
Data:C(AccessTime:2020/06/24(Wed) 20:40:54.112912)  
Data:F(AccessTime:2020/06/24(Wed) 20:40:56.416328)  
  
  
111 clock  
access G  
pagefalut  
pageOut  
pageIn  
  
PageTable_number,(exist_bit,fMemory_number)  
0,(0,-1)  
1,(1,0)  
2,(0,-1)  
3,(1,1)  
4,(0,-1)  
5,(1,3)  
6,(1,2)  
7,(0,-1)  
  
Data:B(AccessTime:2020/06/24(Wed) 20:40:56.071572)  
Data:D(AccessTime:2020/06/24(Wed) 20:40:55.335953)  
Data:G(AccessTime:2020/06/24(Wed) 20:40:56.712432)  
Data:F(AccessTime:2020/06/24(Wed) 20:40:56.416328)  
  
...  
```