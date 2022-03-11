/*
・きっちり自力AC！
・両端4つ以外心配しなくていい。両端同士で組ませるかどうかを7通り書き出して筋肉場合分け…
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);
    auto B = LIST(N);

    ll ans = INF;
    // 4つバラバラ
    vector<ll> cost(4, INF);
    rep(i, N) {
        chmin(cost[0], abs(A[0]-B[i]));
        chmin(cost[1], abs(B[0]-A[i]));
        chmin(cost[2], abs(A[N-1]-B[i]));
        chmin(cost[3], abs(B[N-1]-A[i]));
    }
    chmin(ans, sum(cost));
    // (1,1) + 2つバラバラ
    cost.assign(2, INF);
    rep(i, N) {
        chmin(cost[0], abs(A[N-1]-B[i]));
        chmin(cost[1], abs(B[N-1]-A[i]));
    }
    chmin(ans, sum(cost)+abs(A[0]-B[0]));
    // (1,N) + 2つバラバラ
    cost.assign(2, INF);
    rep(i, N) {
        chmin(cost[0], abs(A[N-1]-B[i]));
        chmin(cost[1], abs(B[0]-A[i]));
    }
    chmin(ans, sum(cost)+abs(A[0]-B[N-1]));
    // (N,1) + 2つバラバラ
    cost.assign(2, INF);
    rep(i, N) {
        chmin(cost[0], abs(A[0]-B[i]));
        chmin(cost[1], abs(B[N-1]-A[i]));
    }
    chmin(ans, sum(cost)+abs(A[N-1]-B[0]));
    // (N,N) + 2つバラバラ
    cost.assign(2, INF);
    rep(i, N) {
        chmin(cost[0], abs(A[0]-B[i]));
        chmin(cost[1], abs(B[0]-A[i]));
    }
    chmin(ans, sum(cost)+abs(A[N-1]-B[N-1]));
    // (1,1) + (N,N)
    chmin(ans, abs(A[0]-B[0])+abs(A[N-1]-B[N-1]));
    // (1,N) + (N,1)
    chmin(ans, abs(A[0]-B[N-1])+abs(A[N-1]-B[0]));

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
