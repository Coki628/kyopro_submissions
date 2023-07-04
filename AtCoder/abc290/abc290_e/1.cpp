/*
参考：https://atcoder.jp/contests/abc290/editorial/5757
　　　https://atcoder.jp/contests/abc290/editorial/5759
・やっとupsolved。むずい。これまじで水diffかよ。
・回文、余事象、主客転倒
・まず、操作する方よりしない方を求める方がいい。
　操作しない方の場合、回文内のペア位置で同じ値を取る所を見つければいいので、
　操作する方で必要な、異なる値を取る所を見つけるより大分やりやすくなる。
　よって、求めるのは、全て操作する場合の回数 - 操作しないで済む回数 みたいにする。
・「全て操作する場合の回数」も地味に簡単には取れない。よく考えて、
　とりあえず区間長で固定してその回数と掛けるみたいにした。(ソースコードも参照)
・で、やっと本題の「操作しないで済む回数」になる。
　これは、自身を右端として左端になる時をmapに詰めるいつものアレを、
　両端から真ん中に向かって進めていくみたいな感じでやる。
　こうすることで、そのペアを取る部分列の個数が定められる。
　(普通に右端のループ回すみたいな考え方でやると、
　これが左端の位置にも影響されてしまってうまく定められない。)
　ここまで来れば、後は同じ値を取るペアを適切に数えればOK。(ソース内コメントも参照)
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
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    // 全て操作する場合の回数total
    ll total = 0;
    rep(len, 1, N + 1) {
        // 長さlenの部分列の個数cnt
        ll cnt = N - len + 1;
        total += len / 2 * cnt;
    }
    vector<ll> C(N + 1);
    // 操作しないで済む回数sub
    ll sub = 0;
    rep(i, N / 2) {
        ll j = N - i - 1;
        // i,jが使われる部分列の通り数
        ll w = i + 1;
        // i,jが自身より外側とペアを組む回数
        sub += C[A[i]];
        sub += C[A[j]];
        // i,j同士で組む場合
        if (A[i] == A[j]) {
            sub += w;
        }
        // より内側と組む場合のためにi,jを重み付きで計上する
        C[A[i]] += w;
        C[A[j]] += w;
    }
    // 奇数長の真ん中
    if (N % 2 == 1) {
        sub += C[A[N / 2]];
    }
    ll ans = total - sub;
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
