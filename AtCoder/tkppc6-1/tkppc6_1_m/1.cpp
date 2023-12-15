/*
・きまぐれ埋め。やっぱりグラフ問は楽しい。
・きっちり自力AC！
・木グラフ、頂点属性、LCA
・DFS、HLD*セグ木、パスクエリ
・駒が移動できる頂点は、いずれかのペアでのLCAとなりうる頂点のみ。
　その条件さえ満たせば、自身から根に向かういずれの頂点へも移動可。
　木DPで駒を葉方面から引っ張ってきて、2つ以上の子頂点から駒が取れる頂点は上記条件を満たす。
　これに先に印をつけた状態で、HLD*最大値セグ木に各頂点のスコアを乗せる。
　最後に各駒から実際に根に向かってパスクエリ投げて最大値取ればOK。
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

#include "graph/HeavyLightDecomposition.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> P(N - 1);
    cin >> P;
    P--;
    vvi nodes(N);
    rep(i, 1, N) {
        nodes[P[i - 1]].eb(i);
    }
    vector<ll> A(N);
    cin >> A;
    ll M;
    cin >> M;
    vector<ll> V(M);
    cin >> V;
    V--;
    vector<ll> C(N);
    rep(i, M) {
        C[V[i]]++;
    }

    vector<ll> dp(N), canuse(N);
    auto dfs = [&](auto &&f, ll u, ll prv) -> void {
        ll hascnt = 0;
        if (C[u] > 0) hascnt++;
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            f(f, v, u);
            dp[u] += dp[v];
            if (dp[v] > 0) hascnt++;
        }
        if (hascnt >= 2) {
            canuse[u] = true;
        }
        dp[u] += C[u];
    };
    dfs(dfs, 0, -1);

    HeavyLightDecomposition hld(nodes);
    auto seg = get_segment_tree(N, [](ll a, ll b) { return max(a, b); }, -INF);
    rep(u, N) {
        if (canuse[u]) {
            seg.set(hld[u], A[u]);
        }
    }
    seg.build();

    ll ans = 0;
    for (auto u : V) {
        ll res = hld.query(
            u, 0, -INF,
            [&](ll a, ll b) { return seg.query(a, b); },
            [](ll a, ll b) { return max(a, b); }
        );
        ans += max(res, A[u]);
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
