/*
・なんとか自力AC！！終了1分前とかで間に合った！
・DPする。例えば、区間4でやるのと区間2で2回やるのは同一視できるので、
　区間1操作と区間2操作だけ考える。で、今見ている要素を消すとして、
　区間1で消して余分を出さないか、区間2で消して余分を1つ先に渡すかみたいな2遷移でDPする。
　あと A[i]^余分 が0だったらそこはノーコストで遷移。状態にこの余分を持たせた。
・ワンチャンと思って一応D2にも投げたけどさすがに通らなかった。。
・そのままやったらMLEしたので配列節約テクは使う。
　この時もう残り3分くらいしかなくてまじで危なかった。
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

    vector<defaultdict<ll, ll>> dp(2, {INF});
    dp[0][0] = 0;
    rep(i, N) {
        for (auto [k, v] : dp[i%2]) {
            ll a = A[i] ^ k;
            if (a == 0) {
                // 何もしなくていい
                chmin(dp[(i+1)%2][0], v);
            } else {
                // 区間長1操作でここを消す
                chmin(dp[(i+1)%2][0], v+1);
            }
            // 区間長2操作でここを消す
            chmin(dp[(i+1)%2][a], v+1);
        }
        dp[i%2].clear();
    }
    ll ans = dp[N%2][0];
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
