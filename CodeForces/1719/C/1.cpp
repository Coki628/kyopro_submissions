/*
・きっちり自力AC！やっぱBみたいのよりこういう方がやりやすい。
・クエリ先読み
・クエリ先読みしてNまでシミュ。残りは一番強いやつが総取り。
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
    ll N, Q;
    cin >> N >> Q;
    auto A = LIST(N);

    vvpll qs(N);
    vector<array<ll, 3>> others;
    rep(q, Q) {
        ll i, k;
        cin >> i >> k;
        i--;
        if (k < N) {
            qs[k].eb(q, i);
        } else {
            others.pb({q, i, k});
        }
    }

    vector<ll> ans(Q), C(N);
    ll winner = 0;
    rep(i, 1, N) {
        if (A[winner] < A[i]) {
            winner = i;
        }
        C[winner]++;
        for (auto [q, j] : qs[i]) {
            ans[q] = C[j];
        }
    }
    for (auto [q, i, k] : others) {
        ll rest = k - (N-1);
        if (i == winner) {
            ans[q] = C[i] + rest;
        } else {
            ans[q] = C[i];
        }
    }
    print(ans, '\n');
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
