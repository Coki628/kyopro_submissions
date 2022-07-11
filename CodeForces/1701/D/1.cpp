/*
・終了後自力AC。
・二分探索、区間スケジューリング系、優先度付きキュー
・条件を満たすA[i]は区間になり、にぶたん2回で見つかる。
　これを区間スケジューリングっぽく右端が早いの優先で使う。
　左端が来た所でプリキューに詰めるといい感じにできる。
　スケジューリングにもうちょい早く気付いてれば…。
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

#include "mystl/my_set.hpp"

#include "acl/maxflow.hpp"
using namespace atcoder;

void solve() {
    ll N;
    cin >> N;
    auto B = LIST(N);

    vvpll adj(N+1);
    rep(i, N) {
        ll l = bisearch_min(0, N+1, [&](ll a) {
            return (i+1)/a <= B[i];
        });
        ll r = bisearch_min(0, N+1, [&](ll a) {
            return (i+1)/a < B[i];
        });
        // debug(mkp(l, r));
        adj[l].eb(r, i);
    }

    vector<ll> ans(N);
    priority_queue<pll, vector<pll>, greater<pll>> que;
    rep(a, 1, N+1) {
        for (auto [r, i] : adj[a]) {
            que.push({r, i});
        }
        auto [_, i] = que.top(); que.pop();
        ans[i] = a;
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
