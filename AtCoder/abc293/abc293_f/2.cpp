/*
参考：https://atcoder.jp/contests/abc293/submissions/39635832
・自力ならず。
・N進変換、実験エスパー、NとN-1で約数列挙、高速素因数分解、メモ化
・想定解じゃないけどsiroさんのツイートを参考に。
　候補となりうる値はNとN-1の約数のみなので、
　10^18までいける約数列挙をして、答えをメモ化しておけば通る。
・N進変換のバグが見つかったりしたので良かった。
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

#include "numbers/dton.hpp"
#include "numbers/FastPrimeFactorization.hpp"

map<ll, ll> memo;

void solve() {
    ll N;
    cin >> N;

    if (memo.count(N)) {
        print(memo[N]);
        return;
    }

    ll ans = 0;
    for (auto x : {N, N - 1}) {
        for (auto b : FastPrimeFactorization::divisors(x)) {
            if (b == 1) continue;
            auto res = dton(N, b);
            UNIQUE(res);
            if (res == "01" or res == "0" or res == "1") {
                ans++;
            }
        }
    }
    memo[N] = ans;
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
