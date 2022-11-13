/*
・きっちり自力AC！
・01BFS
・反転の状態を持って01BFSする。
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
    ll N, M, K;
    cin >> N >> M >> K;
    vvpll nodes(N);
    rep(i, M) {
        ll u, v, a;
        cin >> u >> v >> a;
        u--; v--;
        nodes[u].eb(v, a);
        nodes[v].eb(u, a);
    }
    vector<ll> S(K);
    cin >> S;
    rep(i, K) S[i]--;
    vector<ll> has(N);
    for (auto s : S) {
        has[s] = 1;
    }

    int s = 0;
    auto res = listnd(2, N, INF);
    deque<pll> que;
    res[1][s] = 0;
    que.pb({1, s});
    while (!que.empty()) {
        auto [p, u] = que.front(); que.pop_front();
        for (auto [v, a] : nodes[u]) {
            if (a != p) continue;
            if (chmin(res[p][v], res[p][u]+1)) {
                que.pb({p, v});
            }
        }
        if (has[u]) {
            if (chmin(res[1-p][u], res[p][u])) {
                que.push_front({1-p, u});
            }
        }
    }
    ll ans = min(res[0][N-1], res[1][N-1]);
    if (ans == INF) {
        ans = -1;
    }
    print(ans);
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
