/*
・きっちり自力AC！Dで詰まって早めにこっち通したまでは良かったんだけどな…。
・クエリ系、BFS
・毎回見る状態は少ないので、mapとかで状態持って毎クエリBFSやる。
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
    ll N, M;
    cin >> N >> M;
    vvi nodes(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    ll Q;
    cin >> Q;
    rep(i, Q) {
        ll x, k;
        cin >> x >> k;
        x--;
        
        queue<ll> que;
        map<ll, ll> memo;
        memo[x] = 0;
        que.push(x);
        while (que.size()) {
            auto u = que.front(); que.pop();
            if (memo[u] == k) continue;
            for (auto v : nodes[u]) {
                if (not memo.count(v)) {
                    memo[v] = memo[u] + 1;
                    que.push(v);
                }
            }
        }
        ll res = 0;
        for (auto [k, v] : memo) {
            res += k + 1;
        }
        print(res);
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
