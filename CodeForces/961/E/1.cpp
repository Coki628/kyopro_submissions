/*
・dojo set_e_6_1
・きっちり自力AC！
・左端固定で自分より先だけ見る。
　[i+1,min(A[i], N))の範囲でi+1以上な個数が欲しいので、WMでぶん殴った。
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

#include "segment/WaveletMatrix.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    WaveletMatrix<ll, 33> wm(A);
    ll ans = 0;
    rep(i, N-1) {
        ans += wm.range_freq(i+1, min(A[i], N), i+1, MOD);
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
