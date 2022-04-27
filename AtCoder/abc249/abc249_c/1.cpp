/*
・きっちり自力AC！
・ビット全探索
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
    ll N, K;
    cin >> N >> K;
    vector<string> S(N);
    rep(i, N) {
        cin >> S[i];
        UNIQUE(S[i]);
    }

    ll ans = 0;
    rep(bit, 1LL<<N) {
        vector<ll> C(26);
        rep(i, N) {
            if (bit>>i & 1) {
                for(auto c : S[i]) {
                    C[c-'a']++;
                }
            }
        }
        ll cnt = 0;
        rep(c, 26) {
            if (C[c] == K) {
                cnt++;
            }
        }
        chmax(ans, cnt);
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
