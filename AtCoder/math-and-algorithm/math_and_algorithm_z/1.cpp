/*
・期待値の線形性、2乗和の公式
・危なかった。ちょっと考えた。今i種類のコインを持っているとして、
　ダブる確率と、新しいのを引ける確率が分かれば、i+1枚目を引く期待値が分かる。
　これはある確率の事象を目指す時に、そうなるまでの期待値は確率の逆数、
　みたいに覚えてたから、それが通用した。
・でもこれ、2乗和の公式がそうなってるからうまくいくみたいだね。(本p.61見て)
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

    ld ans = 0;
    rep(i, N) {
        ans += N/(ld)(N-i);
    }
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
