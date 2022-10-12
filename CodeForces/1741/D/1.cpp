/*
・自力AC！
・完全二分木、木DP、DFS
・完全二分木のグラフ構築して、部分木の先頭頂点とコスト持って木DP、
　戻りで左の子の先頭頂点のが大きかったら左右の辺をスワップしてコストを++、
　これで改変したグラフを再度DFSで前から舐めて、
　葉の番号が昇順になってればOKなので先程のコストを出力、とした。(これももっと簡単にできそう？)
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
    ll M;
    cin >> M;
    auto P = LIST(M);

    ll N = M * 2;
    vvi nodes(N);
    rep(i, 1, M) {
        assert(i*2+1 < N);
        nodes[i].eb(i*2);
        nodes[i].eb(i*2+1);
    }

    vector<ll> val(N), cost(N);
    auto dfs1 = [&](auto&& f, ll u) {
        if (u >= M) {
            assert(u-M < M);
            val[u] = P[u-M];
            return;
        }
        ll l = nodes[u][0], r = nodes[u][1];
        f(f, l);
        f(f, r);
        cost[u] = cost[l] + cost[r];
        if (val[r] < val[l]) {
            val[u] = val[r];
            cost[u]++;
            swap(nodes[u][0], nodes[u][1]);
        } else {
            val[u] = val[l];
        }
    };
    dfs1(dfs1, 1);

    vector<ll> ans;
    auto dfs2 = [&](auto&& f, ll u) {
        if (u >= M) {
            assert(u-M < M);
            ans.eb(P[u-M]);
            return;
        }
        ll l = nodes[u][0], r = nodes[u][1];
        f(f, l);
        f(f, r);
    };
    dfs2(dfs2, 1);

    if (ans == sorted(ans)) {
        print(cost[1]);
    } else {
        print(-1);
    }
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
