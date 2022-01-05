/*
・これはランダムテストの正解生成用の愚直解。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_src/base.hpp"

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

// グリッドを時計回りに90度回転
vector<string> rot90(const vector<string> &grid) {
    int H = grid.size();
    int W = grid[0].size();
    vector<string> res(W, string(H, '*'));
    rep(i, H) {
        rep(j, W) {
            res[j][H-i-1] = grid[i][j];
        }
    }
    return res;
}

// 縦反転
vector<string> flip_h(const vector<string> &grid) {
    int H = grid.size();
    int W = grid[0].size();
    vector<string> res(W, string(H, '*'));
    rep(j, W) {
        rep(i, H) {
            res[i][j] = grid[H-i-1][j];
        }
    }
    return res;
}

// 横反転
vector<string> flip_w(const vector<string> &grid) {
    int H = grid.size();
    int W = grid[0].size();
    vector<string> res(W, string(H, '*'));
    rep(i, H) {
        rep(j, W) {
            res[i][j] = grid[i][W-j-1];
        }
    }
    return res;
}

void solve() {
    ll N, Q;
    cin >> N >> Q;

    vector<string> naive(N, string(N, '0'));
    
    rep(i, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ld x, y;
            cin >> x >> y;
            x--; y--;
            naive[x][y] = naive[x][y] == '0' ? '1' : '0';
        } elif (op == 2) {
            char c;
            cin >> c;
            if (c == 'A') {
                naive = rot90(naive);
            } else {
                naive = rot90(rot90(rot90(naive)));
            }
        } else {
            char c;
            cin >> c;
            if (c == 'A') {
                naive = flip_h(naive);
            } else {
                naive = flip_w(naive);
            }
        }
    }
    rep(i, N) {
        print(naive[i]);
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
