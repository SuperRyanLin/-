# 師大附中資訊校隊模擬競賽 I 題解

---

## 人生失敗組 (Failure)
出題者：Ryan Lin  
我不會寫程式，我是個 failure

----

有 $N$ 個 failure，每一個會跟蹤某幾個 failure，總共有 $M$ 個關係。現在 Steven's Dad 想要確保他一定可以透過某個 failure 知道某另一個 failure 在哪裡，還有哪一個該死的 failure 竟敢找不到對方。

----

白話文：  
有 $N$ 個點、 $M$ 條邊，判斷這是不是一個強聯通塊。如果不是則輸出任意兩個不在同一個強聯通塊的點。

----

## 子任務 1
$N \leq 8$  
21 分

----

$O(N^2)$  枚舉每兩個點 $u, v$，再 $O(N + M)$ DFS 檢查是否能從 $u$ 走到 $v$。  
總複雜度 $O(N^2(N + M))$

----

## 子任務 2
$N \leq 1000$  
20 分

----

~~這個本來是亂切的子題~~  
枚舉每一個點，分別 DFS 一次，看哪個點沒走到。  
總複雜度 $O(N(N + M))$  
某參賽者賽中程式碼

```cpp=
#include <cstdio>
#include <vector>
#include <set>
 
void dfs(int start_node, std::vector<int> *edges, std::set<int> *unvisited, bool *visited) {
    visited[start_node] = true;
    unvisited->erase(start_node);
    for(auto i: edges[start_node]) {
        if(!visited[i]) {
            dfs(i, edges, unvisited, visited);
        }
    }
}
 
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    std::vector<int> *edges = new std::vector<int>[n];
    for(int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        edges[a-1].push_back(b-1);
    }
    int touched = 0;
     
    for(int i = 0; i < n; i++) {
        std::set<int> unvisited;
        bool *visited = new bool[n];
        for(int j = 0; j < n; j++) unvisited.insert(j), visited[j] = false;
        dfs(i, edges, &unvisited, visited);
        if(unvisited.size()) {
            puts("There are ultra failures!");
            printf("%d %d", i+1, *unvisited.begin()+1);
            return 0;
        }
        delete []visited;
    }
 
    delete []edges;
    puts("Failures together strong!");
}
```

----

## 子任務 3（滿分解）- 1

----

Kosaraju/Tarjan 直接砸下去（以下使用 Kosaraju）  
總複雜度 $O(N + M)$  
AC code

```cpp=
#include <bits/stdc++>h>
using namespace std;
const int mxn = 100005;
vector<int> g[mxn];
vector<int> gr[mxn];
vector<int> order;
bool vis[maxn];

void dfs1 (int nd) {
    vis[nd] = true;
    for (int x : g[nd]) {
        if (!vis[x]) dfs1(x);
    }
    order.push_back(nd);
}

void dfs2 (int nd) {
    vis[nd] = true;
    for (int x : gr[nd]) {
        if (!vis[x]) dfs2(x);
    }
}

int main () {
    int n, m;
    (void)!scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        (void)!scanf("%d%d", &a, &b);
        g[a].push_back(b);
        gr[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) dfs1(i);
    }
    reverse(order.begin(), order.end());

    vector<int> root;
    memset(vis, 0, sizeof(vis));
    for (int x : order) {
        if (!vis[x]) {
            dfs2(x);
            root.push_back(x);
        }
    }

    if (root.size() == 1) printf("Failures together strong!\n");
    else printf("There are ultra failures!\n%d %d\n", root[1], root[0]);
}
```

----

## 滿分解 - 2

----

正圖、反圖各從節點 $1$ DFS 一次，任何一次沒經過點跟節點 $1$ 就是 ultra failure。  
總複雜度 $O(N + M)$  
AC code

