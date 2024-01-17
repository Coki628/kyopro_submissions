/*
・自力AC。
・座圧BITに突っ込んだけど、絶対もっと簡潔な方針あるんだろなーって思った。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    Compress<ll> cp;
    cp.add(0);
    cp.add(INF);
    ll l = 0, r = INF;
    vector<ll> vec;
    rep(i, N) {
        ll op, x;
        cin >> op >> x;
        if (op == 1) {
            chmax(l, x);
        } else if (op == 2) {
            chmin(r, x);
        } else {
            vec.eb(x);
        }
        cp.add(x);
    }
    cp.build();
    ll M = cp.size();
    BIT<ll> bit(M);
    for (auto v : vec) {
        if (l <= v and v <= r) {
            bit.add(cp[v], 1);
        }
    }
    ll ans = max(r - l + 1 - bit.query(cp[l], cp[r] + 1), 0LL);
    print(ans);
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
