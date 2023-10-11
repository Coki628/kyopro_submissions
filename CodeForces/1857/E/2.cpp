/*
・元々やろうとしてた方針。
　寄与は全部前計算してしまって、各位置の答えは区間和取るだけで済むようにする。
　これやろうとして結局座圧の重みをうまく区間和に織り込めずに断念したんだけど、
　左を取りに行く用と右を取りに行く用で分けて作ればよかったね。
　それで座圧の重みを取り込む時に左右で逆にしておけば、
　取得時には悩まず素直に区間和が取れる。
　個数の寄与も前もって累積和しておけば、必要な区間和取ればいいね。
　本番中落ち着いてこれが書ければまだ良かったんじゃないだろうか。
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

    Compress<ll> cp(A);
    A = cp.zip(A);
    ll M = cp.size();
    vector<ll> C(M);
    rep(i, N) {
        C[A[i]]++;
    }
    Accumulate<ll> acccnt(C), accl(M), accr(M);
    rep(i, M - 1) {
        // 左を見に行く時には自身の右側の重みが欲しい
        accl.add(i, acccnt.query(0, i + 1) * (cp.unzip(i + 1) - cp.unzip(i)));
    }
    accl.add(M - 1, acccnt.query(0, M));
    accr.add(0, acccnt.query(0, M));
    rep(i, 1, M) {
        // 右を見に行く時には自身の左側の重みが欲しい
        accr.add(i, acccnt.query(i, M) * (cp.unzip(i) - cp.unzip(i - 1)));
    }
    accl.build();
    accr.build();

    vector<ll> ans(N);
    rep(i, N) {
        ans[i] = N + accl.query(0, A[i]) + accr.query(A[i] + 1, M);
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
