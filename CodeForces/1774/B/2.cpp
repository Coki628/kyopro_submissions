/*
参考：https://codeforces.com/contest/1774/submission/185708039
・自力ならず。こういう割り算考察頑張るのはほんと苦手…。
・コーナーケース
・こっちがACするやつ。公式解説の説明もいまいちピンと来なかったし、
　これも結局AllDirectionsさんの実装から必要な部分を自分のコードに落としただけなんだけど。。
　ようは最大値が複数ある時には前述の方針がそのままだと取れなくて、
　最大値の個数に合わせた対応が必要になる。最大値が複数あると何か必要そうなのは自分でも思ったんだけど、
　結局うまく具体的な形にはできず、色々な人のツイートとか見た。
　最終的にこの、最大値部分を1と仮定して-1してたみたいな箇所を-mxcntに置き換えたやつが、
　強いて言えば一番自分の中からは捻り出しやすいのかなと思った。
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
    ll N, M, K;
    cin >> N >> M >> K;
    vector<ll> A(M);
    cin >> A;

    if (K > M) {
        NO();
        return;
    }
    if (K == 1) {
        YES();
        return;
    }
    ll mx = max(A);
    ll mxcnt = count(ALL(A), mx);
    ll rest = N - mx * mxcnt;
    if (rest >= (mx - 1) * (K - mxcnt)) {
        YES();
    } else {
        NO();
    }
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
