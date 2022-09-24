/*
・なんとか自力AC！
・最小全域木
・空港・港を超頂点にしてN+2のグラフで考える。
　空港・港は使うなら遠慮なく使う方がいいし、使わないなら1個も繋がない方がいい。
　よってそれらを使う/使わないで4通りのMSTやって最小取る。
　どっちも使わない場合は連結になれないこともありそうなので連結チェックもする。
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
    auto X = LIST(N);
    auto Y = LIST(N);
    vector<array<ll, 3>> edges;
    rep(i, M) {
        ll a, b, z;
        cin >> a >> b >> z;
        a--; b--;
        edges.pb({z, a, b});
    }
    rep(i, N) {
        edges.pb({X[i], i, N});
        edges.pb({Y[i], i, N+1});
    }

    sort(ALL(edges));
    ll ans = INF;
    UnionFind uf(N+2);
    ll curans = 0;
    for (auto [c, u, v] : edges) {
        if (not uf.same(u, v)) {
            curans += c;
            uf.merge(u, v);
        }
    }
    chmin(ans, curans);
    uf = UnionFind(N+2);
    curans = 0;
    for (auto [c, u, v] : edges) {
        if (v == N) continue;
        if (not uf.same(u, v)) {
            curans += c;
            uf.merge(u, v);
        }
    }
    chmin(ans, curans);
    uf = UnionFind(N+2);
    curans = 0;
    for (auto [c, u, v] : edges) {
        if (v == N+1) continue;
        if (not uf.same(u, v)) {
            curans += c;
            uf.merge(u, v);
        }
    }
    chmin(ans, curans);
    uf = UnionFind(N);
    curans = 0;
    for (auto [c, u, v] : edges) {
        if (v == N or v == N+1) continue;
        if (not uf.same(u, v)) {
            curans += c;
            uf.merge(u, v);
        }
    }
    if (uf.size() == 1) {
        chmin(ans, curans);
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
