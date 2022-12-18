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
