/*
・きっちり自力AC！
・?にする場所をビット全探索。
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
    vector<string> S(N);
    cin >> S;

    ll ans = 0;
    rep(bit, 1LL << L) {
        if (popcount(bit) != K) continue;
        HashMap<string, ll> C;
        rep(i, N) {
            string s;
            rep(j, L) {
                if (bit >> j & 1) {
                    s += '?';
                } else {
                    s += S[i][j];
                }
            }
            C[s]++;
        }
        ll mx = 0;
        for (auto [k, v] : C) {
            chmax(mx, v);
        }
        chmax(ans, mx);
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
