/*
参考：TLでDPって聞いた。
・ぱっと思った貪欲に固執して、取り返せないくらい時間が経った後で
　制約N<=500に気付いた所でもう負け確だった。
・dp[i][j][k] := i番目まで見て、j個使って、最後に使った位置がkの時の最小値
　を普通にやったらMLEしたから、MLE対策で1次元目省略したら通った。
　DP方針の意識で考えたら割と素直に出てきたやつで合ってた。これはもったいなかったなー…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

ll dp[507][507], nxt[507][507];

void solve() {
    ll N, L, K;
    cin >> N >> L >> K;
    auto D = LIST(N);
    auto A = LIST(N);

    D.eb(L);
    vector<ll> B(N);
    rep(i, N) {
        B[i] = D[i+1]-D[i];
    }

    // auto dp = list3d(N+1, K+1, N, INF);
    rep(j, K+1) {
        rep(k, N) {
            dp[j][k] = INF;
            nxt[j][k] = INF;
        }
    }
    dp[0][0] = 0;
    rep(i, N) {
        rep(j, K+1) {
            rep(k, i+1) {
                chmin(nxt[j][i], dp[j][k]+A[i]*B[i]);
                if (j+1 <= K) chmin(nxt[j+1][k], dp[j][k]+A[k]*B[i]);
                dp[j][k] = INF;
            }
        }
        swap(dp, nxt);
    }
    ll ans = INF;
    rep(j, K+1) {
        rep(k, N) {
            chmin(ans, dp[j][k]);
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
