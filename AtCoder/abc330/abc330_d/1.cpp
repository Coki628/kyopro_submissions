/*
・自力AC！
・グリッド、数え上げ
・L字っぽく3個取るという話だが、角になる1つを固定すると重複なく数えられる。
　行側と列側から、それぞれ自分以外から1個選ぶように通り数を数える。
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
    vector<string> grid(N);
    cin >> grid;

    vector<ll> rcnt(N), ccnt(N);
    rep(h, N) {
        rep(w, N) {
            if (grid[h][w] == 'o') {
                rcnt[h]++;
                ccnt[w]++;
            }
        }
    }

    ll ans = 0;
    rep(h, N) {
        rep(w, N) {
            if (grid[h][w] == 'o') {
                ans += (rcnt[h] - 1) * (ccnt[w] - 1);
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
