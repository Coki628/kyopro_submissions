/*
・終了後自力AC。間に合わず。Dで沼って時間がなかった。
　とはいえ終了後30分くらいでのACは遅すぎたので、どのみち時間内はきつかったかも。
・期待値、寄与、数え上げ、BIT2本
・方針としてはとりあえず寄与にする。
　あるA[i]が新しく追加される時、A[i]以下の要素とペアを組むならA[i]増えるし、
　A[i]超の要素と組むならその要素分増える。これはBIT2本で個数と和を管理するやつで対応できる。
　これで寄与の和を更新していきながら、その時点での全パターン数(i+1)^2で割って期待値にする。
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
    vector<ll> A(N);
    cin >> A;

    ll M = 200000;
    BIT<ll> bitcnt(M+1), bitsm(M+1);
    mint val = 0;
    rep(i, N) {
        // A[i]以下の要素の個数*2*A[i] + A[i]超の要素の和*2 + A[i](自身同士ペアの分)
        val += bitcnt.query(0, A[i]+1)*2*A[i] + bitsm.query(A[i]+1, M+1)*2 + A[i];
        mint res = val / pow(i+1, 2, MOD);
        print(res);
        bitcnt.add(A[i], 1);
        bitsm.add(A[i], A[i]);
    }
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
