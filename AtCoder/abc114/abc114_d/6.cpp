/*
・dojo set_d_5_1
・自力AC！
・素因数分解、約数の個数
・ちょっと考えたけど、まあちゃんと通せたから良し。
　考察過程は昔Pythonで解いた当時の自分のとだいたい一緒なので省略。
　3種類のやつしかやってなくて、何で足りないんだー？みたいな。(成長してねぇなー。。)
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
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;

    map<ll, ll> fact;
    rep(i, 2, N+1) {
        for (auto [p, c] : factorize(i)) {
            fact[p] += c;
        }
    }
    vector<ll> P;
    for (auto [k, v] : fact) {
        P.eb(k);
    }
    UNIQUE(P);

    ll ans = 0;
    for (auto [k, v] : fact) {
        if (v >= 74) ans++;
    }
    for (auto& comb : combinations(P, 2)) {
        ll x = comb[0], y = comb[1];
        ll xc = fact[x], yc = fact[y];
        if (xc >= 24 and yc >= 2) ans++;
        if (xc >= 2 and yc >= 24) ans++;
        if (xc >= 14 and yc >= 4) ans++;
        if (xc >= 4 and yc >= 14) ans++;
    }
    for (auto& comb : combinations(P, 3)) {
        ll x = comb[0], y = comb[1], z = comb[2];
        ll xc = fact[x], yc = fact[y], zc = fact[z];
        if (xc >= 2 and yc >= 4 and zc >= 4) ans++;
        if (xc >= 4 and yc >= 2 and zc >= 4) ans++;
        if (xc >= 4 and yc >= 4 and zc >= 2) ans++;
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
