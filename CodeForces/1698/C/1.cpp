/*
・自力AC！
・こんなんそうそうある訳ない、と信じてCounterしたやつを3重ループでえいえい回してNG判定すると通る。
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

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    auto C = Counter(A);
    for (auto [k1, v1] : C) {
        for (auto [k2, v2] : C) {
            if (k2 == k1 and v2 <= 1) continue;
            for (auto [k3, v3] : C) {
                if ((k3 == k1 or k3 == k2) and v3 <= 1) continue;
                if (k3 == k1 and k3 == k2 and v3 <= 2) continue;
                if (not C.count(k1+k2+k3)) {
                    NO();
                    return;
                }
            }
        }
    }
    YES();
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
