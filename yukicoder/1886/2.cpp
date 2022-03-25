/*
・自力AC！これは通せて結構嬉しい。
・数え上げ、主客転倒、wolframalpha
・値毎の寄与で考えたら、区間長kと値pの2重ループまでは作れた。
　(pより小さいp-1個からk-1個選ぶ*k個の並び*(N-k)個の並び*この区間長の区間の数*p)
　で、この内側のループから関係ないのを外に出すと、
　for p in range(k, N+1): nCr(p-1, k-1)*p
　くらいシンプルになって、これなら何か出そうってwolframに投げると
　-(N+1)*(k-N-1)*nCr(N, k-1)/(k+1) みたいのが出てきたので勝ち。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;

    ModTools<mint> mt(N);
    rep(k, 1, N+1) {
        mint res = 0;
        // rep(p, k, N+1) {
        //     res += mt.nCr(p-1, k-1)*p;
        // }
        // to wolframalpha: for p=k to n sum(nCr(p-1, k-1)*p)
        res = (mint)-(N+1)*(k-N-1)*mt.nCr(N, k-1)/(k+1);
        res *= mt.fact(k)*mt.fact(N-k)*(N-k+1);
        print(res);
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
