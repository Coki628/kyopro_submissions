/*
・自力AC！
・logで乗算を加算にするテク、誤差対策、にぶたん
・広義単調増加になるように値を大きくするんだけど、
　普通にやると値が大きくなり過ぎるので、工夫する。
　logの世界で計算すれば乗算は加算にできる。
　実数になってしまうので、誤差対策にEPSをつける。
　1回ずつ足さないでにぶたんで一気に足す。これで無事AC。
・公式解は2冪部分とそうでない部分を分けて考えるみたいなやつだった。
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
    vector<ll> A(N);
    cin >> A;

    vector<ld> B(N);
    rep(i, N) {
        B[i] = log10(A[i]);
    }
    ld add = log10(2);
    ll ans = 0;
    rep(i, 1, N) {
        ll cnt = bisearch_min(-1, INF, [&](ll x) {
            return B[i - 1] <= B[i] + add * x + EPS;
        });
        B[i] += add * cnt;
        ans += cnt;
        // while (B[i - 1] - EPS > B[i]) {
        //     B[i] += add;
        //     ans++;
        // }
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