```cpp=
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const ll mxn = 200005;
 
bool vis1[mxn], vis2[mxn];
vector<ll> g1[mxn], g2[mxn];
 
void dfs1(ll cur, ll last) {
    vis1[cur] = true;
    for (ll nxt : g1[cur]) if (nxt != last && !vis1[nxt]) dfs1(nxt, cur);
}
 
void dfs2(ll cur, ll last) {
    vis2[cur] = true;
    for (ll nxt : g2[cur]) if (nxt != last && !vis2[nxt]) dfs2(nxt, cur);
}
 
int main() {
    ll n, m;
    (void)!scanf("%lld%lld", &n, &m);
    while (m--) {
        ll a, b;
        (void)!scanf("%lld%lld", &a, &b);
        g1[a].emplace_back(b);
        g2[b].emplace_back(a);
    }
    
    dfs1(1, 0);
    dfs2(1, 0);
    
    for (ll i = 1; i <= n; i++) {
        if (!vis1[i]) {
            printf("There are ultra failures!\n1 %lld\n", i);
            return 0;
        }
        if (!vis2[i]) {
            printf("There are ultra failures!\n%lld 1\n", i);
            return 0;
        }
    }
    printf("Failures together strong!\n");
}
```

---

## 蜘蛛詭雷 (Patrol)

出題者：Foxyy  
星海好好玩

----

### 子任務 1

$k=0$

----

只要 DFS/BFS 就可以找到最短距離了

----

### 子任務 2

$k = 1$

----

可以模擬每秒鐘詭雷所在的位置，用 $0/1$ BFS 就可以找到受傷最少的路徑

----

### 子任務 3

$l_i = 1$

----

直接 Dijkstra 就好

----

### 子任務 4

$r_i = 0$

----

