/*
・N*N配列に会ったことがあるか持たせて、
　最後に全ペアチェックで1つでも会ってないやつがあればNo、とした。
　Bにしてはややこしめ？(なんかCと逆転してたとか何とか)
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
    ll N, M;
    cin >> N >> M;
    auto G = listnd(N, N, 0);
    rep(i, M) {
        ll K;
        cin >> K;
        auto X = LIST(K);
        rep(i, K) X[i]--;
        rep(i, K) {
            rep(j, K) {
                G[X[i]][X[j]] = 1;
            }
        }
    }
    rep(i, N) {
        rep(j, N) {
            if (not G[i][j]) {
                No();
                return;
            }
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
