/*
・きっちり自力AC！
・差分GCD、約数列挙
・基本的にはソートして差分GCDを取ってその約数。ただし間隔が小さすぎると、
　最初の鐘から最後の鐘までの長さをカバーしきれなくなるので、それは別途確認する。
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
    ll N, K;
    cin >> N >> K;
    auto A = LIST(K);

    sort(ALL(A));
    ll g = 0;
    rep(i, K - 1) {
        g = gcd(g, abs(A[i] - A[i + 1]));
    }
    ll len = A.back() - A[0];
    vector<ll> ans;
    for (auto d : divisors(g)) {
        if (d * (N - 1) >= len) {
            ans.eb(d);
        }
    }
    sort(ALL(ans));
    print(ans.size());
    print(ans);
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
