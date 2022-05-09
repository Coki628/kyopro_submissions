/*
・グリッド、構築
・地味にめんどくないかね、まあBで実装寄りだとこんなもんか…。
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
    ll N, H, W;
    cin >> N >> H >> W;

    vector<string> ans(H*N, string(W*N, '.'));
    ll i = 0;
    rep(h, H*N) {
        ll j = 0;
        rep(w, W*N) {
            if ((i%2) ^ (j%2)) {
                ans[h][w] = '#';
            }
            if (w%W == W-1) j++;
        }
        if (h%H == H-1) i++;
    }
    print(ans, '\n');
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
