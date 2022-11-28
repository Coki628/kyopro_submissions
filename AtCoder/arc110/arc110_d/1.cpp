/*
参考：https://ei1333.hateblo.jp/entry/2021/07/30/144201
　　　https://twitter.com/0x3b800001/status/1595284625890619392
・積の和典型
・考え方がとても難しい。うしさんの記事だけだとよく分からなくて、
　まぐふらいさんのスライドでやっと理解。3つ目の言い換えは本当に知らないとできないと思った。
・積の和典型はとりあえず、「ΣΠ何か」みたいな形の時に、
　計算を二項係数数え上げと対応付けることで、直接積の和を取らなくても答えが求まる、
　みたいな感じの話なんだけど、難しいので別の所でまとめる。
・この問題は、上記参考でも紹介されている最初の例題を発展させたような形の問題。
　基本的な仕切りの入れ方とか3つ目の言い換えの理屈は、まぐふらいさんのスライドを参照。
・ここで、3つ目の言い換えの時に選び出す玉の数が元の例題だとN個増えるんだけど、
　これは各A[i]でどれか1つ玉を選ぶのでN個という感じなので、
　いわばnCr(A[i], 1)みたいな話で、今回はこれがnCr(B[i], A[i])のようになるので、
　数列サイズのNではなく、sum(A)が代わりに使われることになる。
・もう1つ異なるのが、例題だとMちょうどになっていた所がここではM以下となっている。
　これに対応させるには、仕切りを1つ増やせばいい。
　これで使わない要素を最後の仕切りの右側に出すと思えば、ほぼ同じ形にできる。
　ここまでをまとめると、nCr(M+N, S+N)やるだけになる。
・最後に実装上の注意として、nCrのnが大きいので、計算量O(r)でいける方法を使う。
　(久々に使ったけど、これたまーに出る印象。)
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

#include "combinatorics/nCr.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> A(N);
    cin >> A;

    ll S = sum(A);
    mint ans = nCr<mint>(M+N, S+N);
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
