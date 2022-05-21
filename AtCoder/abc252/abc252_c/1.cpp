/*
・きっちり自力AC！
・0～9は全探索として、目当ての数字が出たindexを集めておいて、愚直シミュ。N小さいから大丈夫。
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
    vector<string> S(N);
    rep(i, N) cin >> S[i];

    ll ans = INF;
    for (auto c : digits) {
        vector<ll> C(10);
        rep(i, N) {
            rep(j, 10) {
                if (S[i][j] == c) {
                    C[j]++;
                }
            }
        }

        ll cnt = 0, t = 0;
        while (cnt < N) {
            if (C[t%10]) {
                C[t%10]--;
                cnt++;
            }
            t++;
        }
        t--;
        chmin(ans, t);
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
