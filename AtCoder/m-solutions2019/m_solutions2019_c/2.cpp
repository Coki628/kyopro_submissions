/*
・dojo set_e_4_4
・これは自力TLE。
・期待値DP
・空振り遷移のある期待値DP。これがちゃんと書けるようになってるのはいいんだけど、
　今回は2乗無理なのでこれだと通用しない。
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

void solve() {
    ll N, a, b, c;
    cin >> N >> a >> b >> c;

    auto memo = list2d<mint>(N+1, N+1, 0);
    auto visited = list2d(N+1, N+1, false);
    auto rec = [&](auto&& f, ll i, ll j) -> mint {
        if (visited[i][j]) {
            return memo[i][j];
        }
        if (i == N) {
            return 0;
        }
        if (j == N) {
            return 0;
        }
        mint exp = 1, total = 100;
        exp += f(f, i+1, j)*a/total;
        exp += f(f, i, j+1)*b/total;
        // 全体に「1回の遷移の総数/自己ループにならずに遷移する数」を掛ける
        exp *= total/(a+b);
        memo[i][j] = exp;
        visited[i][j] = true;
        return exp;
    };
    auto res = rec(rec, 0, 0);
    print(res);
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
