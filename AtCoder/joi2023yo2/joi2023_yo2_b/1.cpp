/*
・きっちり自力AC！
・ソートして尺取り
・4クラス全部一緒にソートして尺取りする。
　伸び縮みの条件を4クラス全部揃ってるかどうかにすれば、
　揃ってるうちで最小限の長さを取っていけるので答えが求まる。
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
    ll K = 4;
    auto A = listnd(K, N, 0LL);
    rep(i, K) {
        cin >> A[i];
    }

    vector<pll> vec;
    rep(i, K) {
        for (auto a : A[i]) {
            vec.eb(a, i);
        }
    }
    sort(ALL(vec));

    Deque<pll> que;
    vector<ll> C(4);
    ll ans = INF, hascnt = 0, i = 0;
    rep(_, N * 4) {
        while (i < N * 4 and hascnt < K) {
            auto [a, c] = vec[i];
            que.eb(vec[i]);
            C[c]++;
            if (C[c] == 1) hascnt++;
            i++;
        }
        // 満たしてると限らないので条件チェックする
        if (hascnt == K) {
            chmin(ans, que.back().first - que.front().first);
        }
        auto [a, c] = que.pop_front();
        C[c]--;
        if (C[c] == 0) hascnt--;
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
