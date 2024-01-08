/*
・きっちり自力AC。
・操作回数が足りる限り、少ない方を増やして合わせる貪欲。
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
    ll N, K;
    cin >> N >> K;
    string S;
    cin >> S;

    auto C = Counter(S);
    ll ans = 0;
    rep(c1, 'a', 'z' + 1) {
        char c2 = toupper(c1);
        ll need = abs(C[c1] - C[c2]) / 2;
        ll use = min(K, need);
        if (use) {
            if (C[c1] > C[c2]) {
                C[c1] -= use;
                C[c2] += use;
            } else {
                C[c1] += use;
                C[c2] -= use;
            }
            K -= use;
        }
        ans += min(C[c1], C[c2]);
    }
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
