/*
・終了後約30分で自力AC。。でもその前に1時間近く費やしてる。本日の戦犯その2。
・座圧した左右の重みをうまく取り込みながら、
　自身の左右を寄与を足し引きしつつ求める位置を動かしていく。
　なんだけど、添字的な調整が地獄だった…。
　もうちょい楽な方針がなかったか検討したい。
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

    Compress<ll> cp(A);
    ll M = cp.size();
    vvl adj(M);
    rep(i, N) {
        adj[cp[A[i]]].eb(i);
    }
    ll lval = 0, rval = 0;
    ll cnt = N - adj[0].size();
    rep(cpa, 1, M) {
        ll len = cp.unzip(cpa) - cp.unzip(cpa - 1);
        rval += len * cnt;
        cnt -= adj[cpa].size();
    }
    ll lcnt = 0, rcnt = N;
    vector<ll> ans(N);
    rep(cpa, M) {
        for (auto i : adj[cpa]) {
            ans[i] = N + lval + rval;
        }
        ll asz = adj[cpa].size();
        rcnt -= asz;
        lcnt += asz;
        if (cpa < M - 1) {
            ll alen = cp.unzip(cpa + 1) - cp.unzip(cpa);
            rval -= alen * rcnt;
            lval += alen * lcnt;
        }
        
    }
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
