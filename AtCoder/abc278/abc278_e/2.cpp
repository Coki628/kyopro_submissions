/*
・2次元累積和
・TLで見た方針。これだと添字ゲーしなくていいしすっごい楽…。
　値の最大が小さいのを見た時に、これに気付くべきだったんだよなぁ。
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

#include "datastructure/Accumulate2D.hpp"

void solve() {
    ll H, W, N, h, w;
    cin >> H >> W >> N >> h >> w;
    auto grid = listnd(H, W, 0);
    cin >> grid;

    vector<Accumulate2D<ll>> acc(N+1, {H, W});
    vector<ll> C(N+1);
    rep(ch, H) {
        rep(cw, W) {
            acc[grid[ch][cw]].add(ch, cw, 1);
            C[grid[ch][cw]]++;
        }
    }
    rep(i, N+1) {
        acc[i].build();
    }

    rep(ch, H-h+1) {
        vector<ll> ans;
        rep(cw, W-w+1) {
            ll cnt = 0;
            rep(i, N+1) {
                ll has = C[i] - acc[i].query(ch, cw, ch+h, cw+w);
                if (has) {
                    cnt++;
                }
            }
            ans.eb(cnt);
        }
        print(ans);
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
