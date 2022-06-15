/*
・これは部分点64点。結局これより先には進めず。
・毎クエリにぶたんしてダイクストラやる。今回は所持金が減っていく形なので、
　いつもと勝手が逆になるからちゃんと動くか心配だったけど大丈夫だった。
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
    ll N, M, Q, L;
    cin >> N >> M >> Q >> L;
    vvpll nodes(N);
    rep(i, M) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        nodes[u].eb(v, c);
        nodes[v].eb(u, c);
    }

    rep(i, Q) {
        ll t;
        cin >> t;
        t--;
        ll res = bisearch_min(0, L+1, [&](ll x) {
            vector<ll> res(N, -INF);
            priority_queue<pll, vector<pll>> que;
            res[0] = x;
            que.push({x, 0});
            while (que.size()) {
                auto [dist, u] = que.top(); que.pop();
                if (u == t) break;
                if (res[u] > dist) continue;
                for (auto [v, t] : nodes[u]) {
                    ll nxdist = t == 1 ? dist - 1 : dist / 2;
                    if (nxdist <= 0) continue;
                    if (chmax(res[v], nxdist)) {
                        que.push({nxdist, v});
                    }
                }
            }
            return res[t] > 0;
        });
        if (res > L) {
            print("Large");
        } else {
            print(res);
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
