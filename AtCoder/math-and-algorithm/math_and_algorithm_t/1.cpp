/*
・再帰全探索
・5重ループ書くか悩んだけど、練習も兼ねて再帰で。ABC頻出だしな。
・案の定、秒では書けなくて少しもたついた。内側でループ回そうとしたり。。
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
    ll K = 1000;
    ll D = 5;

    ll sm = 0, ans = 0;
    auto rec = [&](auto&& f, ll d, ll i) {
        if (d == D) {
            if (sm == K) ans++;
            return;
        }
        if (i == N) return;
        sm += A[i];
        if (sm <= K) f(f, d+1, i+1);
        sm -= A[i];
        f(f, d, i+1);
    };
    rec(rec, 0, 0);
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
