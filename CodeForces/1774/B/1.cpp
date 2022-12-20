/*
・自力ならず。こういう割り算考察頑張るのはほんと苦手…。
・コーナーケース
・K個以上間隔空けるに当たって、最大値がボトルネックになる。なので基本方針としては、
　最大値を軸にして他の要素を隙間に詰めて問題なく置けるか、になる。
　そもそも本番中はこの時点で-1ついてなかったりでWAだったんだけど、
　それを直してもプレテス通ってハックされるみたいなこのコードになる。
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
    ll N, M, K;
    cin >> N >> M >> K;
    vector<ll> A(M);
    cin >> A;

    if (K > M) {
        NO();
        return;
    }
    if (K == 1) {
        YES();
        return;
    }
    ll mx = max(A);
    ll rest = sum(A) - mx;
    if (rest >= (mx - 1) * (K - 1)) {
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
