/*
・グリッド、行交換
・今どこなのかをpos配列に持たせておく。
　今回は行だけだけど、確か列もやっても独立で大丈夫なはず。
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
    ll N;
    cin >> N;
    auto grid = listnd(N, N, 0);
    rep(i, N) {
        cin >> grid[i];
    }

    vector<ll> pos(N);
    iota(ALL(pos), 0);
    ll Q;
    cin >> Q;
    rep(_, Q) {
        ll op, a, b;
        cin >> op >> a >> b;
        a--, b--;
        if (op == 1) {
            swap(pos[a], pos[b]);
        } else {
            print(grid[pos[a]][b]);
        }
    }
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
