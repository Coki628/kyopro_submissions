/*
・きっちり自力AC！
・最大値の最小化、操作の構築、逆操作で貪欲
・ぱっと聞くとにぶたんしたくなる問題の見た目なんだけど、しない。
　逆操作でシミュすると、あるモンスターを倒すために入手するべきポーションの最適が分かる。
　(早めに手に入れて得はないので、全部一番直前のものを入手するとする。)
　後はこれに従って前から実際に操作すればOK。
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
    vector<pll> qs;
    rep(i, N) {
        ll t, x;
        cin >> t >> x;
        x--;
        qs.eb(t, x);
    }

    vector<ll> mon(N), use(N);
    rep(i, N - 1, -1, -1) {
        auto [t, x] = qs[i];
        if (t == 1) {
            if (mon[x] > 0) {
                mon[x]--;
                use[i] = true;
            }
        } else {
            mon[x]++;
        }
    }
    if (max(mon) > 0) {
        print(-1);
        return;
    }
    ll cnt = 0, mx = 0;
    vector<ll> ans;
    rep(i, N) {
        auto [t, x] = qs[i];
        if (t == 1) {
            if (use[i]) {
                cnt++;
                chmax(mx, cnt);
                ans.eb(1);
            } else {
                ans.eb(0);
            }
        } else {
            cnt--;
        }
    }
    print(mx);
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
