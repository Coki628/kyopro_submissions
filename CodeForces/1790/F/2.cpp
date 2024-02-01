/*
参考：https://twitter.com/noimi_kyopro/status/1619015319414247424
・もう1個の方針。こっちで解いた人も結構いるっぽい。
・木グラフ、最短距離、重心分解
・cf342_eでやったのとほぼ同じ感じにする。
　重心分解上の木での親を持っておけば、
　ある頂点から木全体への更新/取得がlog回でできる。
　今回は重みなし最短距離だけど、HLDのパスクエリの組み合わせると、
　なんか色々取れそうな気がする。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
#include "graph/centroid_decomposition.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<int> C(N);
    cin >> C;
    C--;
    vector<ll> inv(N);
    rep(i, N) {
        inv[C[i]] = i;
    }
    vvi nodes(N);
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    HeavyLightDecomposition hld(nodes);
    auto par = centroid_decomposition(nodes);
    vector<ll> ans, dist(N, INF);
    ll cur = INF;
    rep(i, N) {
        ll u = C[i];
        ll v = u;
        // 取得
        while (v != -1) {
            chmin(cur, dist[v] + hld.dist(u, v));
            v = par[v];
        }
        dist[u] = 0;
        v = u;
        // 更新
        while (v != -1) {
            // この時に比較に用いる距離は元の木のものを使う
            chmin(dist[v], (ll)hld.dist(u, v));
            v = par[v];
        }
        if (i > 0) {
            ans.eb(cur);
        }
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
