/*
・きっちり自力AC！
・グラフに帰着、DAG、メモ化再帰
　依存先のないものから確定したくなるので、依存関係の有向辺を張りたくなる。
　問題文に、自身を作成できてしまうようなプロセスはないと明記されているので、
　DAGを構築してメモ化再帰すればOK。
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

void solve() {
    ll N, K;
    cin >> N >> K;
    vector<ll> C(N);
    cin >> C;
    vector<ll> P(K);
    cin >> P;
    P--;

    rep(i, K) {
        C[P[i]] = 0;
    }
    vvi nodes(N);
    rep(u, N) {
        ll sz;
        cin >> sz;
        rep(_, sz) {
            ll v;
            cin >> v;
            v--;
            nodes[u].eb(v);
        }
    }
    vector<ll> memo(N, -1LL);
    auto dfs = [&](auto &&f, ll u) {
        if (memo[u] != -1) {
            return memo[u];
        }
        ll res = C[u];
        if (nodes[u].size()) {
            ll sm = 0;
            for (auto v : nodes[u]) {
                sm += f(f, v);
            }
            chmin(res, sm);
        }
        return memo[u] = res;
    };
    vector<ll> ans(N);
    rep(i, N) {
        ans[i] = dfs(dfs, i);
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
