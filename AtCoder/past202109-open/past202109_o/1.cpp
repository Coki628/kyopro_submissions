/*
参考：https://atcoder.jp/contests/past202109-open/editorial/2358
・自力ならず。
・トーナメント、二分木の実装
・自力では謎のDPを頑張ろうとしたりして全然いい方針立たず。
・まず、色に関して人1の色を青とか適当に決めておくとする。
　2色分けで、条件も異なるか等しいかだけなので、
　全員色を反転させたものが同様に有効になる。なので最後に×2するとする。
　それで、条件によって結果が決まっている試合とそれに至るまでの試合に関しては、
　勝者が決まっている。よってここは塗り分けが一意。ここまではまあいい。
　問題は他の結果が決まっていない試合だけど、実はこれは何やってもいいらしい。
　結果が決まってる試合とぶつかる時に、話が合わなくなる場合がありそうに思ってしまうけど、
　やってみると確かに合う。正確には、ちょうど半分はOKな塗り分けがあって、
　前述の全部反転させた場合にもう半分がOKになるみたいなことのようだ。
・上記考察が整ったら後は実装。セグ木内部みたいに二分木を走査して、
　各試合での勝者が決まっているか、整合性が取れてるかをチェックする。
　全部辻褄が合っていれば、未確定の試合の数だけ全通りやるので2冪するだけ。
・あと順列の並びの配列でいつもこんがらがるやつだけど、
　今回使うのは「位置iにいるp」じゃなくて「pのいる位置i」なので、
　入力受け取ったそのままじゃなくて、持ち替えをちゃんとやっておく。
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
    ll N, M;
    cin >> N >> M;
    ll L = pow(2, N);
    vector<ll> P(L), ptoi(L);
    cin >> P;
    P--;
    rep(i, L) {
        ptoi[P[i]] = i;
    }
    ll L2 = L * 2;

    // 確定済の試合を確認
    vector<ll> fixed(L2, -1);
    rep(i, M) {
        ll w, l;
        cin >> w >> l;
        w--; l--;

        ll cw = ptoi[w] + L;
        ll cl = ptoi[l] + L;
        while (cw != cl) {
            if (
                fixed[cw] != -1 and fixed[cw] != w or
                fixed[cl] != -1 and fixed[cl] != l
            ) {
                print(0);
                return;
            }
            fixed[cw] = w;
            fixed[cl] = l;
            cw /= 2;
            cl /= 2;
        }
        if (fixed[cw] != -1 and fixed[cw] != w) {
            print(0);
            return;
        }
        fixed[cw] = w;
    }

    ll d = 0;
    rep(i, 1, L) {
        if (fixed[i] == -1) {
            d++;
        }
    }
    mint ans = mint(2).pow(d) * 2;
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
