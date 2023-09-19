/*
・きっちり自力AC！
・クエリ先読み座圧、BITにぶたん
・BITにぶたんでシミュった。けど今見たらこれはPQでやる方が自然だったかね。
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

    BIT<ll> bit(N);
    rep(i, N) {
        bit.add(i, 1);
    }

    Compress<ll> cp;
    vector<array<ll, 3>> qs;
    rep(i, M) {
        ll t, w, s;
        cin >> t >> w >> s;
        cp.add(t);
        cp.add(t + s);
        qs.pb({t, w, s});
    }
    cp.build();
    ll L = cp.size();

    vector<ll> ans(N);
    vvl adj(L);
    ll cur = 0;
    rep(i, M) {
        auto [t, w, s] = qs[i];
        ll cpt = cp[t];
        while (cur <= cpt) {
            for (auto k : adj[cur]) {
                bit.add(k, 1);
            }
            cur++;
        }
        ll j = bit.bisearch_fore(0, N - 1, 1);
        if (j != -1) {
            ans[j] += w;
            bit.add(j, -1);
            adj[cp[t + s]].eb(j);
        }
    }
    print(ans, '\n');
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
