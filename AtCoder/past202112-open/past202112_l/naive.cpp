/*
・ランダムテスト用愚直解。
　でもこれ投げると何かWAになるんだよね。。ｗ
　よくこれ使ってダメなケース見つけられたなって思う。
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
    ll N, P;
    cin >> N >> P;
    auto A = LIST(N);

    vector<bool> ng(N);
    rep(i, N) {
        if (A[i]+i > P or A[i]+i < N-1) {
            ng[i] = true;
        }
    }
    ll ans = N;
    rep(bit, 1LL<<N) {
        auto cur = A;
        bool ok = true;
        rep(i, N) {
            if (bit>>i & 1) {
                if (i == 0) {
                    cur[i] = P;
                } else {
                    cur[i] = cur[i-1]-1;
                }
            } else {
                if (ng[i]) {
                    ok = false;
                    break;
                }
                if (i and cur[i] >= cur[i-1]) {
                    ok = false;
                    break;
                }
            }
        }
        if (min(cur) >= 0 and ok) {
            chmin(ans, (ll)popcount(bit));
        }
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
