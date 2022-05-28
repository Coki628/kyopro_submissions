/*
・なんとか自力AC！
・最近、近い考察の問題解いてて助かった…。(abc249_f)
・更新クエリは後ろから見る
・直近の更新の所でクエリをまとめて答えられるように先読みしておく。
　その上で、後ろから加算をシミュ。その直近の更新より手前のことはこのクエリには関係ないので、
　その時の更新値 + そこより先の加算分 - クエリが実際にある位置より先の加算分 が答え。
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

#include "segment/BIT2.hpp"

void solve() {
    ll H, W, Q;
    cin >> H >> W >> Q;

    vector<array<ll, 4>> qs;
    vector<vector<array<ll, 4>>> qs2(Q);
    vector<pll> upd(H);
    rep(i, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll wl, wr, x;
            cin >> wl >> wr >> x;
            wl--;

            qs.pb({op, wl, wr, x});
        } elif (op == 2) {
            ll h, x;
            cin >> h >> x;
            h--;

            upd[h] = {i, x};
            qs.pb({op, h, x, -1});
        } else {
            ll h, w;
            cin >> h >> w;
            h--; w--;

            qs2[upd[h].first].pb({i, h, w, upd[h].second});
            qs.pb({op, h, w, -1});
        }
    }

    BIT2<ll> bit(W);
    vector<ll> ans(Q);
    rep(i, Q-1, -1, -1) {
        ll op = qs[i][0];
        if (op == 1) {
            ll wl = qs[i][1], wr = qs[i][2], x = qs[i][3];
            bit.add(wl, wr, x);
        } elif (op == 2) {
        } else {
            ll h = qs[i][1], w = qs[i][2];
            // このクエリ返答以降の加算分は予め引いておく
            ans[i] -= bit[w];
        }
        // この時の更新値 + ここより先の加算分で答える
        for (auto [j, h, w, lastupd] : qs2[i]) {
            ans[j] += lastupd + bit[w];
        }
    }
    rep(i, Q) {
        if (qs[i][0] == 3) {
            print(ans[i]);
        }
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
