/*
・きっちり自力AC。
・差分が1ずつ大きくなるように配置していく。最大値Nで上を抑えながら。
　でもこれだけだと後半が平らになるので、後ろから順に平らになった所は1ずつずらしていく。
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
    ll K, N;
    cin >> K >> N;

    ll diff = 2;
    vector<ll> ans = {1, 2};
    rep(_, K - 2) {
        ans.eb(min(ans.back() + diff, N));
        diff++;
    }
    rep(i, K - 2, -1, -1) {
        if (ans[i] >= ans[i + 1]) {
            ans[i] = ans[i + 1] - 1;
        }
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
