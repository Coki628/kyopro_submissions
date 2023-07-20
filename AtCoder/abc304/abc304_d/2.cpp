/*
・mapで集計の方針を検討してみた。
　最小値でイチゴ0個の区画があるかのチェックは要るものの、
　こっちが思いつくなら平面走査っぽくするより全然楽だと思った。
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
    ll W, H;
    cin >> W >> H;
    ll N;
    cin >> N;
    vector<pll> P;
    rep(i, N) {
        ll p, q;
        cin >> p >> q;
        P.eb(p, q);
    }
    ll M1, M2;
    cin >> M1;
    vector<ll> A(M1);
    cin >> A;
    cin >> M2;
    vector<ll> B(M2);
    cin >> B;

    A.insert(A.begin(), 0);
    B.insert(B.begin(), 0);
    M1++, M2++;
    map<pll, ll> C;
    for (auto [p, q] : P) {
        ll i = bisect_left(A, p) - 1;
        ll j = bisect_left(B, q) - 1;
        C[{i, j}]++;
    }
    ll mn = INF, mx = -INF;
    for (auto [k, v] : C) {
        chmin(mn, v);
        chmax(mx, v);
    }
    if (C.size() < M1 * M2) {
        mn = 0;
    }
    print(mkp(mn, mx));
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
