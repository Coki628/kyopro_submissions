/*
・自力AC。
・決め打ち二分探索
・決め打ちにぶたん。1時間で終わるやつを閾値までできるだけ使う。
　残りをまとめて使う時、2時間を2人が1時間ずつ余らせてるやつでもOKとしてしまっているのに中々気付けず…。
　後から突貫工事で直したから色々ゴチャゴチャしてしまった。
・なんかTL見た感じ、残タスクに*2じゃなくて残リソースに/2すれば、
　上記の話気にしなくてもよかったぽい。(直すの面倒で試してはいない)
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
    auto A = LIST(M);
    rep(i, M) A[i]--;

    auto C = Counter(A);
    ll res = bisearch_min(0, 1000000000000, [&](ll m) {
        auto cur = C;
        ll rest = (N-cur.size()) * (m-m%2), task = 0;
        vector<ll> rest2;
        for (auto [k, v] : cur) {
            ll use = min(v, m);
            rest2.eb(m-use);
            task += v - use;
        }
        task -= rest / 2;
        for (auto r : rest2) {
            task -= r / 2;
        }
        return task <= 0;
    });
    print(res);
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
