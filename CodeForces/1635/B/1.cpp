/*
・自力AC
・でっぱりが来たらその次のやつを貪欲に修正、でOK。
　N == 2 があるのでそれは場合分け。
　なんだけどその例外処理でreturn書き忘れたせいで時間が無限に溶けた。。
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
    ll N;
    cin >> N;
    auto A = LIST(N);

    if (N < 3) {
        print(0);
        print(A);
        return;
    }
    A.eb(-INF);

    ll ans = 0;
    rep(i, 1, N-1) {
        if (A[i-1] < A[i] and A[i] > A[i+1]) {
            A[i+1] = max(A[i], A[i+2]);
            ans++;
        }
    }
    A.pop_back();
    print(ans);
    print(A);
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
