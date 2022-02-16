/*
・dojo set_d_4_1
・きっちり自力AC！
・尺取り法
・それはまあ尺取りでうまくいくって覚えてたから…。
　でも今見ると累積和にぶたんでも行けそうだね。単調性あるから。
・尺取りは相変わらず添字バグって一発じゃ行かない。ダメだなー。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

    ll ans = 0, sm1 = 0, sm2 = 0, r = 0;
    rep(l, N) {
        while (r < N and sm1+A[r] == (sm2^A[r])) {
            sm1 += A[r];
            sm2 ^= A[r];
            r++;
        }
        if (sm1 == sm2) {
            ans += r-l;
        }
        sm1 -= A[l];
        sm2 ^= A[l];
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
