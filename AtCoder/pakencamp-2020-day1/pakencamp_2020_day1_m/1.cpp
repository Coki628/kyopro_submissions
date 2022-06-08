/*
・その他埋めAC数上げ
・自力ならず。
・ビットで部分集合から遷移するDP
・xor基底みたいにor基底的なものが分かればいけると思ったけど分からず。
　方針としては全然そういう感じじゃなくてDPだった…。
・前提として、ある数xを作りたい時、今ある要素のうちxの部分集合となるようなものを
　全部orしてみてダメなら無理だしいけるならいける。(言われたら確かにそうかも)
・これを小さい値から見て行くと、xから1ビット減らしたものからxに遷移させるような形で、
　上記と同じチェックをしていける。
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

    ll L = 20;
    ll M = 1LL<<L;
    vector<ll> dp(M);
    rep(i, N) {
        dp[A[i]] = A[i];
    }
    ll ans = 0;
    rep(i, 1, M) {
        // iより1ビット削った場所から貰うDP
        rep(j, L) {
            dp[i] |= dp[i&~(1LL<<j)];
        }
        // iを構成できていれば答えに足す
        if (dp[i] == i) ans++;
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
