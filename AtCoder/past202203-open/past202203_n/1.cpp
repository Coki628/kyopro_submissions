/*
・終了1分前なんとか自力AC！
　まあ色々紆余曲折あったんだけど最終的にFFTいけそうと気付いて、
　出して1WAが出て少し考えた後、残り2分くらいでmintを2つに増やしてる時はさすがに手が震えたわ。
・FFT
・よく見ると取りうる値の範囲は広くないので、下駄履かせてFFT。
　mintキラーがちゃんと入ってるようなので2種類以上のmintでやる。
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
using mint1 = ModInt<MOD>;
using mint2 = ModInt<1000000007>;
#include "template.hpp"

#include "math/FormalPowerSeries.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    ll mx = max(A);
    FPS<mint1> F11(mx*2+1), F12(mx*2+1);
    FPS<mint2> F21(mx*2+1), F22(mx*2+1);
    rep(i, N) {
        F11[mx-A[i]]++;
        F12[mx+A[i]]++;
        F21[mx-A[i]]++;
        F22[mx+A[i]]++;
    }
    auto res1 = F11 * F12;
    auto res2 = F21 * F22;
    ll ans = 0;
    rep(i, res1.size()) {
        if (res1[i] != 0 or res2[i] != 0) ans++;
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
