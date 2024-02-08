/*
・きっちり自力AC！
・AだけBだけ両方の3つを数える。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    ll N, M, K;
    cin >> N >> M >> K;
    auto A = LIST(N);
    auto B = LIST(M);

    auto C1 = Counter(A);
    auto C2 = Counter(B);
    ll acnt = 0, bcnt = 0, bothcnt = 0;
    rep(i, 1, K + 1) {
        if (C1.count(i) and C2.count(i)) {
            bothcnt++;
        } else if (C1.count(i)) {
            acnt++;
        } else if (C2.count(i)) {
            bcnt++;
        }
    }
    chmin(acnt, K / 2);
    chmin(bcnt, K / 2);
    YESNO(acnt + bcnt + bothcnt >= K);
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
