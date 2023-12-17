/*
・自力AC！
・K番目の値、全探索
・全探索で済ませたくなるが、オーバーフローしない範囲の探索で、
　Nの最大値333番目までをカバーできるかが気になる所。
　10^3でも1000なのでいけるだろ、と思うも結構重複がある模様。
　さてどのくらい大きくしようか、と考えようとしたら、
　サンプルに最大値が書いてあって優しいので、
　これを十分カバーできそうなくらいの大きさまで回す。
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

    vector<ll> vec;
    rep(i, 1, 15) {
        ll a = toint(string(i, '1'));
        rep(j, 1, 15) {
            ll b = toint(string(j, '1'));
            rep(k, 1, 15) {
                ll c = toint(string(k, '1'));
                vec.eb(a + b + c);
            }
        }
    }
    UNIQUE(vec);
    N--;
    print(vec[N]);
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
