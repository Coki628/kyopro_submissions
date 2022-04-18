/*
参考：https://atcoder.jp/contests/abc223/editorial/3584
　　　https://atcoder.jp/contests/abc223/submissions/30147315
・クエリ系、XOR基底
・XOR基底はセグ木に乗るということで乗せてみた。これはTLE…。
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

#include "numbers/XorBasis.hpp"

auto f = [](XorBasis<ll> a, XorBasis<ll> b) {
    for (auto b : b.basis) {
        a.add(b);
    }
    return a;
};
const XorBasis<ll> T;

void solve() {
    ll N, Q;
    cin >> N >> Q;
    auto A = LIST(N);

    auto seg = get_segment_tree(N, f, T);
    rep(i, N) {
        seg.set(i, vector<ll>{A[i]});
    }
    seg.build();

    rep(i, Q) {
        ll l, r, x;
        cin >> l >> r >> x;
        l--;
        auto basis = seg.query(l, r);
        if (basis.exists(x)) {
            Yes();
        } else {
            No();
        }
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
