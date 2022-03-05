/*
・きっちり自力AC！
・Mo's algorithm
・一見してMoで解けそう、って思えたのは良かった。
　クエリ100万なのは気になったけど、TL5秒だし行けると踏んだ。
　少し前にもABC-GでMoを書いてたのが良かったかも。(abc238_g)
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

#include "segment/Mo.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    ll Q;
    cin >> Q;
    Mo mo(N);
    rep(i, Q) {
        ll l, r;
        cin >> l >> r;
        l--;
        mo.add(l, r);
    }

    vector<ll> C(N+1), ans(Q);
    ll cnt = 0;
    auto add = [&](ll i) -> void {
        C[A[i]]++;
        if (C[A[i]]%2 == 0) {
            cnt++;
        }
    };
    auto erase = [&](ll i) -> void {
        C[A[i]]--;
        if (C[A[i]]%2 == 1) {
            cnt--;
        }
    };
    auto out = [&](ll i) -> void {
        ans[i] = cnt;
    };
    mo.build(add, erase, out);
    rep(i, Q) print(ans[i]);
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
