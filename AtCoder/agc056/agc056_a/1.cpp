/*
参考：https://atcoder.jp/contests/agc056/editorial
・グリッド、構築
・類題(cf1360_G)をやったので、これも通しておいた。
　まあ確かにグリッド構築手順の前半パートは同じ感じだけど、発想は…。
・とりあえず、N*Nのグリッドだと、行にx個(今回は3個固定だけど)置いたら次の行、ってやって、
　最後の列まで言ったら最初に戻って、ってのをやってくと、
　最後のマスはぴったりx個終わる所で収まるみたい。で、縦もx個ずつになってる。
　これがまず非自明だし、なのでこの方針に行けるかが分からない。
・で、さらに今回は連結成分数がN個って条件があって、
　これはさっきの手順を踏むと、3の倍数ならぴったり行く。
　じゃあそうじゃない時はどうかと言うと、常に連結成分はN+2個になる模様。
　で、先頭と末尾でうまいことスワップさせると成分数がくっついて減るので、ちょうどNにできる。
・やっぱこういうのを発想できる気はしないなぁ。
　熱烈実験してようやく分かるかどうか、って感じ。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll N;
    cin >> N;
    const int M = 3;

    vector<string> ans(N, string(N, '.'));
    ll j = 0;
    rep(i, N) {
        rep(k, M) {
            ans[i][(j+k)%N] = '#';
        }
        j += M;
    }
    if (N%3 != 0) {
        ll d = N/M;
        swap(ans[0], ans[d]);
        swap(ans[N-1], ans[N-1-d]);
    }
    rep(i, N) {
        print(ans[i]);
    }
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
