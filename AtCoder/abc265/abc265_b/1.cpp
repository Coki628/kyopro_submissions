/*
・シミュ。ボーナスを所要時間と同じ形の配列に詰めるとやりやすい。
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
    ll N, M, T;
    cin >> N >> M >> T;
    auto A = LIST(N-1);

    vector<ll> B(N);
    rep(i, M) {
        ll x, y;
        cin >> x >> y;
        x--;
        B[x] = y;
    }

    ll cur = T;
    rep(i, N-1) {
        cur += B[i];
        cur -= A[i];
        if (cur <= 0) {
            No();
            return;
        }
    }
    Yes();
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
