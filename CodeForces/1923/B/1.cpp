/*
・きっちり自力AC！
・まず、負方向も正方向ど同一視していい。
　で、操作はBITにぶたんでシミュしたけど、
　B問題だしなんかもっと楽な方針があるんだとは思う。
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

void solve(int testcase) {
    ll N, K;
    cin >> N >> K;
    auto A = LIST(N);
    auto X = LIST(N);

    rep(i, N) {
        if (X[i] < 0) {
            X[i] = -X[i];
        }
    }
    BIT<ll> bit(N + 1);
    rep(i, N) {
        bit.add(X[i], A[i]);
    }
    rep(i, N + 1) {
        if (bit[i] > 0) {
            NO();
            return;
        }
        ll l = bit.bisearch_fore(0, N, 1);
        if (l == -1) break;
        ll r = bit.bisearch_fore(0, N, K);
        if (r == -1) r = N + 1;
        ll cur = K;
        rep(j, l, r) {
            cur -= bit[j];
            bit.update(j, 0);
        }
        if (r <= N) {
            bit.add(r, -cur);
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
    rep(t, T) solve(t);

    return 0;
}
