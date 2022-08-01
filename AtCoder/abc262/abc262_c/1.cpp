/*
・なんとか自力AC。。誤読がきつい。
・最初、Ai,Ajペアのmin,maxじゃなくて、区間[i,j]のmin,maxかと思ってしまって終了。。
　よく見るとそんなことどこにも書いてないのに、雰囲気で解いちゃうとダメだねー。。
・正しい問題が分かると、これはA[i]=iならそれらで好きに組めるし、
　そうでないなら対になる場所としか組みようがないのでそこだけチェック、
　みたいな場合分けでいける。
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
    auto A = LIST(N);

    rep(i, N) A[i]--;
    Accumulate<ll> acc(N);
    rep(i, N) {
        if (A[i] == i) {
            acc.set(i, 1);
        }
    }
    acc.build();

    ll ans = 0;
    rep(i, N) {
        if (A[i] == i) {
            ans += acc.query(i+1, N);
        } else {
            if (A[i] > i and A[A[i]] == i) ans++;
        }
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
