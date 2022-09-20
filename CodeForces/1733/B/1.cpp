/*
・自力AC！
・0は必ず必要、でも両方0はダメ、0,1の場合は例外的に処理。
　といった小さい数の場合分けを済ませると、後は2番目から勝たせるとして展開は一本道。
　ぴったり終わる人数(Nがmod yで1)の場合だけOKとする。
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
    ll N, x, y;
    cin >> N >> x >> y;
    if (x > y) swap(x, y);

    if (x != 0 or (x == 0 and y == 0)) {
        print(-1);
        return;
    } elif (y == 1) {
        vector<ll> ans(N-1);
        iota(ALL(ans), 2);
        print(ans);
        return;
    }

    if (N%y == 1) {
        ll cur = 2;
        vector<ll> ans;
        while (cur <= N) {
            rep(_, y) {
                ans.eb(cur);
            }
            cur += y;
        }
        print(ans);
    } else {
        print(-1);
    }
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
