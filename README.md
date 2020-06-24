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
59 clock
access F
pagefalut
pageOut
pageIn

PageTable_number,(exist_bit,fMemory_number)
0,(1,0)
1,(1,1)
2,(0,-1)
3,(0,-1)
4,(1,3)
5,(1,2)
6,(0,-1)
7,(0,-1)

Data:A(AccessTime:2020/06/24(Wed) 21:20:06.995050)
Data:B(AccessTime:2020/06/24(Wed) 21:20:07.033714)
Data:F(AccessTime:2020/06/24(Wed) 21:20:07.060927)
Data:E(AccessTime:2020/06/24(Wed) 21:20:06.936435)


60 clock
access F

PageTable_number,(exist_bit,fMemory_number)
0,(1,0)
1,(1,1)
2,(0,-1)
3,(0,-1)
4,(1,3)
5,(1,2)
6,(0,-1)
7,(0,-1)

Data:A(AccessTime:2020/06/24(Wed) 21:20:06.995050)
Data:B(AccessTime:2020/06/24(Wed) 21:20:07.033714)
Data:F(AccessTime:2020/06/24(Wed) 21:20:07.087704)
Data:E(AccessTime:2020/06/24(Wed) 21:20:06.936435)


61 clock
access C
pagefalut
pageOut
pageIn

PageTable_number,(exist_bit,fMemory_number)
0,(1,0)
1,(1,1)
2,(1,3)
3,(0,-1)
4,(0,-1)
5,(1,2)
6,(0,-1)
7,(0,-1)

Data:A(AccessTime:2020/06/24(Wed) 21:20:06.995050)
Data:B(AccessTime:2020/06/24(Wed) 21:20:07.033714)
Data:F(AccessTime:2020/06/24(Wed) 21:20:07.087704)
Data:C(AccessTime:2020/06/24(Wed) 21:20:07.129966)


62 clock
access F

PageTable_number,(exist_bit,fMemory_number)
0,(1,0)
1,(1,1)
2,(1,3)
3,(0,-1)
4,(0,-1)
5,(1,2)
6,(0,-1)
7,(0,-1)

Data:A(AccessTime:2020/06/24(Wed) 21:20:06.995050)
Data:B(AccessTime:2020/06/24(Wed) 21:20:07.033714)
Data:F(AccessTime:2020/06/24(Wed) 21:20:07.160299)
Data:C(AccessTime:2020/06/24(Wed) 21:20:07.129966)


63 clock
access H
pagefalut
pageOut
pageIn

PageTable_number,(exist_bit,fMemory_number)
0,(0,-1)
1,(1,1)
2,(1,3)
3,(0,-1)
4,(0,-1)
5,(1,2)
6,(0,-1)
7,(1,0)

Data:H(AccessTime:2020/06/24(Wed) 21:20:07.187404)
Data:B(AccessTime:2020/06/24(Wed) 21:20:07.033714)
Data:F(AccessTime:2020/06/24(Wed) 21:20:07.160299)
Data:C(AccessTime:2020/06/24(Wed) 21:20:07.129966)
  
...  
```