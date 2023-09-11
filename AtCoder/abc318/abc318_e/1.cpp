/*
・なんとか自力AC。時間かかりすぎ…。
・3つ組は真ん中固定
・真ん中固定で、1つ動かした時の差分だけ見て更新をしていけばOK。
　なんだけど、数えるのは3つ組で3つのindexを見るのに、
　差分更新は2つのindexで考えるので、
　細部の詰めがゴチャゴチャしてすごく時間かかってしまった…。
・nok0さんの公式解法がほぼ同じ方針なので、実装を確認。
　C1に足す所を1つ手前をやる感じすると良さそう。
　でも他の人何人か実装見たら色毎にまとめて見る方針やってる人のが多そうだったので、
　そもそもそっちの方針取れなかったのが失敗だったかもしれん。
参考：https://atcoder.jp/contests/abc318/submissions/45107060
　　　https://atcoder.jp/contests/abc318/submissions/45149034
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
    A--;

    vector<ll> C1(N), C2(N);
    C1[A[0]]++;
    rep(i, 1, N) {
        C2[A[i]]++;
    }
    ll cur = 0, ans = 0;
    rep(j, 1, N - 1) {
        C2[A[j]]--;
        cur -= C1[A[j]];
        // 隣接が同じ時も引いてしまっているので戻す
        if (A[j - 1] == A[j]) {
            cur++;
        }
        cur += C2[A[j - 1]];
        ans += cur - C1[A[j]] * C2[A[j]];
        C1[A[j]]++;
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
