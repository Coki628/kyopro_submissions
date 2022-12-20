/*
・自力AC！
・差分に注目すると、両者の半分くらいの所で大小が切り替わるのが分かる。
　ここからそれぞれの位置で以上以下の条件が作れるので、
　全部集めてきてソートして、一番厳しい所同士で比較すればいい。
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
    vector<ll> A(N);
    cin >> A;

    vector<ll> B1 = {1000000000}, B2 = {0};
    rep(i, N - 1) {
        if (A[i] < A[i + 1]) {
            B1.eb((A[i] + A[i + 1]) / 2);
        } else if (A[i] > A[i + 1]) {
            B2.eb(ceil(A[i] + A[i + 1], 2LL));
        }
    }
    sort(ALL(B1));
    sort(ALL(B2));
    if (B1[0] < B2.back()) {
        print(-1);
    } else {
        print(B2.back());
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
