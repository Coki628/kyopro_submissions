/*
・期待値DPのこと
・操作回数じゃない期待値DP
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
    vvl A(N);
    vector<ll> sz(N);
    rep(i, N) {
        cin >> sz[i];
        A[i] = LIST(sz[i]);
    }
    
    vector<mint> memo(N+1);
    vector<bool> visited(N+1);
    auto rec = [&](auto&& f, ll i) -> mint {
        if (i < 0) return 0;
        if (visited[i]) return memo[i];
        mint exp = 0;
        rep(j, sz[i]) {
            // (この先でかかる分+今回かかる分) * そうなる確率
            exp += (f(f, i-1)*pow(10, tostr(A[i][j]).size(), MOD)+A[i][j]) / sz[i];
        }
        memo[i] = exp;
        visited[i] = true;
        return exp;
    };
    auto ans = rec(rec, N-1);
    rep(i, N) {
        ans *= sz[i];
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
