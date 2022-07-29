/*
・終了後自力AC！TLでキーワードちら見してたけどこれは解けただろう…。
・転倒数、座圧
・なんとなく題意を考えると、全体の転倒数を求めて、色毎の転倒数を全部引けば求まりそう。
　実際そうで、それで問題なくAC。。
　色毎にやる時は、毎回長さNのBITを初期化するとまずいので、適切に座圧してやること。
・まーじでさっさとこっち考えれば良かった…。
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
    auto B = LIST(N);
    rep(i, N) {
        A[i]--;
        B[i]--;
    }

    ll ans = 0;
    BIT<ll> bit(N);
    rep(i, N) {
        ans += bit.query(B[i]+1, N);
        bit.add(B[i], 1);
    }
    vvl adj(N);
    rep(i, N) {
        adj[A[i]].eb(B[i]);
    }
    rep(i, N) {
        if (adj[i].size()) {
            Compress<ll> cp(adj[i]);
            adj[i] = cp.zip(adj[i]);
            ll n = cp.size();
            BIT<ll> bit(n);
            ll inv = 0;
            rep(j, adj[i].size()) {
                inv += bit.query(adj[i][j]+1, n);
                bit.add(adj[i][j], 1);
            }
            ans -= inv;
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
