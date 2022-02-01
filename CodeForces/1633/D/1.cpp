/*
・自力ならず。。これは悔しい。
・前計算、整数BFS、工夫してナップザック
・すげー悩んだけど、割り算を難しく考えなくても、
　整数BFSであり得る値のコストは全列挙できるのは分かった。
　でもそれでも操作回数Kが大きすぎてナップザックに乗らない。
　明らかにやりたいのはナップザックなのに。
・結局、列挙したコストは最大のものでも12くらいにしかならないらしく、
　これに最大のNである1000を掛けてもKの最大100万より全然小さい。
　ここを操作回数の上界にすれば1000*10000くらいのDPなので間に合う。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

vector<ll> cost(1007, -1);
ll MX = -1;

void prep() {
    queue<ll> que;
    que.push(1);
    cost[1] = 0;
    while (que.size()) {
        auto cur = que.front(); que.pop();
        rep(x, 1, cur+1) {
            ll nxt = cur+cur/x;
            if (nxt <= 1000 and cost[nxt] == -1) {
                cost[nxt] = cost[cur]+1;
                que.push(nxt);
            }
        }
    }
    MX = max(cost)*1000;
}

void solve() {
    ll N, K;
    cin >> N >> K;
    auto B = LIST(N);
    auto C = LIST(N);

    chmin(K, MX);
    auto dp = list2d(2, K+1, -INF);
    dp[0][0] = 0;
    rep(i, N) {
        rep(j, K+1) {
            chmax(dp[(i+1)%2][j], dp[i%2][j]);
            if (j+cost[B[i]] <= K) {
                chmax(dp[(i+1)%2][j+cost[B[i]]], dp[i%2][j]+C[i]);
            }
        }
    }
    ll ans = max(dp[N%2]);
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    prep();

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
