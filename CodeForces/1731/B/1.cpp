/*
・なんとか自力AC。
・BM
・真ん中をジグザグに進むのが最善。答えは綺麗な数列になるけど、
　O(1)で表す方法は分からないので、途中まで愚直に作ってBMで殴った。
・公式解説見た。答えはシグマの式2つで表せる。(これは多分分かった。)
　ここからNについての式に自力で式変形する方法は分からないけど、
　このシグマの式をWolframAlphaに
　(sum(i^2) from i=1 to n) + (sum(i*(i+1)) from i=1 to n-1)
　とかって投げると、ちゃんとNについての式を出してくれる。
　こういうので詰まったらWolframに投げるはやっぱやった方がいいな…。
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

#include "math/FormalPowerSeries.hpp"
#include "math/BM.hpp"

void solve() {
    ll N;
    cin >> N;

    ll K = N * 2 - 2;
    ll K2 = min(K, 50LL);
    mint cur = 1;
    FPS<mint> F = {cur};
    while (F.size() < K2) {
        auto prv = F.back();
        F.eb(prv + cur);
        cur++;
        prv = F.back();
        F.eb(prv + cur);
    }
    rep(i, 1, F.size()) {
        F[i] += F[i - 1];
    }
    mint res = BM(F, K);
    mint ans = res *= 2022;
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
