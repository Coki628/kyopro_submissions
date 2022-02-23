/*
・自力AC！
・更新は逆操作
・Cよりこっちのが考察は早かった。更新は逆操作。
　逆から見ていって、まだ白いマスが1マスでもあればans *= Kする。
　その判定は使用済の行,列をsetとかで持っておけばできる。
　「まだその行を使ってないかつまだその列を使ってない」は自明として、
　「まだその行を使ってないかつ、その列が1マスでも空いている」とその逆を見る。
　細部詰めれてなくてのWA3つが痛かった。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

void solve() {
    ll H, W, K, Q;
    cin >> H >> W >> K >> Q;
    vector<pll> qs;
    rep(i, Q) {
        ll h, w;
        cin >> h >> w;
        qs.eb(h, w);
    }

    reverse(ALL(qs));
    set<ll> rows, cols;
    mint ans = 1;
    for (auto& [h, w] : qs) {
        if (not rows.count(h) and not cols.count(w)) {
            ans *= K;
        } elif (
            not rows.count(h) and cols.size() < W or
            not cols.count(w) and rows.size() < H
        ) {
            ans *= K;
        }
        rows.insert(h);
        cols.insert(w);
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
