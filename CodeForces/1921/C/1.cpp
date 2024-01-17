/*
・きっちり自力AC！
・貪欲にやる。
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
    ll N, f, a, b;
    cin >> N >> f >> a >> b;
    vector<ll> A(N);
    cin >> A;

    A.insert(A.begin(), 0);
    ll res = 0;
    rep(i, N) {
        ll costa = (A[i + 1] - A[i]) * a;
        ll costb = b;
        res += min(costa, costb);
    }
    YESNO(res < f);
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
