/*
・きっちり自力AC！
・出現数最大をcntとしてこれを目指す。スワップコストはN-cntは確実にかかる。
　分裂コストはそのcntをN以上になるまで2倍する。
・C++でもmost_commonそろそろライブラリ化したいなーって思ってた矢先だったので、やった。
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

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    ll cnt = most_common(Counter(A))[0].first;
    ll ans = N - cnt;
    while (cnt < N) {
        cnt *= 2;
        ans++;
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
