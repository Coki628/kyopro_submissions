/*
・なんとか自力AC！
・ゲーム、1つ決めて全探索
・ボブはアリスが残したうち大きい方から取るのが最善そう。
　制約的に細かいことはやらないはずなので、どうせアリスも大きい方か小さい方からだろう、
　みたいな雑な予測で、アリスも大きい方優先で、何個取るか全探索、ってしたら通った。
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
    ll N, K, X;
    cin >> N >> K >> X;
    vector<ll> A(N);
    cin >> A;

    sort(ALL(A));
    Accumulate<ll> acc(A);
    ll ans = -INF;
    rep(r, N, max(N - K, 0LL) - 1, -1) {
        ll m = max(r - X, 0LL);
        chmax(ans, acc.query(0, m) - acc.query(m, r));
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
