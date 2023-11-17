/*
・きっちり自力AC！
・偶数に揃えるか奇数に揃えるか両方試す。
　奇数が1つでもあると偶数に揃えるのは無理で(最小の奇数で詰む)、
　奇数に揃える時は、最小の奇数が操作したい偶数より小さければ可なので、
　最小の奇数が分かる状態にしておいてチェックする。
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

    vector<ll> A2[2];
    rep(i, N) {
        A2[A[i] % 2].eb(A[i]);
    }
    rep(i, 2) sort(ALL(A2[i]));

    bool ok = true;
    rep(i, N) {
        if (A[i] % 2 == 1) {
            ok = false;
            break;
        }
    }
    if (ok) {
        YES();
        return;
    }
    ok = true;
    rep(i, N) {
        if (A[i] % 2 == 0) {
            if (A2[1].empty() or A2[1][0] > A[i]) {
                ok = false;
                break;
            }
        }
    }
    if (ok) {
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
