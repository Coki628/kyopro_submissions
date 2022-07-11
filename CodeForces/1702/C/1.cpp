/*
・きっちり自力AC！
・クエリ先読み
・クエリ先読みして駅を前から見て訪問済にしてく。
　クエリの右端が来た所で左端とする駅が訪問済みかチェック。
・と、思ったらシステス落ち。ひどい。
　多分、クエリの右端が同じのばっかで、A[i]も同じのばっかだと、
　最後の2重ループが2乗になるとかそんな感じな気がする…。
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

    map<ll, vector<pll>> qs;
    rep(i, Q) {
        ll a, b;
        cin >> a >> b;
        qs[b].eb(a, i);
    }
    vector<string> ans(Q, "NO");
    set<ll> visited;
    rep(i, N) {
        visited.insert(A[i]);
        for (auto [a, j] : qs[A[i]]) {
            if (visited.count(a)) {
                ans[j] = "YES";
            }
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
