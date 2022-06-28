/*
・古のARC埋め
・これはTLEだしMLE。。
・順列3000万通りくらいmapに詰めてるのでそれはそう…。
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
    ll N, M, K;
    cin >> N >> M >> K;
    auto mat = list2d(N, N, false);
    rep(i, M) {
        ll a, b;
        cin >> a >> b;
        mat[a][b] = true;
        mat[b][a] = true;
    }

    vector<map<vector<ll>, ld>> dp(2);
    vector<ll> tmp(N);
    iota(ALL(tmp), 0);
    dp[0][tmp] = 1;
    rep(i, K) {
        for (auto& [P, val] : dp[i%2]) {
            auto cur = P;
            rep(j, N) {
                rep(k, j+1, N) {
                    swap(cur[j], cur[k]);
                    dp[(i+1)%2][cur] += val / (N*(N-1)/2);
                    swap(cur[j], cur[k]);
                }
            }
        }
        dp[i%2].clear();
    }

    ld ans = 0;
    for (auto& [P, val] : dp[K%2]) {
        bool ok = true;
        rep(i, N) {
            if (mat[P[i]][P[(i+1)%N]]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            ans += val;
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
