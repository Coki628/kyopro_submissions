/*
・自力AC！
・Aにしては色々実装が面倒。簡単に言えば、
　ソートして後ろから交互に使ってくみたいにするだけなんだけど…。
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
    auto B = LIST(N);

    vvl adj(2);
    rep(i, N) {
        adj[A[i]].eb(B[i]);
    }
    rep(i, 2) {
        sort(ALL(adj[i]));
    }
    if (adj[0].size() < adj[1].size()) {
        swap(adj[0], adj[1]);
    }
    ll ans = 0;
    while (adj[0].size() and adj[1].size()) {
        ans += adj[0].back()*2 + adj[1].back()*2;
        if (adj[0].size() == adj[1].size() and adj[1].size() == 1) {
            ans -= min(adj[0].back(), adj[1].back());
        }
        adj[0].pop_back(); adj[1].pop_back();
    }
    for (auto b : adj[0]) {
        ans += b;
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
