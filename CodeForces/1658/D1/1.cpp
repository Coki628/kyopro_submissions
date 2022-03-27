/*
参考：https://twitter.com/laycrs/status/1508123140425412608
・自力ならず。。色々考えたけどダメだった。
・ビットの性質
・元の列が0からの順列なので、これをビットで表すと、
　立っているビットの数の合計は必ず全体Nの半分以下になる。
　これに気付ければ、ある数xで立っていたビットは、
　全て反転、つまり立っていた個数も反転しているはずで、
　立っているビットが半分超であれば、反転させられたと判断できる。
　半分ちょうどは、試してみると、結局どっちになっても結果の集合が変わらないことが確認できるので、
　半分超の所だけxでも立っていたと判断して答えに足せばOK。
・これに気付けなかった訳だけど、メモに書いてある図を見て考える時、
　同じビットが並ぶ縦の軸にもっと注目すれば気付けたかなぁ。
　こういうの見えない時ほんと見えないから、どうやって気付けばいいかっていつも思うよ。
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
    ll l, r;
    cin >> l >> r;
    ll N = r - l + 1;
    vector<ll> A(N);
    cin >> A;

    ll M = 17;
    vector<ll> C(M);
    rep(i, N) {
        rep(j, M) {
            if (A[i]>>j & 1) {
                C[j]++;
            }
        }
    }
    ll ans = 0;
    rep(i, M) {
        if (C[i] > N/2) {
            ans += 1LL<<i;
        }
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
