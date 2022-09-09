/*
参考：https://twitter.com/SSRS_cp/status/1567915079450136576
・自力ならず。。悔しい。
・優先度付きキュー、貪欲
・プリキューで大きい方から貪欲。これでいいのかって感じだけど、これでよかった。
　なーんかプリキューの貪欲って気付かないがちなんだよなー…。
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

const auto f = [](ll a) -> ll {
    return tostr(a).size();
};

void solve() {
    ll N;
    cin >> N;
    auto A = listnd(2, N, 0LL);
    rep(i, 2) {
        A[i] = LIST(N);
    }
    vector<HashMap<ll, ll>> C(2);
    rep(i, 2) {
        C[i] = Counter(A[i]);
    }

    priority_queue<pll, vector<pll>> que;
    rep(i, 2) {
        for (auto [k, v] : C[i]) {
            rep(_, v) {
                que.push({k, i});
            }
        }
    }
    ll ans = 0;
    while (que.size()) {
        auto [a, i] = que.top(); que.pop();
        // 既に使用済
        if (C[i][a] == 0) continue;
        C[i][a]--;
        if (C[1-i][a] > 0) {
            C[1-i][a]--;
        } else {
            a = f(a);
            C[i][a]++;
            ans++;
            que.push({a, i});
        }
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
