/*
・確率DPで自己ループがある遷移について、
　期待値DPでまとめた方針が適用できるのか確認。
　最初は合わなくて困ったけど、コストを0とみなすと合った。
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
    ll N;
    cin >> N;

    ll cnt2 = 0, cnt3 = 0, cnt5 = 0;
    ll cur = N;
    while (cur % 2 == 0) {
        cnt2++;
        cur /= 2;
    }
    while (cur % 3 == 0) {
        cnt3++;
        cur /= 3;
    }
    while (cur % 5 == 0) {
        cnt5++;
        cur /= 5;
    }
    if (cur > 1) {
        print(0);
        return;
    }

    auto memo = listnd(cnt2 + 1, cnt3 + 1, cnt5 + 1, (mint)0);
    auto visited = listnd(cnt2 + 1, cnt3 + 1, cnt5 + 1, 0);
    auto rec = [&](auto &&f, ll i, ll j, ll k) -> mint {
        if (i == cnt2 and j == cnt3 and k == cnt5) {
            return 1;
        }
        if (visited[i][j][k]) {
            return memo[i][j][k];
        }
        visited[i][j][k] = true;
        mint prob = 0, cost = 0;
        // 2
        if (i + 1 <= cnt2) {
            // (この先でかかる分+今回かかる分) * そうなる確率(1/6)
            prob += (f(f, i + 1, j, k) + cost) / 6;
        }
        // 3
        if (j + 1 <= cnt3) {
            prob += (f(f, i, j + 1, k) + cost) / 6;
        }
        // 4
        if (i + 2 <= cnt2) {
            prob += (f(f, i + 2, j, k) + cost) / 6;
        }
        // 5
        if (k <= cnt5) {
            prob += (f(f, i, j, k + 1) + cost) / 6;
        }
        // 6
        if (i + 1 <= cnt2 and j + 1 <= cnt3) {
            prob += (f(f, i + 1, j + 1, k) + cost) / 6;
        }
        // 自己ループ分のコスト * そうなる確率
        prob += cost * 1 / 6;
        // 自己ループ補正「1回の遷移の総数/自己ループにならずに遷移する数」を掛ける
        prob *= (mint)6 / 5;
        return memo[i][j][k] = prob;
    };
    auto ans = rec(rec, 0, 0, 0);
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
