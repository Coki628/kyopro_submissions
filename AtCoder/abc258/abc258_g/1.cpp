/*
・なんとか自力AC！
・2点決めると、bitsetのandで該当する3つ目の頂点数が分かる。3000ビットでも軽いと信じて進む。
　分かればすぐだけど、結構気付くのに時間かかった…。
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
    ll N;
    cin >> N;
    auto G = list2d(N, N, 0);
    vector<bitset<3000>> B(N);
    rep(i, N) {
        rep(j, N) {
            char c;
            cin >> c;
            G[i][j] = toint(c);
            if (G[i][j] and i < j) {
                B[i].set(j);
            }
        }
    }

    ll ans = 0;
    rep(i, N) {
        rep(j, i+1, N) {
            if (G[i][j]) {
                auto res = B[i] & B[j];
                ans += res.count();
            }
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
