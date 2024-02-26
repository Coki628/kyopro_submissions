/*
・終了後自力AC。
・平方数、ペア数え上げ、式変形、素因数分解
・本質パートはabc254_dから拝借してきた。最初自力導出しようとして結局できなくて。
　本来なら本番ACに間に合うはずだったけど、
　2重ループrep(c, 1, M + 1)のMがNになっていて、これを発見できず時間切れ。
　そもそも本質パートをうまく咀嚼しきれていないのが良くないんだよね。
　abc254_dの時も思ったけど、この考察むずいと思うんだけど、
　なんかみんなかなり通すんだよなー…。
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
    auto A = LIST(N);

    ll M = max(A);
    vector<ll> C(M + 1);
    for (auto a : A) {
        C[a]++;
    }
    ll ans = 0;
    rep(i, 1, M + 1) {
        // 素因数が奇数の部分aは他方でも必ず必要になるので、ここをまず求める
        // i = a * b^2
        ll a = 1;
        for (auto [k, v] : factorize(i)) {
            if (v % 2 == 1) {
                a *= k;
            }
        }
        // 少なくともaの部分はjに含まねばならず、それ以外は2乗で表せれば何でもいいので、c^2の部分を1から全探索
        // j = a * c^2
        rep(c, 1, M + 1) {
            ll j = a * c * c;
            if (j > M) break;
            if (i == j) {
                ans += nC2(C[i]);
            } else if (i < j) {
                ans += C[i] * C[j];
            }
        }
    }
    ans += nC2(C[0]);
    ans += C[0] * (N - C[0]);
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
