/*
・自力ならず。。
・三分探索
・なんか色々迷走してしまったんだけど、翌朝ちゃんと考えたら、
　決め打ちさぶたんすれば、ある座標xに集まる所要時間f(x)をO(N)で求められればいいので、
　中身はすごく素直に判定処理書けばいいだけだった…。
　昨日はこの「ある座標xに集まる所要時間f(x)」はlogNくらいで高速に求めなくちゃいけないような
　気がしちゃってたんだよね。。まじで脳みそ付いてなかったー。
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

#include "common/trisearch_real.hpp"

void solve() {
    ll N;
    cin >> N;
    auto X = LIST(N);
    auto T = LIST(N);

    ld mn = min(X);
    ld mx = max(X);
    auto [id, val] = trisearch_min(mn, mx, [&](ld x) -> ld {
        ld res = 0;
        rep(i, N) {
            chmax(res, abs(X[i]-x)+T[i]);
        }
        return res;
    }, 100);
    print(id);
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
