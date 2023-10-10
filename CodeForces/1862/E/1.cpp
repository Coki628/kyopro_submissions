/*
・なんとか自力AC。本質に気付くのに大分時間かかった…。
・優先度付きキュー
・一見無理そうな話に見えるが、Dに係るマイナスの寄与は実は
　途中でどこを選ぼうが選ぶまいが変化がなく、最後に選んだ要素だけに影響される。
　これが分かると、最後に選ぶ要素を決めて全探索できる。
　今見ている要素より手前で大きいものM-1個以下を保持しながら前に進む。
　これは優先度付きキューでできる。
　正数要素以外は持っても損するので、そこはちゃんと場合分けする。
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
    ll N, M, D;
    cin >> N >> M >> D;
    vector<ll> A(N);
    cin >> A;

    priority_queue<ll, vector<ll>, greater<ll>> que;
    ll mxsm = 0, ans = 0;
    rep(i, N) {
        while (que.size() > M - 1) {
            mxsm -= que.top();
            que.pop();
        }
        chmax(ans, mxsm + A[i] - D * (i + 1));
        if (A[i] > 0) {
            mxsm += A[i];
            que.push(A[i]);
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
