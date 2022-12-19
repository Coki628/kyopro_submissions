/*
・自力ならず。。これは悔しい。
・グラフに帰着、最大全域木
・題意の「2つ選んで1つは再利用もう1つは破棄」という操作が、
　グラフに閉路を作らないように辺を張る操作と一致する。
　これに気付けないと何やっても無理だと思う。
　で、気付きさえすれば、制約から全ペア列挙はできるので、
　全ての辺を用意して、MSTの最大版やればいい。
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
    vector<ll> A(N);
    cin >> A;

    vector<tuple<ll, ll, ll>> edges;
    rep(i, N) {
        rep(j, N) {
            if (i == j) {
                continue;
            }
            edges.eb((pow(A[i], A[j], M) + pow(A[j], A[i], M)) % M, i, j);
        }
    }
    sort(edges.rbegin(), edges.rend());
    UnionFind uf(N);
    ll ans = 0;
    for (auto [c, u, v] : edges) {
        if (not uf.same(u, v)) {
            uf.merge(u, v);
            ans += c;
        }
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
