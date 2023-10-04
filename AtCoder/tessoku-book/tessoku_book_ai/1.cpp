/*
・グリッド、ゲームDP、ミニマックス法
・そのままピラミッド型だとやりづらいので、直角三角形で下か右下に行くとする。
　手番は行位置で分かるので状態は要らない。
　あとは手番によって最大化か最小化するいつものやつ。
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
    vector<ll> A(N);
    cin >> A;

    auto memo = listnd(N, N, -1LL);
    auto rec = [&](auto &&f, ll h, ll w) -> ll {
        ll turn = h % 2;
        if (h == N - 1) {
            return A[w];
        }
        if (memo[h][w] != -1) {
            return memo[h][w];
        }
        assert(w < N - 1);
        if (turn == 0) {
            return memo[h][w] = max(f(f, h + 1, w), f(f, h + 1, w + 1));
        } else {
            return memo[h][w] = min(f(f, h + 1, w), f(f, h + 1, w + 1));
        }
    };
    ll res = rec(rec, 0, 0);
    print(res);
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
