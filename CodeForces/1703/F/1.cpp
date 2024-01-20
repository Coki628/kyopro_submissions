/*
・終了後自力AC。バチャ中なんか眠くなっちゃって頭回らんかった。
・条件のうち、添字が同じAi<iとAj<jは先に要素毎にチェックできる。
　これを満たさない要素Ai(Aj)はそもそもペアの候補に入らない。
　数を減らした数列A2を作って、ここでi<Ajを満たすものを累積和とか使って数える。
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

    vector<pll> A2;
    rep(i, N) {
        if (A[i] < i + 1) {
            A2.eb(A[i], i + 1);
        }
    }
    ll N2 = A2.size();
    Accumulate<ll> acc(N + 1);
    rep(i, N2) {
        acc.add(A2[i].second, 1);
    }
    acc.build();
    ll ans = 0;
    rep(i, N2) {
        ans += acc.query(0, min(A2[i].first, N + 1));
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
