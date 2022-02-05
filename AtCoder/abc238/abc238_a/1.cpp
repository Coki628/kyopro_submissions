/*
・また多倍長の出番か？って思った後、でもさすがにN乗でかすぎたら多倍長でもTLEだろ、
　と思い少し焦る。もう少し考えると、どうせN乗のがNの2乗より
　すぐでかくなるのは明らかなので、適当にでかいのはYesにすればいい。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

    if (N >= 5) {
        Yes();
        return;
    }
    if (pow(2, N) > pow(N, 2)) Yes();
    else No();
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
