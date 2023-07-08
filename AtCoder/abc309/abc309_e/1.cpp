/*
・きっちり自力AC！
・木の走査、DFS
・根からDFS、前から更新。その人の保険でchmaxして1減らしながら潜る。
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
    vector<ll> P(N - 1);
    cin >> P;
    P--;
    vvi nodes(N);
    rep(i, N - 1) {
        nodes[P[i]].eb(i + 1);
    }
    vector<ll> A(N);
    rep(i, M) {
        ll x, y;
        cin >> x >> y;
        x--;
        y++;
        chmax(A[x], y);
    }

    ll ans = 0;
    auto dfs = [&](auto&& f, ll u, ll a) -> void {
        chmax(a, A[u]);
        if (a > 0) {
            ans++;
        }
        for (auto v : nodes[u]) {
            f(f, v, max(a - 1, 0LL));
        }
    };
    dfs(dfs, 0, 0);
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
