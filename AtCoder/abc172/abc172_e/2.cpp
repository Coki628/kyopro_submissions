/*
参考：https://manabitimes.jp/math/612
・dojo set_e_7_3
・なんとか自力AC！
・攪乱順列、包除原理
・色々悩んだけど、最終的に正解に繋がった考察を記しておく。
・まず数列Aはどんな風に置いてもいい。よってここはnPr(M, K)通りできるとしておく。
　以下、数列Aを一つ固定して数列Bを考える。
　数列Aと同じ位置に同じ値が入ってはダメなので、どうにかしようと考えると、それとなく既視感。
　攪乱順列だ。思い出せてよかった。今回は正確には順列じゃなく、
　M種類からN個を選ぶ必要があるけど、同じ位置がダメって制約はかなり考え方が近い。
　ググるといつものありがたいサイトが出てくるので、ここをよく読む。
　使えそうな方針がないか精査すると、最後の項の「包除原理を用いた公式の導出」
　の考察は、要素の種類数が増えても応用が効きそうだと思う。
　実際、全通りでN!の所をnPr(M, N)として、同じ位置になってしまう要素をk個選んだあと、
　残りの位置を(N-k)個自由に並べる代わりに、(M-k)個から選んでから(N-k)個並べるとすると、
　ここの!(N-k)がnPr(M-k, N-k)となり、これで話が合う。包除する。
　これで数列Bが取りうる通り数が分かるので、数列Aの全通りと掛ければ答え。
・包除っぽいなっていう考察は自分でも少し考えてたんだけど、
　位置1を同じ要素にして、位置2を同じ要素にして、、みたいに1要素ずつ固定で考えてしまった。
　これを位置じゃなくて個数で、1個同じ要素にして、2個同じ要素にして、、
　ってやれれば正解の方針だったので、そこまで自力で辿り着けるようにしたいなー。。
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

void solve() {
    ll N, M;
    cin >> N >> M;

    ModTools<mint> mt(M);
    mint ans = mt.nPr(M, N);
    rep(k, 1, N+1) {
        ans += mt.nCr(N, k) * mt.nPr(M-k, N-k) * pow(-1, k%2);
    }
    ans *= mt.nPr(M, N);
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
