/*
・なんとか自力AC。
・転倒数の最小化ってのはブラフで、全部転倒数0にできる、はず。
　値の大きい所から順に開始位置に選ぶと転倒数0になるはず。
　Div.2Cでこんな単純なソート貪欲だけとかあり？と思ったけど通った。
・なんか添字の置き方間違えてWAってて、ランダムチェックで修正して何とか通せた。
　ギャグっぽい感じだったのに、ここでだいぶ時間使ったのはきつかった。
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

#include "common/randrange.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);
    // N = randrange(1, 11);
    // vector<ll> A(N);
    // iota(ALL(A), 1);
    // shuffle(ALL(A), mt);

    vector<pll> AI;
    rep(i, N) {
        AI.eb(A[i], i);
    }
    sort(AI.rbegin(), AI.rend());
    vector<ll> ans(N);
    rep(i, N) {
        auto [a, j] = AI[i];
        ans[i] = j + 1;
    }
    print(ans);
    // auto B = A;
    // rep(i, N) {
    //     rep(j, ans[i]-1, N) {
    //         B[j] += i + 1;
    //     }
    // }
    // if (not (B == sorted(B))) {
    //     debug(A);
    //     debug(B);
    // }
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
