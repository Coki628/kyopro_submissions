/*
参考：https://codeforces.com/contest/1899/submission/233144116
・別解2、かいけーさんがやってた。
・順列、クエリ先読み、DFS、マージテク
・部分木に含まれる番号を、マージテクを使うことで陽に持てる。
　setでマージテクしていくこと自体は分かるが、
　これの場合順列Pそのままじゃ無理でrev作らないとダメっぽい。
　いまいち何がOKで何がダメなのか掴み切れてない。
*/

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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

#include "graph/HeavyLightDecomposition.hpp"
#include "datastructure/WaveletMatrix.hpp"

void solve() {
    int N, Q;
    cin >> N >> Q;
    vvi nodes(N);
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }
    vector<int> P(N);
    cin >> P;
    P--;

    vector<int> rev(N);
    rep(i, N) {
        rev[P[i]] = i;
    }
    vv<array<int, 3>> qs(N);
    rep(i, Q) {
        int l, r, x;
        cin >> l >> r >> x;
        l--, x--;
        qs[x].pb({l, r, (int)i});
    }
    vector<string> ans(Q);
    auto dfs = [&](auto &&f, ll u, ll prv) -> set<int> {
        set<int> cur = {rev[u]};
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            auto res = f(f, v, u);
            if (res.size() > cur.size()) {
                swap(res, cur);
            }
            for (auto w : res) {
                cur.insert(w);
            }
        }
        for (auto [l, r, i] : qs[u]) {
            auto itr = cur.lower_bound(l);
            if (itr != cur.end() and *itr < r) {
                ans[i] = "YES";
            } else {
                ans[i] = "NO";
            }
        }
        return cur;
    };
    dfs(dfs, 0, -1);
    print(ans, '\n');
    print();
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
