/*
・ダブリング
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

#include "numbers/digit_sum.hpp"
#include "datastructure/Doubling.hpp"

auto f = [](int prev, int power) {
    return power;
};

void solve() {
    ll N, K;
    cin >> N >> K;

    vector<ll> nxt(N + 1);
    rep(i, N + 1) {
        nxt[i] = i - digit_sum(i);
    }
    auto db = get_doubling(30, nxt, -1LL, f);
    rep(i, 1, N + 1) {
        ll res = db.get(i, K);
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
