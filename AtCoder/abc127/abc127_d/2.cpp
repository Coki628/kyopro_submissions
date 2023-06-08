/*
・想定と違ったけど無事ACは確認。
・同じ値をまとめて、優先度付きキューで貪欲にやる。
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
    vector<ll> A(N);
    cin >> A;

    priority_queue<pll, vector<pll>, greater<pll>> que;
    for (auto [k, v] : Counter(A)) {
        que.push({k, v});
    }
    rep(i, M) {
        ll b, c;
        cin >> b >> c;
        ll cnt = 0;
        while (que.size() and que.top().first < c) {
            auto [k, v] = que.top();
            que.pop();
            ll use = min(b, v);
            b -= use;
            v -= use;
            cnt += use;
            if (v > 0) {
                que.push({k, v});
                break;
            }
        }
        que.push({c, cnt});
    }
    ll ans = 0;
    while (que.size()) {
        auto [k, v] = que.top();
        que.pop();
        ans += k * v;
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
