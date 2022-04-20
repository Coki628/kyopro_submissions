/*
・きっちり自力AC！
・2乗の制約に注目。0位置を決めて全探索できる。
　左右に伸ばすのは線形かけれるので、愚直っぽいシミュでOK。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

    ll ans = INF;
    rep(x, N) {
        vector<ll> B(N);
        ll sm = 0;
        rep(i, x+1, N) {
            ll need = B[i-1] + 1;
            ll cnt = ceil(need, A[i]);
            B[i] = A[i] * cnt;
            sm += cnt;
        }
        rep(i, x-1, -1, -1) {
            ll need = B[i+1] + 1;
            ll cnt = ceil(need, A[i]);
            B[i] = A[i] * cnt;
            sm += cnt;
        }
        chmin(ans, sm);
    }
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
