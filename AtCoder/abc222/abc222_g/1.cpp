/*
参考：https://www.youtube.com/watch?v=lxY_xv5Bdu0
　　　https://atcoder.jp/contests/abc222/editorial
・式変形、BSGS
・むずい。やっぱ数学寄りの問題は大変。
・まず式変形パート。公式解で突然2/9とか出てきて何が起きたのかと思ったけど、
　解説動画のsnukeさんの丁寧な解説に感謝。
　とりあえずそのままだと扱えないので、10冪の形に持っていこうと思うと、
　割る2して111..で掛ける9で999..になって+1して10^nだねってなる。
　これをさらに変形させて 222.. = 2*10^n/9-1 として、これをKの倍数にしたいので、
　2*10^n/9-1 = K*x のxが1以上の整数になればいい。
　今度は10冪を軸にして 10^n = 9*K*x/2+1 として、ある周期で1となる数を求める形に持っていく。
　/2が邪魔なのでKの偶奇で場合分け。Kが偶数ならそこで約分できるのでそのままでよくて、
　奇数だったらxの方が偶数でないといけないので、
　そっちで約分するとして/2が消えた 9*K*x+1 の形にする。
　これで 10^n ≡ 1 mod 9*K/2 か 10^n ≡ 1 mod 9*K での最小のnを求める問題にできた。
　この形であればそのままBSGSの定義がほぼそのままハマるので、使う。
　ただし、n^0=1ではダメなので、n^1以降での最小とする必要がある。
　任意の場合に使えるやつがlibrary checkerにあったけど、
　ここの調整をどういじればいいか分からず使えなかった…。
　xとmodが互いに素であれば、普通っぽいBSGSが使えるので、こっちで行く。
　今回はxとmodが互いに素でなければ、即NGでいいようなので。
　(まあ確かに例えばmodが偶数だったらそもそも10冪で永遠に奇数にならんだろうから
　1にするのは無理だろうなぁ、とは思う。お気持ち。)
　10^0を使わない処置としては、開始位置を10^1にしておいて後で回数1回足すとか、
　最初の状態を訪問済みとしてmapに入れるのをしないとか、そんな感じで。前者でやった。
・これで無事ACはするんだけど、最初のは1.91秒かかってギリギリだった。
　制約でT*Kが2*10^10なので、計算量が√K*Tだと200万で、これにmapのlogが乗ったからだと思う。
　最近仕入れたNyaanさんのHashMapにBSGSの実装変えたら、0.42秒になった。すげーや。
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
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

#include "numbers/bsgs.hpp"

void solve() {
    ll K;
    cin >> K;

    ll mod = K * 9;
    if (K%2 == 0) {
        mod /= 2;
    }

    if (gcd(10, mod) != 1) {
        print(-1);
        return;
    }

    ll res = bsgs(10, 1, mod, 10);
    if (res != -1) res++;
    print(res);
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
