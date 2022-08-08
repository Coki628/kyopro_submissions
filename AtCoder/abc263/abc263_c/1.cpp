/*
・きっちり自力AC！
・再帰全探索
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

    vvl ans;
    vector<ll> cur;
    auto rec = [&](auto&& f, ll i) {
        if (i == N) {
            ans.eb(cur);
            return;
        }
        rep(j, cur.size() ? cur.back()+1 : 1, M+1) {
            cur.eb(j);
            f(f, i+1);
            cur.pop_back();
        }
    };
    rec(rec, 0);
    for (auto& a : ans) print(a);
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
