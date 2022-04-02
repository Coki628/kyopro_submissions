/*
・きっちり自力AC！
・包除原理、ビット全探索
・どの行を使うかは全集合持てる。
　これでその集合全部で使える文字で作れるものを重複として包除。
　立ってるビットの本数の偶奇で足し引きする。
・本番中にまともに包除の問題通せたの初めてな気がする。それは嬉しい。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

void solve() {
    ll N, L;
    cin >> N >> L;
    vector<string> S(N);
    rep(i, N) cin >> S[i];

    mint ans = 0;
    rep(bit, 1, 1LL<<N) {
        vector<ll> C(26);
        rep(i, N) {
            if (bit>>i & 1) {
                rep(j, S[i].size()) {
                    C[S[i][j]-'a']++;
                }
            }
        }
        ll cnt = 0;
        rep(c, 26) {
            if (C[c] == popcount(bit)) {
                cnt++;
            }
        }
        if (popcount(bit)%2 == 0) {
            ans -= pow(cnt, L, MOD);
        } else {
            ans += pow(cnt, L, MOD);
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
