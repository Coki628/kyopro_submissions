/*
・きっちり自力AC！
・mapに詰めてvalue(-Tとi)でソート。
　条件を{降順, 昇順}にしたい時は、符号をひっくり返すと普通にできて楽。
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
    ll N;
    cin >> N;
    map<string, pll> mp;
    rep(i, N) {
        string S;
        cin >> S;
        ll T;
        cin >> T;
        if (not mp.count(S)) {
            mp[S] = {-T, i};
        }
    }

    vector<pll> V;
    for (auto [k, v] : mp) {
        V.eb(v);
    }
    sort(ALL(V));
    ll ans = V[0].second + 1;
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
