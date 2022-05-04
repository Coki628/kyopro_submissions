/*
・きっちり自力AC！
・状況を整理すると、隣接2項だけは交換可能みたいになるので、
　その条件で大小関係直して、ソート済になってるかチェック、でOK。
　ただしNが奇数だと末尾ではなく先頭だけが操作不可みたいになるので、
　後ろから見るようにやった。
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
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    rep(i, N-2, -1, -2) {
        if (A[i] > A[i+1]) {
            swap(A[i], A[i+1]);
        }
    }
    if (A == sorted(A)) {
        YES();
    } else {
        NO();
    }
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
