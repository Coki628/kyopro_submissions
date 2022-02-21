/*
・きっちり自力AC
・制約から、全ペア試せる。orが変わらない限り削れる条件なので、つまりそれは
　andな部分は削れるということ。あとは操作順によって結果が変わらないか悩んだけど、
　WAが出たらちゃんと検討すればいいやくらいでぶん投げて無事AC。
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

    rep(i, N) {
        rep(j, i+1, N) {
            A[i] -= A[i]&A[j];
        }
    }
    print(sum(A));
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
