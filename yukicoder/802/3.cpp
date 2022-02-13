/*
参考：https://yukicoder.me/submissions/420417
　　　https://maspypy.com/%e5%a4%9a%e9%a0%85%e5%bc%8f%e3%83%bb%e5%bd%a2%e5%bc%8f%e7%9a%84%e3%81%b9%e3%81%8d%e7%b4%9a%e6%95%b0%ef%bc%88%ef%bc%92%ef%bc%89%e5%bc%8f%e5%a4%89%e5%bd%a2%e3%81%ab%e3%82%88%e3%82%8b%e8%a7%a3%e6%b3%95#toc13
　　　https://opt-cp.com/fps-implementation/
　　　https://koba-e964.hatenablog.com/entry/2019/03/18/000751
・FPS演習
・FPS、式変形、冪乗の高速化
・2項の冪乗は二項係数をうまく使って高速化できる。
　baitoさんの提出を精読した。色々勉強になった。
・ゴリゴリ式変形していくんだけど、まずは等比数列の和を使う。
　今回遷移先はd1~d2までで多いんだけど区間になっているので、
　こういうのは全体に左端までのxの冪乗掛けると、
　1からの等比数列の和に変形できて、項を2つだけにできる。
　DPでも累積和取れば始点と終点の2点操作みたいにできるもんね。
・で、項が2つだけになると、二項係数をうまく使ってlog乗せないで計算する方法があった。
　注意点として、nCrだけでなく、逆元の時はnHrも使うので、
　前計算の上限が十分かはちゃんと確認すること。(これで最後ずっとWAだった。。)
・あと単一の項を掛ける時は、その分全体の次数が増減するので、
　数列としては左右にシフトすると考えていい。
　FPSクラスにそういうシフト演算が実装されているが、
　今回はここがとても大きくなることがあり陽に持ちたくないので、
　optさんのところからsparseな列に使う乗除算を持ってきている。
　この中の処理だと大きくなり過ぎる所は無視してくれるのでいい感じ。
・kobaeさんの解説記事からも情報を得た。そこから、
　最後に総和する所は、1/(1-x)と変形できる。
　ここまで変形するとやっとbaitoさんの式とほぼ同じ形になる。
　(ここからさらにD1の大きさによってよしなにMの位置を変えているが、
　それの代わりにこちらでは最後に右シフトで次数を上げるようなことをしている。)
・ここまで全て整えると、項数M(100万)ある多項式乗算は1回だけになる。無事AC、0.82秒。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
// #define MINT_TO_LL_CAST
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

#include "math/FormalPowerSeries.hpp"
#include "math/fps/pow_term2.hpp"

void solve() {
    ll N, M, D1, D2;
    cin >> N >> M >> D1 >> D2;

    // 等比数列の和で式変形して、2項の式にしてから冪乗する
    // F := x / (1-x)
    // G^(N-1) := (x^d1)^(N-1) * (1-x^(d2-d1+1))^(N-1) / (1-x)^(N-1)
    // H(最後に総和とする分) := 1 / (1-x)
    // F*G^(N-1)*H := x^(d1*(N-1)+1) * (1-x^(d2-d1+1))^(N-1) / (1-x)^(N+1)
    FPS<mint> fps = pow_term2(D2-D1+1, N-1, M+1)*pow_term2_inv(N+1, M+1);
    fps.shrink();
    SFPS<mint> tmp = {{D1*(N-1)+1, 1}};
    fps *= tmp;
    mint ans = fps[M];
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
