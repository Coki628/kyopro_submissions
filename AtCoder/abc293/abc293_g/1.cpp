/*
・きっちり自力AC！
・Mo's algorithm
・Gの通され方を見て様子見に来て正解だった。
　ぱっと考えてすぐMoっぽいと思えたからかなりすんなり通せた。
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

#include "datastructure/Mo.hpp"

ll nC3(ll n) {
    return (n * (n - 1) * (n - 2)) / 6;
}

void solve() {
    ll N, Q;
    cin >> N >> Q;
    vector<ll> A(N);
    cin >> A;
    Mo mo(N);
    rep(i, Q) {
        ll l, r;
        cin >> l >> r;
        l--;
        mo.add(l, r);
    }

    vector<ll> ans(Q), C(200007);
    ll cur = 0;
    auto add = [&](int i) -> void {
        cur -= nC3(C[A[i]]);
        C[A[i]]++;
        cur += nC3(C[A[i]]);
    };
    auto erase = [&](int i) -> void {
        cur -= nC3(C[A[i]]);
        C[A[i]]--;
        cur += nC3(C[A[i]]);
    };
    auto out = [&](int i) -> void {
        ans[i] = cur;
    };
    mo.build(add, erase, out);
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
