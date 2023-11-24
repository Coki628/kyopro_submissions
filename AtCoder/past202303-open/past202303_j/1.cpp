/*
・自力AC！
・グリッド、サイクルシフト、2次元ロリハ
・最初、行側にもサイクルシフトできるものと思ってしまって時間かかった。
　列側だけだったので、これなら多分1次元の普通のロリハでも大丈夫だったっぽい。
　2次元ロリハは久々だったのもあり、体裁整えるのに結構時間を取られてしまった。
　今回合わせて3回目の登場っぽいけど、毎回使い方ほぼ一緒っぽいのでライブラリ化するか。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
// #define CAST_MINT_TO_LL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

#include "string/RollingHash.hpp"
#include "grid/transpose.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    ll W2 = W * 2;
    auto grid1 = listnd(H, W2, '*');
    auto grid2 = listnd(H, W, '*');
    rep(h, H) {
        rep(w, W) {
            cin >> grid1[h][w];
        }
    }
    rep(h, H) {
        rep(w, W) {
            cin >> grid2[h][w];
        }
    }
    rep(h, H) {
        rep(w, W2) {
            grid1[h][w] = grid1[h % H][w % W];
        }
    }

    RollingHash rh1, rh2;
    auto rowhashs = listnd(H, W2 - W + 1, (uint64_t)0);
    rep(i, H) {
        auto table = rh1.build(grid1[i]);
        rep(j, W2 - W + 1) {
            ll k = j + W;
            rowhashs[i][j] = rh1.query(table, j, k);
        }
    }
    rowhashs = transpose(rowhashs);
    auto colhashs = listnd(W2 - W + 1, H - H + 1, (uint64_t)0);
    rep(i, W2 - W + 1) {
        auto table = rh2.build(rowhashs[i]);
        rep(j, H - H + 1) {
            ll k = j + H;
            colhashs[i][j] = rh2.query(table, j, k);
        }
    }
    colhashs = transpose(colhashs);

    vector<uint64_t> ptn_hashs(H);
    rep(i, H) {
        ptn_hashs[i] = rh1.get_hash(grid2[i], 0, W);
    }
    auto target = rh2.get_hash(ptn_hashs, 0, H);

    rep(i, H - H + 1) {
        rep(j, W2 - W + 1) {
            if (colhashs[i][j] == target) {
                Yes();
                return;
            }
        }
    }
    No();
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
