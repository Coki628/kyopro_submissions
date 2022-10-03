/*
参考：https://codeforces.com/blog/entry/107461
・自力ならず。TL見てもいまいち分からず、公式解説を熟読して理解。
・ゲーム、二項係数数え上げ
・大事な考察があって、そこに気付かないことには正解はなかった。
　まず、引き分けのパターンは1つだけ。(これは何となく分かる。)
　で、大事なのは、その引き分けパターンから1つ外れたら、そこで即決着がつくってこと。
　それとゲームは、常に持っている最大の数をお互いに出そうとして進行していくこと。
　(相手がそれより強いカード持ってなければ即勝ちだし、先延ばすメリットがない。)
　これで、iターン目で決着がつく(iターン目で初めて引き分けパターンから外れる)を全探索、
　の方針に辿り着ける。ここまで来るとやっとTLでみんなが言ってたことが理解できる。
・方針が分かればそこからの二項係数はそんな難しくなくて、
　決着がつく場所以降の使われなかったカードの選び方だけ考えればOK。
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
    ll N;
    cin >> N;

    ModTools<mint> mt(N);
    vector<mint> ans(3);
    rep(i, N, 0, -2) {
        if ((N-i)%4 == 0) {
            // mod 4の0ターン目でA勝ち
            ans[0] += mt.nCr(i-1, (i-1)/2);
        } elif ((N-i)%4 == 2) {
            // mod 4の3ターン目でA勝ち(Aが多く取ってる状態なので選ぶ数はちょうど半分から1つずれる)
            ans[0] += mt.nCr(i-2, (i-2)/2+1);
        }
    }
    mint total = mt.nCr(N, N/2);
    ans[1] = total - ans[0] - 1;
    ans[2] = 1;
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
