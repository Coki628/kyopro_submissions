/*
・きっちり自力AC！
・グリッド、実装、二分探索
・大変。mapにvectorの隣接リストを行列それぞれ持って、
　何もない行(列)なら制限なく進む、あるならにぶたんする。
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
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll H, W, sh, sw;
    cin >> H >> W >> sh >> sw;
    ll N;
    cin >> N;
    map<ll, vector<ll>> rows, cols;
    rep(i, N) {
        ll h, w;
        cin >> h >> w;
        rows[w].eb(h);
        cols[h].eb(w);
    }
    for (auto& [k, v] : rows) {
        v.eb(0);
        v.eb(H+1);
        sort(ALL(v));
    }
    for (auto& [k, v] : cols) {
        v.eb(0);
        v.eb(W+1);
        sort(ALL(v));
    }

    ll Q;
    cin >> Q;
    ll ch = sh, cw = sw;
    rep(i, Q) {
        char d;
        ll l;
        cin >> d >> l;
        if (d =='L') {
            if (cols.count(ch)) {
                ll res = *--lower_bound(ALL(cols[ch]), cw);
                cw = max(cw-l, res+1);
            } else {
                cw = max(cw-l, 1LL);
            }
        } elif (d == 'R') {
            if (cols.count(ch)) {
                ll res = *upper_bound(ALL(cols[ch]), cw);
                cw = min(cw+l, res-1);
            } else {
                cw = min(cw+l, W);
            }
        } elif (d == 'U') {
            if (rows.count(cw)) {
                ll res = *--lower_bound(ALL(rows[cw]), ch);
                ch = max(ch-l, res+1);
            } else {
                ch = max(ch-l, 1LL);
            }
        } else {
            if (rows.count(cw)) {
                ll res = *upper_bound(ALL(rows[cw]), ch);
                ch = min(ch+l, res-1);
            } else {
                ch = min(ch+l, H);
            }
        }
        print(mkp(ch, cw));
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
