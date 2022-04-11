/*
・きっちり自力AC！
・逆操作、整数BFS
・逆操作にすれば、0からの最短距離をBFSで任意の答えが出る。
　ちょっと悩んだのが、逆操作が除算だと、今回はmodが素数でもないので、
　逆元が取れないから行き先が分からない。
　これは、単純に辺を張る向きを逆にすることで対応できた。
　(入次の頂点から計算して、出次の頂点を求める。)
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

#include "graph/bfs.hpp"

void solve() {
    const int mod = 32768;
    ll N;
    cin >> N;
    auto A = LIST(N);

    ll L = mod;
    vvi nodes(L);
    rep(v, L) {
        ll u = (v+1) % mod;
        nodes[u].eb(v);
        u = (v*2) % mod;
        nodes[u].eb(v);
    }
    auto dist = bfs(nodes, {0});

    vector<ll> ans(N);
    rep(i, N) {
        ans[i] = dist[A[i]];
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
