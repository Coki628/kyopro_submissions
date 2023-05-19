/*
・過去SCC使ってたけど、BFSだけでいい気がしたのでやってみた。無事AC。
・BFS応用、経路復元
・ようは最小サイクルを探す。2乗が効く制約なので、方法は各頂点を始点としてBFS試す。
　ある頂点からの最小サイクルであれば、BFSは常に短い方を先にやるので最初に始点に戻った経路でOK。
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
        u--, v--;
        nodes[u].eb(v);
    }

    auto bfs = [](const vvi &nodes, const int &src) {
        int N = nodes.size();
        vector<ll> dist(N, INF), prv(N, -1), res;
        queue<int> que;
        dist[src] = 0;
        que.push(src);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (auto v : nodes[u]) {
                if (v == src) {
                    ll w = u;
                    while (w != -1) {
                        res.eb(w);
                        w = prv[w];
                    }
                    return res;
                }
                if (chmin(dist[v], dist[u] + 1)) {
                    prv[v] = u;
                    que.push(v);
                }
            }
        }
        return res;
    };

    vector<ll> ans;
    rep(i, N) {
        auto res = bfs(nodes, i);
        if (!res.empty() and (ans.empty() or ans.size() > res.size())) {
            ans = res;
        }
    }
    if (ans.empty()) {
        print(-1);
    } else {
        ans++;
        print(ans.size());
        print(ans, '\n');
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
