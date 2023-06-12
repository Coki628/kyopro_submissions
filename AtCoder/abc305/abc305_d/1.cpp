/*
・きっちり自力AC！
・クエリ先読みで座圧してBIT。
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
    vector<ll> A(N);
    cin >> A;
    Compress<ll> cp;
    for (auto a : A) {
        cp.add(a);
    }
    ll Q;
    cin >> Q;
    vector<pll> qs;
    rep(i, Q) {
        ll l, r;
        cin >> l >> r;
        qs.eb(l, r);
        cp.add(l);
        cp.add(r);
    }
    cp.build();
    ll M = cp.size();

    BIT<ll> bit(M);
    set<ll> se(ALL(A));
    ll sleep = 1;
    rep(i, M - 1) {
        ll a = cp.unzip(i);
        ll b = cp.unzip(i + 1);
        if (se.count(a)) {
            sleep = 1 - sleep;
        }
        if (sleep) {
            bit.add(i, b - a);
        }
    }

    for (auto [l, r] : qs) {
        ll res = bit.query(cp[l], cp[r]);
        print(res);
    }
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
