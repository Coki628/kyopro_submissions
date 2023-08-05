/*
・きっちり自力AC。
・どの位置に寄せるかで三分探索。まあ貪欲できたらしいけど。
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

#include "common/trisearch.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    ll mn = min(A);
    ll mx = max(A);
    auto [i, val] =  trisearch_min(mn, mx + 1, [&](ll x) {
        ll a = 0, b = 0;
        rep(i, N) {
            if (A[i] < x) {
                a += x - A[i];
            } else if (A[i] > x + 1) {
                b += A[i] - (x + 1);
            }
        }
        return max(a, b);
    }, 10);
    print(val);
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
