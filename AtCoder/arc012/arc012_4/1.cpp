/*
参考：https://maspypy.com/%e5%a4%9a%e9%a0%85%e5%bc%8f%e3%83%bb%e5%bd%a2%e5%bc%8f%e7%9a%84%e3%81%b9%e3%81%8d%e7%b4%9a%e6%95%b0%ef%bc%88%ef%bc%92%ef%bc%89%e5%bc%8f%e5%a4%89%e5%bd%a2%e3%81%ab%e3%82%88%e3%82%8b%e8%a7%a3%e6%b3%95#toc10
　　　https://betrue12.hateblo.jp/entry/2020/02/23/173513
・FPS演習、と言いつつなんかライブラリ整備がメインみたいになった。
・FPS、任意MOD二項係数、ランダムウォーク
・FPSは考察パートで使う。今回は添字が2つあるし、直接高速計算ができる訳ではない。
　詳細はmaspyさんの記事もよく参照して欲しいけど、
　ようは(x+y)^nみたいな二項の形は二項係数の和に式変形すると、
　答えが求めやすくなる時がある。最初はどう使うかよく分からなかったけど、
　今理解できたお気持ちを書き記しておく。
・DPで言う所の添字に当たるx,y部分だが、変数部分をこのxyだけにできると、
　x[a]y[b]みたいな特定の添字に当たる場所の値が、一発で分かる時がある。
　今回は色々こねこねすると、F^T = ΣnCr(T, i)nCr(T, j)x^(i+j-T)y^(i-j)
　って形になるんだけど、このx,yの添字部分(i+j-T)と(i-j)に、
　実際に与えられるx,yを当てはめて、式変形してi=とj=の形に整える(連立方程式の代入みたいにやる)と、
　i = (x+y+T)/2, j = (x-y+T)/2 となり、これを先程のnCr(T, i)nCr(T, j)に当てはめれば、
　二項係数の和から、この部分だけ切り取って逆算みたいにして答えが求まる。
　二項係数の和にできても、結局和の形じゃループ回さなきゃじゃないか、と思って腑に落ちなかったんだけど、
　この特定の添字だけ逆算するみたいな考え方を理解出来たら合点がいった。確かに使える。
・ここが分かれば、後は自明に無理が偶奇が合わない弾いたりして、答え全部掛け合わせればいいだけ。
・さて、考察はこれでいいんだけど、任意MODのnCrが地味に大変だった。
　前mod 3で使っただけで安心してたやつは盛大にバグって(というか使い方間違えて)いた。。
　内部にメインのMODと素因数毎のmodがあるので区別する必要があったのと、
　そもそもcrtで復元が必要だった。アルメリアさんに申し訳がない…。
　諸々ちゃんと直したら、無事AC。
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

#include "combinatorics/ArbitraryModInt.hpp"
#include "combinatorics/AnyModTools.hpp"

void solve() {
    ll N, T, mod;
    cin >> N >> T >> mod;

    using mint = ArbitraryModInt;
    mint::set_mod(mod);
    AnyModTools amt(mod, 1200007);

    mint ans = 1;
    rep(_, N) {
        ll x, y;
        cin >> x >> y;

        if ((x+y+T)%2 != 0) {
            ans = 0;
            break;
        }
        ll i = (x+y+T)/2;
        ll j = (x-y+T)/2;
        ans *= amt.nCr(T, i)*amt.nCr(T, j);
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
