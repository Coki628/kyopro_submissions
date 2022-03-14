/*
参考：https://atcoder.jp/contests/abc243/editorial
・自力ならず。。これは悔しい。
・完全二分木、2進数、スタック
・完全に考察方針ミスって帰ってこれなかった。
　以下、自戒の意味も込めてクソムーブを記しておく。
　・オーバーフローしそうだからPythonで書いてみるか → TLE
　・そうかでかすぎるのもあるんだな、MODでやって復元するやつ使えないかな
　　→切り捨て除算が。。
　・偶奇、いや素因数2の個数持っておけば切り捨て除算判定できないか
　　→奇数から偶数になった時、素因数2の個数分からない
　・そもそも方針がやばそう、陽に持つからやばいんであって、深さと横の位置だけとか持てば
　　→横位置もでかくなりすぎて無理じゃね (この辺で機能停止)
・正解方針は2つあった。1つは2進数文字列にして持つ方法。
　こっちのが自分的には思いつきやすそうに思えたからこっちで通した。
　本当にそのまんまシミュできる。切り捨て除算も末尾捨てるだけだし。
・もう1つが無駄な動きを全部先に取り除く方法。
　結局途中でRUとかLUとかした分は無な訳で、これはスタックに詰めていけば消せる。
　これやっとけば10^18より大きくならないから問題なく処理できる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define CAST_MINT_TO_LL
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

#include "numbers/ntod.hpp"

void solve() {
    ll N, x;
    cin >> N >> x;
    string S;
    cin >> S;

    string cur = bin(x);
    rep(i, N) {
        if (S[i] == 'U') {
            cur.pop_back();
        } elif (S[i] == 'L') {
            cur += '0';
        } else {
            cur += '1';
        }
    }
    ll ans = ntod(cur, 2);
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
