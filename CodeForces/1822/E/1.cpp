/*
・自力ならず。
・考えた通りに書いたら、テストケース2でWAになって手掛かりなし…。
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
    string S;
    cin >> S;

    if (N % 2 == 1) {
        print(-1);
        return;
    }
    auto C = Counter(S);
    for (auto [k, v] : C) {
        if (v > N / 2) {
            print(-1);
            return;
        }
    }

    ll cnt = 0;
    rep(i, N / 2) {
        ll j = N - i - 1;
        if (S[i] == S[j]) cnt++;
    }
    ll ans = ceil(cnt, 2LL);
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