跟上個子題一樣(?，只是加上模擬

----

### 子任務 5

$m = 1$

----

~~降低實作複雜度~~

----

### 子任務 6 (滿分解)

----

觀察到詭雷的路徑長度最長只有 $4$，所以所有詭雷會有一個 $\text{lcm}(1, 2, 4, 6) = 12$ 的週期。  
建一張 `g[12][n][m]` 的圖，然後跑 Dijkstra 就可以過了

----

官解：
```cpp=
#include <bits/stdc++.h>
using namespace std;

#define ll long long

#define Foxyy cin.tie(0); cout.sync_with_stdio(0); cout.tie(0);

const int INF = 0x3f3f3f3f;

struct Solver {
	static const int T = 12;
	
	int& n;
	int& m;
	int& k;
	vector<string>& grid;
	vector<int>& l;
	vector<int>& r;
	vector<vector<int>>& x;
	vector<vector<int>>& y;
	int& sx;
	int& sy;
	int& tx;
	int& ty;
	
	bool isValidCoord(int x, int y) {
		return 	0 <= x and x < n
			and	0 <= y and y < m
			and grid[x][y] != '#';
	}
	
	array<vector<vector<int>>, T>& getCost() {
		array<vector<vector<int>>, T>& cost = *(new array<vector<vector<int>>, T>());
		fill(cost.begin(), cost.end(), vector<vector<int>>(n, vector<int>(m, 0)));
		
		auto fillCircle = [this, &cost](int t, int r, int ax, int ay) {
			// ax : anchor x
			// ay : anchor y
			for (int x = max(ax - r, 0); x <= min(ax + r, n-1); x++) {
				for (int y = max(ay - (r - abs(ax - x)), 0); y <= min(ay + (r - abs(ax - x)), m-1); y++) {
					cost[t][x][y]++;
				}
			}
		};
		
		for (int t = 0; t < T; t++) {
			for (int i = 0; i < k; i++) {
				fillCircle(t, r[i], x[i][t % l[i]], y[i][t % l[i]]);
			}
		}
		
//		for (int t = 0; t < T; t++) {
//			cerr << "t = " << t << '\n';
//			for (int i = 0; i < n; i++) {
//				for (int j = 0; j < m; j++) {
//					cerr << cost[t][i][j] << '\t';
//				}
//				cerr << '\n';
//			}
//			cerr << '\n';
//		}
		
		return cost;
	}
	
	pair<int, int> findLessDamageRoute(array<vector<vector<int>>, T>& cost) {
		static const pair<int, int> steps[]{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
		
		array<vector<vector<pair<int, int>>>, T> dist;
		fill(dist.begin(), dist.end(), vector<vector<pair<int, int>>>(n, vector<pair<int, int>>(m, {INF, INF})));
		
		struct Info {
			int dmgTaken;
			int length;
			int time;
			struct { int x, y; } coord;
			
			bool operator < (Info other) const {
				return dmgTaken == other.dmgTaken ? length < other.length : dmgTaken < other.dmgTaken;
			}
			bool operator > (Info other) const {
				return other < *this;
			}
		};
				
		priority_queue<Info, vector<Info>, greater<Info>> pq;
		pq.push({0, 0, 0, {sx, sy}});
		while (not pq.empty()) {
			auto [dmgTaken, length, time, coord] = pq.top(); pq.pop();
			auto [x, y] = coord;
			
//			cerr << time << ' ' << x << ' ' << y << ' ' << dmgTaken << ' ' << length << '\n';
			
			if (make_pair(dmgTaken, length) >= dist[time][x][y]) {
				continue;
			}
			dist[time][x][y] = make_pair(dmgTaken, length);
			
			if (x == tx and y == ty) {
				return {dmgTaken, length};
			}
			
			int nTime = (time + 1) % T;
			pq.push({dmgTaken + cost[nTime][x][y], length + 1, nTime, {x, y}});
			for (auto [dx, dy] : steps) {
				int nx = x + dx;
				int ny = y + dy;
				if (not isValidCoord(nx, ny)) {
					continue;
				}
				pq.push({dmgTaken + cost[nTime][nx][ny], length + 1, nTime, {nx, ny}});
			}
		}
		return {-1, -1};
	}
	
	void solve() {
		if (sx == tx and sy == ty) {
			cout << "0 0\n";
			return;
		}
		
		for (int i = 0; i < k; i++) {
			for (int j = l[i]-2; j > 0; j--) {
				x[i].push_back(x[i][j]);
				y[i].push_back(y[i][j]);
			}
			l[i] = (int)x[i].size();
		}
		
		pair<int, int> ans = findLessDamageRoute(getCost());
		
		if (ans.first == -1) {
			cout << "-1\n";
		} else {
			cout << ans.first << ' ' << ans.second << '\n';
		}
	}
};

signed main() {
//	Foxyy
	
	int T = 1;
//	cin >> T;
	while(T--) {
		int n, m, k;
		cin >> n >> m >> k;
		
		vector<string> grid(n);
		for (auto& row : grid) {
			cin >> row;
		}
		
		vector<int> l(k), r(k);
		vector<vector<int>> x(k), y(k);
		for (int i = 0; i < k; i++) {
			cin >> l[i] >> r[i];
			x[i].resize(l[i]), y[i].resize(l[i]);
			for (int j = 0; j < l[i]; j++) {
				cin >> x[i][j] >> y[i][j];
				x[i][j]--, y[i][j]--;
			}
		}
		
		int sx, sy, tx, ty;
		cin >> sx >> sy >> tx >> ty;
		sx--, sy--, tx--, ty--;
		
		Solver solver{n, m, k, grid, l, r, x, y, sx, sy, tx, ty};
		solver.solve();
	}
}
```

---

## 	一般圖最大最小權極大匹配 (Matching)

出題者：WiwiHo  
侯女神缺席，小弟們都不會 QQ  
![](https://i.imgur.com/BHq3MKd.png)

----

沒錯這題整體都是偷的 (X)  
題敘只是故意寫得很噁心，白話文就是  
有很多東西排在一條直線上，如果兩個東西距離 $\leq K$ 它們就可以配成一對，你要把東西配對使得：  
- 所有東西最多在一對裡
- 不存在兩個沒有配對的東西，使得它們可以配成一對
- 讓沒有配到對的東西權重總和最小$(T=1)$/最大$(T=2)$

----

首先如果存在 $x_{i + 1} - x_i > K$，那麼兩邊其實可以當成兩個問題分開做。因此以下假設所有 $x_{i + 1} - x_i \leq K$。  
想哪些人要配在一起很麻煩，我們不如想「誰沒有被配到」。

----

如果沒有被配到的人是固定的，那麼剩下的人都要在某個配對裡，顯而易見地一種配對方法是，把要配的人兩兩相鄰的配成一組。  
要檢查一些人能不能當沒有配到的人，首先沒配的人不能相鄰，然後有配到的人必須是偶數個。對於每個沒配到的人，如果它左右各有奇數個有配到的人，那它的前一個人和後一個人（他們一定是要配的）就會配在一起，也就是它們的距離要 $\leq K$。

----

### T = 1

如果數量是偶數，那相鄰兩兩配起來，沒配到的權重總和就是 0。反之，會有一個東西配不到，枚舉那個東西並檢查它可不可以不要配。

----

### T = 2

令 $dp[i][j] =$ 考慮前 $i$ 個人中有 $j$ 個不配對。如果第 $i$ 個人不要配的話，看左邊有奇數還偶數個人要配，如果是偶數個，那就可以配，否則第 $i − 1$ 個人和第 $i + 1$ 個人必須可以配在一起。  
如果滿足第 $i$ 個人可以不配的條件，$dp[i][j]$ 就是 $max(dp[i−1][j], dp[k][j−1])$，$k$ 是最大的數字滿足 $k < i∧x_i − x_k > K$，不存在的話就是 $0$。否則 $dp[i][j]$ 就是 $dp[i − 1][j]$。

----

注意到我們只關心 $j$ 是奇數還是偶數，所以後面那個狀態可以直接改成前面不配的人數是奇數還是偶數。時間複雜度 $O(N \ log \ N)$ 。

---

## 棋王 (Chess)
出題者：Ryan Lin  
我的初始腦力值 $b = 0$ 才會出這個殘害社會

----

注：這題的實作技巧都放在滿分解一次講，子題只講該部分實作技巧

----

### 子任務 1
只有段位棋手  
高手大亂鬥

----

把差幾段要讓多少分數分別列出來就好了

----

### 子任務 2
只有級位棋手  
高麗菜大亂鬥

----

把差幾級要讓多少分數分別列出來就好了  
把級位倒過來比較方便做滿分解

----

### 子任務 3（滿分解）
把級位反過來、段位 + 13 就可以直接相減了  
把讓的分數全列出來查表就好了  
排序方法看清楚  
每次讓棋手 $i$、$i + 1$ 對弈  
紀錄 Dry、Wet 最後一次交手的結果，勝方設成 true  
沒有對到、和棋都記錄兩個 false

----

沒看清楚題目的注意！！！  
讓九子**只有**執紅棋一種型態，再讓先太不仁道了！  
所以讓九子後馬上接著讓車馬執紅棋。  
~~這也是出題者設計九段的目的。~~

----

AC code
```cpp=
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

const int mxn = 10005;
pii b[mxn];
int x[mxn];
int points[mxn];

char s[10];

pii handicap[] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {5, 1}, {6, 0}, {7, 0}, {8, 0}, {5, 1}, {6, 0}, {7, 0}, {8, 0}, {10, 1}, {11, 0}, {12, 0}, {13, 0}, {10, 1}, {11, 0}, {12, 0}, {13, 0}, {13, 1}, {15, 1}};

int main() {
    int n;
    (void)!scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        (void)!scanf("%d", &b[i].first);
        b[i].second = i;
    }
    for (int i = 1; i <= n; i++) {
        (void)!scanf("%s", s);
        if (s[0] == 'l') {
            int lv;
            (void)!scanf("%d", &lv);
            x[i] = 14 - lv;
        } else {
            x[i] = (s[0] - '0') + 13;
            (void)!scanf("%s", s);
        }
    }
    
    bool dry = false, wet = false;
    for (int round = 1; round <= 5; round++) {
        sort(b + 1, b + n + 1, [](pii& a, pii& b) { return a.first == b.first ? a.second < b.second : a.first > b.first; });
        for (int i = 1; i <= n; i += 2) {
            int& ba = b[i].first;
            int& bb = b[i + 1].first;
            const int ida = b[i].second, idb = b[i + 1].second;
            if (x[ida] < x[idb]) {
                const int d = x[idb] - x[ida];
                bb -= handicap[d].first;
                ba -= handicap[d].second;
            } else if (x[ida] > x[idb]) {
                const int d = x[ida] - x[idb];
                ba -= handicap[d].first;
                bb -= handicap[d].second;
            } else {
                if (ida < idb) bb -= 1;
                else ba -= 1;
            }
            ba = max(ba, 0);
            bb = max(bb, 0);
            
            if (ba > bb) {
                points[ida] += 2;
                if (ida == 1 && idb == 2) {
                    dry = true;
                    wet = false;
                } else if (ida == 2 && idb == 1) {
                    wet = true;
                    dry = false;
                }
            } else if (ba < bb) {
                points[idb] += 2;
                if (idb == 1 && ida == 2) {
                    dry = true;
                    wet = false;
                } else if (idb == 2 && ida == 1) {
                    wet = true;
                    dry = false;
                }
            } else {
                points[ida] += 1;
                points[idb] += 1;
                if ((ida == 1 && idb == 2) || (ida == 2 && idb == 1)) dry = wet = false;
            }
        }
    }
    sort(b + 1, b + n + 1, [](pii& a, pii& b) { return a.second < b.second; });
    
    for (int i = 1; i <= n; i++) printf("%d ", points[i]);
    printf("\n");
    for (int i = 1; i <= n; i++) printf("%d ", b[i].first);
    printf("\n");
    
    if (dry) printf("10 minutes has passed!\n");
    else if (wet) printf("I just mopped the floor!\n");
    else printf("Liquid-gas interface\n");
}
```

----

以下都是題外話 (TL, DR)  
所以說讓九子到底為什麼不能再讓先？  
以下圖為例...  
![image](https://github.com/SuperRyanLin/Problem_Generating_Chess/blob/main/讓九子一先.jpg)

----

第一步炮平中間直接將軍，黑方只能把將往旁邊歪  
第二步出俥後黑方難以招架

----

棋譜  
1. 炮二平五 將 5 平 6  
2. 俥一進二 紅大優

----

那麼最下面 Q&A 問的問題呢？  
一切淵源的開端：  
I just mopped the floor ten minutes ago, so it's ___ now.  
1. dry  
2. wet

----

所有隨機測資中 Dry 贏的次數比較多，正式宣佈 Dry 獲勝！

----

### 趣文分享
其實 DRY 是一種大家最推薦的寫 code 的原則，它是 Don't Repeat Yourself 的縮寫，也就是盡量把相同性質的 code 包裝成 function, constant, reference 或 class 來保持整潔美觀。

----

相對的 WET 是 Write Everything Twice，也就是不特地把重複的 code 獨立出來。在一般的小程式中或是主幹函式裡當然是 DRY 比較簡潔，但有時候在函式中又包裝小函式會反而更亂，WET 才會派上用場。

----

不過我們是競程選手，我們的程式碼要以好修改、好寫、簡潔且一次性使用為主，所以還是主流的 DRY 比較適合。

參考資料：
https://medium.com/jl-codes/dry-vs-wet-code-589c564aa5aa

---

## 戰地前線 (Frontline)
出題者：Foxyy
\1D CSGO/

----

首先觀察到，如果要開槍，一定會在某個 $x_i-k$ 的位置開槍

----

### 子任務 1
$n = 1$

----

只要可以安全走到 $x_1-k$ 的位置就可以過關

----

### 子任務 2 
$k = 1$  
~~近戰狙擊手~~

----

可以算出要殺掉所有敵人所需的最低血量，而且一定要走到敵人面前才能擊殺該敵人

----

#### 子任務 3
$d_i = 1$

~~刀是打不過大狙的~~

----

Melon 一定會在 $x_i - k$ 殺人，且每個敵人都需要被擊殺  
Melon 只有在走進敵人攻擊範圍的那一刻會受傷，且對於同個 $i$，兩個不同的轉移點 $j$ 轉移時受到的傷害會不一樣  
我們可以列出 DP 式

$$
\begin{align}
    dp[i][h]  &= \min_{lst(i) \le j < i}\{dp[j][h+dmg(j, i)]\}+1 \\
    dmg(j, i) &= |\{t \mid t > j \land x[t]-1 = x[i]-k\}| \\
    lst(i)    &= \arg\max_j\{x[j] \le x[i]-k\}
\end{align}
$$

----

Code
```cpp=
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define Foxyy cin.tie(0); cout.sync_with_stdio(0);

const int INF = 0x3f3f3f3f;

struct Solver {
	
	int& n;
	int& h;
	int& k;
	vector<int>& x;
	vector<int>& d;
	
	int lst(int i) {
		int j = lower_bound(x.begin(), x.end(), x[i]-k+1) - x.begin();
		return max(j-1, 0);
	}
	
	int dmg(int j, int i) {
		return count(x.begin()+j+1, x.end(), x[i]-k+1);
	}
	
	void solve() {
		vector<vector<int>> dp(n+1, vector<int>(h+1, INF));
		dp[0][h] = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = lst(i); j < i; j++) {
				int dmgTaken = dmg(j, i);
				for (int health = 1; health <= h-dmgTaken; health++) {
					dp[i][health] = min(dp[i][health], dp[j][health+dmgTaken]+1); 
				}
			}
		}
		
//		for (int i = 1; i <= n; i++) {
//			for (int j = 1; j <= h; j++) {
//				cerr << dp[i][j] << '\t';
//			}
//			cerr << '\n';
//		}
//		cerr << dmg(2, 3) << '\n';
		
		int minTime = INF, maxHealth = 0;
		for (int health = h; health > 0; health--) {
			if (minTime > dp[n][health]) {
				minTime = dp[n][health];
				maxHealth = health;
			}
		}
		if (maxHealth == 0) {
			cout << "-1\n";
		} else {
			cout << minTime + x[n] - k << ' ' << maxHealth << '\n';
		}
	}
};

signed main() {
	Foxyy
	
	int T = 1;
//	cin >> T;
	
	while (T--) {
		int n, h, k;
		cin >> n >> h >> k;
		vector<int> x(n+1), d(n+1);
		for (int i = 1; i <= n; i++) {
			cin >> x[i] >> d[i];
		}
		
		Solver solver{n, h, k, x, d};
		solver.solve();
	}
}
```

----

### 子任務 4 (滿分解)

----

跟上一題唯一不一樣的地方是，$dmg(j, i)$ 的條件改變了

$$
\begin{align}
dmg(j, i)   &= \sum_{t \in S(j, i)}\left((x[i]-k+1)-
            \max(x[t]-d[t], x[j]-k+1)\right) \\
    S(j, i) &= \{t \mid t > j \land x[i] - k \ge x[t] - d[t]\}
\end{align}
$$

----

官解
```cpp=
#include <bits/stdc++.h>
using namespace std;

#define ll long long

#define Foxyy cin.tie(0); cout.sync_with_stdio(0); cout.tie(0);

const int INF = 0x3f3f3f3f;

struct Solver {
	
	int& n;
	int& h;
	int& k;
	vector<int>& x;
	vector<int>& d;
	
	int getLst(int i) {
		int pos = lower_bound(x.begin(), x.end(), x[i]-k+1) - x.begin();
		return max(pos - 1, 0);
	}
	
	int getDmg(int j, int i) {
		ll dmg = 0;
		for (int t = j+1; t <= n; t++) {
			if (x[i] - k >= x[t] - d[t]) {
				dmg += (x[i] - k + 1) - max(x[t] - d[t], x[j] - k + 1);
			}
		}
		return (int)min(dmg, (ll)h);
	}
	
	void solve() {
		vector<vector<int>> dp(n+1, vector<int>(h+1, INF));
		dp[0][h] = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = getLst(i); j < i; j++) {
				int dmg = getDmg(j, i);
				for (int health = 1; health <= h - dmg; health++) {
					dp[i][health] = min(dp[i][health], dp[j][health+dmg] + 1);
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= h; j++) {
				cerr << dp[i][j] << '\t';
			}
			cerr << '\n';
		}
		pair<int, int> ans = {INF, INF};
		for (int i = h; i > 0; i--) {
			if (ans.first > dp[n][i]) {
				ans.first = dp[n][i];
				ans.second = i;
			}
		}
		if (ans.first == INF) {
			cout << "-1\n";
		} else {
			cout << ans.first + x[n] - k << ' ' << ans.second << '\n';
		}
	}
};

signed main() {
	Foxyy
	
	int T = 1;
//	cin >> T;
	while(T--) {
		int n, h, k;
		cin >> n >> h >> k;
		vector<int> x(n+1), d(n+1);
		for (int i = 1; i <= n; i++) {
			cin >> x[i] >> d[i];
		}
		
		Solver solver{n, h, k, x, d};
		solver.solve();
	}
}
```
