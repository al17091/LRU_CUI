# LRU_CUI
LRUアルゴリズムによって物理メモリ空間上のデータを入れ替えるデモ。 

## Data
- lru.hに物理メモリ、仮想メモリのサイズを定義。  
- lru-core.cでデータを格納。  

## Operate
- Enter keyで1回ずつアクセスする。
- 1回のアクセスで仮想メモリにあるデータを無作為に取ってくる。
- q, Enter keyを押すと終了。

## Compile
以下のどちらかでコンパイルしてください。
1. makeが使える場合、binディレクトリが作成されbinに実行ファイルが出力されます。  
```make```
2. makeが使えない場合  
```gcc -g -O2 -Wall -Werror *.c -o lru```  
```-g -O2 -Wall -Werror ```はなくてもいいです。

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
106 clock
access C

PageTable[N],vMemoryData,(exist_bit,fMemory_number)
0[A],(1, 1)
1[B],(0,-1)
2[C],(1, 3)
3[D],(0,-1)
4[E],(0,-1)
5[F],(0,-1)
6[G],(1, 2)
7[H],(1, 0)

Data:H(AccessTime:2020/06/28(Sun) 14:28:51.269402)
Data:A(AccessTime:2020/06/28(Sun) 14:28:51.167739)
Data:G(AccessTime:2020/06/28(Sun) 14:28:51.226666)
Data:C(AccessTime:2020/06/28(Sun) 14:28:51.300962)　<changed>


107 clock
access D

pagefault

PageTable[N],vMemoryData,(exist_bit,fMemory_number)
0[A],(0,-1) => PageOut
1[B],(0,-1)
2[C],(1, 3)
3[D],(1, 1) <= PageIn
4[E],(0,-1)
5[F],(0,-1)
6[G],(1, 2)
7[H],(1, 0)

Data:H(AccessTime:2020/06/28(Sun) 14:28:51.269402)
Data:D(AccessTime:2020/06/28(Sun) 14:28:52.266763)　<changed>
Data:G(AccessTime:2020/06/28(Sun) 14:28:51.226666)
Data:C(AccessTime:2020/06/28(Sun) 14:28:51.300962)
...  
```
