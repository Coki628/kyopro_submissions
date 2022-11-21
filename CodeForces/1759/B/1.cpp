/*
・きっちり自力AC！
・総和がa*(a+1)/2になるまで進む。ぴったりにならなかったり、max(A)がこのaより大きかったらNO。
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
    ll M, S;
    cin >> M >> S;
    vector<ll> A(M);
    cin >> A;

    ll total = sum(A) + S;
    ll a = 1;
    while (1) {
        ll b = a * (a+1) / 2;
        if (b > total) break;
        if (b == total) {
            if (max(A) > a) {
                NO();
            } else {
                YES();
            }
            return;
        }
        a++;
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
