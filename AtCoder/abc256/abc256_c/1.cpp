/*
・きっちり自力AC！とはいえちょっと悩んでもたついたのは良くない…。
・工夫して全列挙
・9マス全部30^9は無理だけど4マス決めれば残りが一意なので30^4する。
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
    ll H = 3, W = 3;
    auto A = LIST(H);
    auto B = LIST(W);

    vvl V;
    vector<ll> cur;
    auto rec = [&](auto&& f) {
        if (cur.size() == 4) {
            V.eb(cur);
            return;
        }
        rep(j, 1, max(max(A), max(B))+1) {
            cur.eb(j);
            f(f);
            cur.pop_back();
        }
    };
    rec(rec);

    ll ans = 0;
    for (auto& cur : V) {
        bool ok = true;
        auto grid = list2d(3, 3, 0);
        grid[0][0] = cur[0];
        grid[0][1] = cur[1];
        grid[1][0] = cur[2];
        grid[1][1] = cur[3];
        rep(i, 2) {
            grid[i][2] = A[i] - (grid[i][0]+grid[i][1]);
            grid[2][i] = B[i] - (grid[0][i]+grid[1][i]);
            if (grid[i][2] <= 0 or grid[2][i] <= 0) {
                ok = false;
                break;
            }
        }
        if (not ok) continue;
        grid[2][2] = A[2] - (grid[2][0]+grid[2][1]);
        if (grid[2][2] <= 0) {
            ok = false;
        }
        if (not ok) continue;
        if (grid[0][2]+grid[1][2]+grid[2][2] != B[2]) {
            ok = false;
        }
        if (not ok) continue;
        ans++;
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
