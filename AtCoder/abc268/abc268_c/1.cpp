/*
・自力AC！
・円環
・スコアの入る3箇所だけ++するのを集計してmax、添字考えるのがつらい。
　結局、P[i]-i ってやると「P[i]がぴったりの位置にくるためのシフト回数」
　みたいのが分かるので、そこを起点にしてやる。
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
    ll N;
    cin >> N;
    auto P = LIST(N);

    vector<ll> C(N);
    rep(i, N) {
        ll d = P[i] - i;
        rep(j, d-1, d+2) {
            C[modulo(j, N)]++;
        }
    }
    ll ans = max(C);
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
