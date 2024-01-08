/*
参考：https://nyaannyaan.github.io/library/tree/tree-hash.hpp
　　　https://snuke.hatenablog.com/entry/2017/02/03/054210
・根付き木のハッシュ、木の同型判定
・話だけ聞いたことあって未履修だったので、今回やってみた。
　ハッシュで同型判定ができれば、後はそのハッシュを使って上から部分木のハッシュを見ていく。
　全て偶数個なら対称になるのでOK、1つだけ奇数個のものがあれば潜る、2つ以上あったらNG、となる。
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

#include "graph/TreeHash.hpp"

void solve(int t) {
    ll N;
    cin >> N;
    vvi nodes(N);
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    TreeHash th(N);
    auto hash = th.get_hash(nodes, 0);
    auto dfs = [&](auto &&f, ll u, ll prv) -> bool {
        map<ull, vector<ll>> C;
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            C[hash[v]].eb(v);
        }
        ll oddcnt = 0, w = -1;
        for (auto& [k, vec] : C) {
            if (vec.size() % 2 == 1) {
                oddcnt++;
                w = vec[0];
            }
        }
        if (oddcnt > 1) {
            return false;
        } else if (oddcnt == 1) {
            if (!f(f, w, u)) {
                return false;
            }
        }
        return true;
    };
    YESNO(dfs(dfs, 0, -1));
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
    rep(t, T) solve(t);

    return 0;
}
