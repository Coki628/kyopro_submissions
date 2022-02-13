/*
参考：https://twitter.com/butsurizuki/status/1492547397867937794
・自力ならず。。
・式変形、DP復元
・題意の操作を式変形すると、(Ai+Aj)^2 = Ai^2+2*AiAj+Aj^2 となり、
　Ai^2とAj^2はどんな入れ替えをやっても一定なので、結局AiAjの最小化のみが目標となり、
　これはA,Bでなるべく均等に割り振るのが正解。(ほんとか？まあでもみんな言ってたし多分そう。)
・で、もしそこに確証が持てなくても、制約的に和の割り振りをDPした後、
　到達可の全ての和に対して復元試して最小値見つける、でも大丈夫だった。
・式変形は自分では出せなかったけど、この和のパターン全部で復元やるのが
　間に合うのは気付くべきだったな…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
// #define MINT_TO_LL_CAST
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

    ll M = sum(A)+sum(B);
    // dp[i][j] := i番目まで見て、片方側の和がjの時の到達可否と、その時どちらを選んだか
    auto dp = list2d(N+1, M+1, mkp(false, -1));
    dp[0][0] = {true, -1};
    rep(i, N) {
        rep(j, M+1) {
            if (!dp[i][j].first) continue;
            if (!dp[i+1][j+A[i]].first) {
                dp[i+1][j+A[i]] = {true, 0};
            }
            if (!dp[i+1][j+B[i]].first) {
                dp[i+1][j+B[i]] = {true, 1};
            }
        }
    }
    ll ans = INF;
    rep(j, M+1) {
        if (dp[N][j].first) {
            vector<ll> cura, curb;
            ll i = N, sm = j;
            while (dp[i][sm].second != -1) {
                if (dp[i][sm].second == 0) {
                    cura.eb(A[i-1]);
                    curb.eb(B[i-1]);
                    sm -= A[i-1];
                } else {
                    cura.eb(B[i-1]);
                    curb.eb(A[i-1]);
                    sm -= B[i-1];
                }
                i--;
            }
            ll cnt = 0;
            rep(k, N) {
                rep(l, k+1, N) {
                    cnt += pow(cura[k]+cura[l], 2);
                    cnt += pow(curb[k]+curb[l], 2);
                }
            }
            chmin(ans, cnt);
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
