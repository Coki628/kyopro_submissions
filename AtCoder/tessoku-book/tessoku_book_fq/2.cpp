/*
・部分点解法
・DPする。ガソリン残量の状態を持って、
　各位置でどのくらい給油するかの遷移を全部やる。無事部分点獲得。
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
    ll N, L, K;
    cin >> N >> L >> K;
    // 部分点解法
    assert(N <= 100 and L <= 100);
    vector<ll> A(N), C(N);
    rep(i, N) {
        cin >> A[i] >> C[i];
    }
    A.insert(A.begin(), 0);
    C.insert(C.begin(), 0);
    A.eb(L);
    C.eb(0);
    N++;

    auto dp = listnd(N + 1, K + 1, INF);
    dp[0][K] = 0;
    rep(i, N) {
        rep(j, K + 1) {
            rep(k, K + 1) {
                if (j + k > K) break;
                ll nxj = j + k - abs(A[i] - A[i + 1]);
                if (nxj < 0) continue;
                chmin(dp[i + 1][nxj], dp[i][j] + k * C[i]);
            }
        }
    }
    ll ans = min(dp[N]);
    if (ans >= INF) ans = -1;
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
