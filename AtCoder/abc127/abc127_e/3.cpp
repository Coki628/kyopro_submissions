/*
参考：https://atcoder.jp/contests/abc127/editorial
・dojo set_d_4_5
・自力ならず。。こういう数え上げ、ほんと解けるようにならないね。
・二項係数数え上げ、縦横独立、主客転倒
・多分、気付くべきポイントは3段階あった。
・まずXYで縦横独立。ここからして見えなかった。。
　マンハッタン距離は縦横独立って唱えるくらいでいいのかもしれない。
・で、ここから何を固定すれば効率的に、排反に、数えられるか考える。
　使う行ペアを固定とか考えたけど、全然排反にならなかった。
　正解は使うマスペアを固定、だった。これだとマス間の距離をdとして
　その2マス間にかかるコストdはそれ以外の全マスからK-2マス置く通り数だけ使われるので、
　d*nCr(N*M-2, K-2)みたいにできる。これでマスペアなので(N*M)^2。もう1段要る。
・どういう時を同一視できるか考えると、距離を固定できる。
　横にずらす位置がM-dだけあって、縦は両者とも自由に置けるのでN^2、
　これをさっきのやつにさらに掛ける。これで距離dの全探索にまとまった。
　今は横のコストで説明したけど縦もNM入れ替えるだけで同じ。
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
    ll N, M, K;
    cin >> N >> M >> K;

    ModTools<mint> mt(N*M);
    mint ans = 0;
    rep(d, 1, M) {
        ans += mt.nCr(N*M-2, K-2)*(M-d)*N*N*d;
    }
    rep(d, 1, N) {
        ans += mt.nCr(N*M-2, K-2)*(N-d)*M*M*d;
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
