/*
・Eでどん詰まっても、残り時間20分でこっち通し切ったのはまだ評価できる…。
・きっちり自力AC！
・なもりグラフ、DFS
・サイクル見つけて、その先で木みたいになってる部分同士はOKなので、
　DFSで探して、UFとか使って連結成分にしておく。
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
    ll N;
    cin >> N;
    vvi nodes(N);
    rep(i, N) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    vector<bool> visited(N);
    set<ll> cycle;
    bool end = false;
    auto dfs = [&](auto&& f, ll u, ll prv) -> bool {
        if (visited[u]) {
            cycle.insert(u);
            return true;
        }
        visited[u] = true;
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            if (f(f, v, u)) {
                if (not end) {
                    if (not cycle.count(u)) {
                        cycle.insert(u);
                    } else {
                        end = true;
                    }
                }
                return true;
            }
        }
        return false;
    };
    dfs(dfs, 0, -1);
    UnionFind uf(N);
    vector<bool> visited2(N);
    auto dfs2 = [&](auto&& f, ll u, ll prv) -> void {
        visited2[u] = true;
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            uf.merge(u, v);
            if (cycle.count(v)) continue;
            f(f, v, u);
        }
    };
    rep(i, N) {
        if (not visited2[i] and not cycle.count(i)) {
            dfs2(dfs2, i, -1);
        }
    }

    ll Q;
    cin >> Q;
    rep(i, Q) {
        ll a, b;
        cin >> a >> b;
        a--; b--;
        if (uf.same(a, b)) {
            Yes();
        } else {
            No();
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
