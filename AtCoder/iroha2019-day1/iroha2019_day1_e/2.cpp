/*
・dojo set_e_5_c
・きっちり自力AC！
・前後に番兵置いて間の長さに応じて割り算。
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

void solve() {
    ll N, K, M;
    cin >> N >> K >> M;
    auto D = LIST(M);
    sort(ALL(D));
    D.insert(D.begin(), 0);
    D.eb(N+1);

    ll ans = 0;
    rep(i, M+1) {
        ans += (D[i+1]-D[i]-1) - (D[i+1]-D[i]-1)/K;
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
