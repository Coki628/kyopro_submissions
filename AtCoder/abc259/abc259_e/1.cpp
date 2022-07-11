/*
・きっちり自力AC！
・D詰まったのでこっち先に通した。
　素因数毎に、全体として何個持ってるやつが何か所あるか持っておいて、
　A[i]が1つでも他よりも多いような素因数を持ってたら、
　そいつは固有の値を出すとして答えを増やす、みたいにやった。
・被ってるやつも、他の固有の値とは別の値(1つも取り除かない時の値)を出すので、
　その分1個だけは別途足す必要がある。
　まあコーナーだけど、サンプルでも分かるから落ち着いて対処。
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
    vvpll A;
    map<ll, vector<ll>> adj;
    rep(i, N) {
        ll m;
        cin >> m;
        vector<pll> cur;
        rep(j, m) {
            ll p, c;
            cin >> p >> c;
            cur.eb(p, c);
            adj[p].eb(c);
        }
        A.eb(cur);
    }

    for (auto& [k, li] : adj) {
        sort(ALL(li));
    }
    ll ans = 0;
    bool has_dup = false;
    rep(i, N) {
        bool dup = true;
        rep(j, A[i].size()) {
            auto [p, c] = A[i][j];
            ll cnt = adj[p].size() - bisect_left(adj[p], c);
            if (cnt <= 1) {
                dup = false;
                break;
            }
        }
        if (dup) has_dup = true;
        if (not dup) ans++;
    }
    ans += has_dup;
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
