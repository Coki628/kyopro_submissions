/*
・貪欲も検討した。無事AC。
・上位ビットから貪欲。ただし確定部分は最初に計上しておく。
　これで済むんだから、桁DPに走るのはさすがに悪手だよなぁ。。
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
    string S;
    cin >> S;
    ll N;
    cin >> N;
    ll M = S.size();

    reverse(ALL(S));
    ll ans = 0;
    rep(i, M - 1, -1, -1) {
        if (S[i] == '1') {
            ans += 1LL << i;
        }
    }
    rep(i, M - 1, -1, -1) {
        if (S[i] == '?' and (ans + (1LL << i) <= N)) {
            ans += 1LL << i;
        }
    }
    if (ans <= N) {
        print(ans);
    } else {
        print(-1);
    }
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
