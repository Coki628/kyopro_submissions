/*
・きっちり自力AC。
・ちょっとめんどい。尺取りん中でキュー回してシミュるみたいにやった。
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
    auto S = LIST(N);
    auto T = LIST(N);

    vector<ll> ans(N);
    ans[0] = T[0] - S[0];
    ll cur = T[0];
    ll j = 1;
    queue<pll> que;
    rep(i, 1, N) {
        while (j < N and S[j] <= cur) {
            que.push({S[j], T[j]});
            j++;
        }
        if (j < N and que.empty()) {
            que.push({S[j], T[j]});
            cur = S[j];
            j++;
        }
        auto [s, t] = que.front(); que.pop();
        ans[i] = t - cur;
        cur = t;
    }
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
