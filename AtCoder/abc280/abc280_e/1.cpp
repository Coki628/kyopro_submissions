/*
・きっちり自力AC！
・期待値DP、メモ化再帰
・気分で普通のDPやったらなんかバグったので再帰で書き直した…。
　分かってれば結構やるだけな感じだっただけに、
　そのタイムロスはもったいなかったな。。
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
    ll N, P;
    cin >> N >> P;

    mint a = (mint)P / 100;
    mint b = (mint)1 - a;
    vector<mint> memo(N + 1);
    vector<ll> visited(N + 1);
    auto rec = [&](auto&& f, ll n) -> mint {
        if (n <= 0) {
            return 0;
        }
        if (visited[n]) {
            return memo[n];
        }
        mint res = 0;
        res += (f(f, n - 2) + 1) * a;
        res += (f(f, n - 1) + 1) * b;
        memo[n] = res;
        visited[n] = 1;
        return res;
    };
    mint ans = rec(rec, N);
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
