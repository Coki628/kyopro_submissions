/*
・自力AC！
・累積和と集計と全探索
・これも若干もたついた。なんかもっと簡単にできそう。
　ボブ側の右から累積和を、値をキーで個数を値にして持っておく。
　これを消しながら、左からアリスがどこまで食べるか全探索すれば、
　全位置で一致するのがあるかとその時の個数をチェックできる。
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
    vector<ll> A(N);
    cin >> A;

    Accumulate<ll> acc(A);
    map<ll, ll> C;
    rep(i, 1, N) {
        C[acc.query(i, N)] = N - i;
    }
    ll ans = 0;
    rep(i, 1, N) {
        if (C[acc.query(0, i)] > 0) {
            chmax(ans, i + C[acc.query(0, i)]);
        }
        C[acc.query(i, N)] = 0;
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
