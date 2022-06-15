/*
・きっちり自力AC！
・値はmod 10しておく。
　で、j固定で今見ている位置より手前と後ろの個数が分かるように集計しておけば、
　i,kとして妥当な物があるかどうかは10*10見ればいい。
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
    auto A = LIST(N);

    rep(i, N) {
        A[i] %= 10;
    }
    vector<ll> C1(10), C2(10);
    rep(i, N) {
        C2[A[i]]++;
    }
    rep(i, N) {
        C2[A[i]]--;
        rep(a, 10) {
            rep(b, 10) {
                if (C1[a] > 0 and C2[b] > 0) {
                    if ((A[i]+a+b)%10 == 3) {
                        YES();
                        return;
                    }
                }
            }
        }
        C1[A[i]]++;
    }
    NO();
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
