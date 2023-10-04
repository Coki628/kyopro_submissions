/*
・約数、倍数、包除原理、ビット全探索
・想定解愚直だったけど、一般化したやつやった。練習にはなった。
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

void solve() {
    ll N;
    cin >> N;
    vector<ll> A = {3, 5, 7};
    ll M = A.size();

    ll ans = 0;
    rep(bit, 1, 1LL << M) {
        ll cur = 1;
        rep(i, M) {
            if (bit >> i & 1) {
                cur = lcm(cur, A[i]);
            }
        }
        // N以下のcurの倍数の個数
        ll cnt = N / cur;
        if (popcount(bit) % 2) {
            ans += cnt;
        } else {
            ans -= cnt;
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
