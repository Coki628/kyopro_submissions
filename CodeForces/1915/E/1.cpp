/*
・きっちり自力AC！
・連続部分列、区間和、偶奇、zero sum ranges系
・偶数位置と奇数位置で等しくするのを目指すので、
　片側を負に向ければ区間和0を目指す形にできて都合がいい。
　区間和0を目指すのであれば、累積和で左端=右端があればいいので、
　累積和で同じ値が出現したかチェックすればよくなる。
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
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    rep(i, 0, N, 2) {
        A[i] = -A[i];
    }
    vector<ll> acc(N + 1);
    rep(i, N) {
        acc[i + 1] = acc[i] + A[i];
    }
    set<ll> se(ALL(acc));
    YESNO(se.size() <= N);
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
