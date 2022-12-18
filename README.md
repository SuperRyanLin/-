# 棋王 (Chess)

## 問題敘述

Dry 是屍大附中的棋王，他下象棋所向披靡，他的 $N - 2$ 個同學都被電得苦不堪言，只有 Wet 與他不分軒輊，但還是都敗下陣來。於是，他們聯手設計一場象棋比賽，想把 Dry 幹掉。

這場比賽的賽制為「乾濕瑞士制」：
贏棋得 2 分，和棋得 1 分，輸棋不得分。總共比五輪。紅棋先行（等同於執黑棋者讓一先）。
因為 Dry 班上人數是偶數，所以不會有輪空的情形。

每個人都有初始的腦力值，但因為實力（腦力）差距懸殊，他們還要求依段位差距讓子、讓先。每顆棋子的價值不同，分別為：

| 棋子 | 價值 |
| :---: | :----: |
| 帥、將 | 100 |
| 仕、士 | 2 |
| 相、象 | 2 |
| 俥、車 | 10 |
| 傌、馬 | 5 |
| 炮、包 | 5 |
| 兵、卒 | 1 |
| 1 先 | 1 |

象棋段位最低為 13 級，1 級後則升段，由初段至最高八段，但因 Dry 實力太強大，於是他有可能是九段棋手。
若兩人段位相同，編號小者執紅棋（編號大者讓一先），每差一級或一段，則段位較高者多讓一先。
例：五段棋手需讓二段棋手三先，也就是開局時二段棋手先下三步再換五段棋手下。
因為讓超過三先太難取勝，所以最多只能讓三先。若讓超過三先，則以讓子取代。
例：五段棋手需讓初段棋手四先，改為五段棋手讓傌並執紅棋（即初段棋手讓一先）。
若讓馬三先（即為讓馬外加讓三先）還不夠，如九段對初段，則讓下一種棋子，即讓炮、執紅棋，依此類推。讓子順序如下：
```
傌（馬）
炮（包）
俥（車）
雙傌（馬）
九子（雙仕、雙相、五隻兵）
俥（車）傌（馬）
俥（車）炮（包）
俥（車）傌（馬）炮（包）
```
完整讓子、讓先順序為：
```
讓一先
讓兩先
讓三先
讓傌、執紅棋
讓馬一先
讓馬兩先
讓馬三先
讓炮、執紅棋
讓包一先
...
```
依此類推，唯獨讓九子不讓先、只執紅棋。

在每輪比賽開始前，每位棋手會先失去等同於他讓的子、先的價值的腦力值。腦力值最多只會扣到剩 0，剩下的賽程該棋手會以無腦的方式下棋。腦力值較大的棋手將贏得該輪比賽，低的人則落敗；若兩人腦力值相等則和棋。

每輪的賽程會將棋手依腦力值由大到小排序，兩兩對戰。若腦力值相同則依編號由小到大排序。
請模擬賽程，算出 Dry（編號 1）、Wet（編號 2）與他們的同學在賽事結束後的總得分與剩餘的腦力值，以及 Wet 是否成功如願打敗 Dry 成為新的棋王。
因為 Dry 和 Wet 可能不只對戰一輪，所以用最後一次的勝負（和）判斷誰是棋王。

## 輸入說明
輸入總共有 $N + 2$ 行。
第一行有一個整數 $N$，表示班上總共有 $N$ 位同學（包含 Dry 和 Wet）
第二行有 $N$ 個整數 $b_i$，表示每位同學的初始腦力值。
接下來 $N$ 行有 $N$ 個字串 $s_i$，表示每位同學的段位、級位。一個人只會有一個段位或一個級位。
"$x_i$ pieces" 表示第 $i$ 位同學 $x_i$ 段，"level $y_i$" 表示第 $i$ 位同學 $y_i$ 級，不包括雙引號。

## 輸出說明
輸出總共有三行。
第一行輸出 $N$ 個整數，表示每個人的總得分。
第二行輸出 $N$ 個整數，表示每個人剩餘的腦力值。
第三行輸出 Wet 與 Dry 的戰果。
"10 minutes has passed!" 表示 Dry 獲勝，"I just mopped the floor!" 表示 Wet 獲勝，"Liquid-gas interface" 表示兩人沒有交戰或和棋，不包括雙引號。

## 測資限制
- $6 \leq N \leq 10^4, N = 2k$
- $0 \leq b_i \leq 10^9$
- $1 \leq x_1 \leq 9$
- $1 \leq x_i \leq 8, i \in \{2...N\}$
- $1 \leq y_i \leq 13$

## 範例測資

### 範例輸入
```
6
100 100 100 100 100 100
8 pieces
7 pieces
6 pieces
5 pieces
4 pieces
3 pieces
```

### 範例輸出
```
0 6 2 6 6 10 
89 95 94 96 98 100 
I just mopped the floor!
```

## 評分說明
| 子任務 | 分數 | 額外輸入限制 |
|:----:|:---:|:----:|
| $1$ | $20$ | 只有段位棋手 |
| $2$ | $20$ | 只有級位棋手 |
| $3$ | $60$ | 無額外限制 |

## Hint
冠軍有可能不是 Dry 也不是 Wet，但因為其他同學只崇拜他們兩個其中一個，所以只需要關心他們兩人的對戰結果。

## Q&A
Q: 讓九子為什麼不能讓先？
A: 第一步走炮中間一將軍臉就歪了，走不下去啊...

Q: 真的有九段棋手嗎？
A: 沒有，象棋最高段位是八段，而且人數很少。我們來看看 Dry 是否能成為下一位吧！

Q: 拖完地過十分鐘後，地會是乾的還是濕的呢？
A: Dry 覺得是乾的，Wet 覺得是濕的，所以他們展開這場大戰來決定...
A(Q): 你覺得呢？
