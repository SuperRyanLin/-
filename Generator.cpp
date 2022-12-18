#include "testlib.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int mxn = atoi(argv[1]);
    int mxb = 1e9;
    int testcase = atoi(argv[2]);
    
    int n = rnd.next(3, mxn / 2) * 2;
    cout << n << '\n';
    
    for (int i = 0; i < n - 1; i++) cout << rnd.next(0, mxb) << ' ';
    cout << rnd.next(0, mxb) << '\n';
    
    if (testcase == 1) {
        cout << rnd.next(1, 9) << " pieces\n";
        for (int i = 1; i < n; i++) cout << rnd.next(1, 8) << " pieces\n";
    } else if (testcase == 2) {
        for (int i = 0; i < n; i++) cout << "level " << rnd.next(1, 13) << '\n';
    } else if (testcase == 3) {
        int pl = rnd.next(0, 1);
        if (pl) cout << "level " << rnd.next(1, 13) << '\n';
        else cout << rnd.next(1, 9) << " pieces\n";
        for (int i = 1; i < n; i++) {
            pl = rnd.next(0, 1);
            if (pl) cout << "level " << rnd.next(1, 13) << '\n';
            else cout << rnd.next(1, 8) << " pieces\n";
        }
    }
}
