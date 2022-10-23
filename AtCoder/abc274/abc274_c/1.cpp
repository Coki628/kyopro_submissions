/*
・なんとか自力AC。
・完全二分木
・しばらく何言ってるのかよく分からなかったんだけど、
　要は入力通りの木グラフ作って頂点1からDFSで深さ見る。
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
    auto A = LIST(N);

    ll L = N*2 + 2;
    vvi nodes(L);
    rep(i, N) {
        ll l = (i+1)*2;
        ll r = (i+1)*2 + 1;
        nodes[A[i]].eb(l);
        nodes[A[i]].eb(r);
    }

    vector<ll> ans(L);
    auto dfs = [&](auto&& f, ll u, ll d) -> void {
        ans[u] = d;
        for (auto v : nodes[u]) {
            f(f, v, d+1);
        }
    };
    dfs(dfs, 1, 0);
    ans.erase(ans.begin());
    print(ans, '\n');
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
