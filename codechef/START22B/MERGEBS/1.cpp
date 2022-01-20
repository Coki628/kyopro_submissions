/*
・自力AC！ここまでちゃんと通せたのは嬉しい。
・dp[i][j] := i番目まで決めて、Sを使った回数がjの時の最小転倒数 みたいなDP。
　Sの回数が決まればTの回数も分かるし、両方の回数が分かれば、
　その手前にある1の個数も累積和前計算とかで分かるから、今使うのが0だったら転倒数に足せばいい。
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

void solve() {
    ll N;
    cin >> N;
    string S, T;
    cin >> S >> T;

    vector<ll> A(N), B(N);
    rep(i, N) {
        if (S[i] == '1') {
            A[i] = 1;
        }
        if (T[i] == '1') {
            B[i] = 1;
        }
    }
    Accumulate<ll> acca(A), accb(B);

    auto dp = list2d(N*2+1, N+1, INF);
    dp[0][0] = 0;
    rep(i, N*2) {
        rep(j, min(i+1, N+1)) {
            ll k = i-j;
            if (k > N) continue;
            ll cnt1 = acca.query(0, j)+accb.query(0, k);
            if (j+1 <= N) {
                chmin(dp[i+1][j+1], dp[i][j]+(S[j] == '0' ? cnt1 : 0));
            }
            if (k+1 <= N) {
                chmin(dp[i+1][j], dp[i][j]+(T[k] == '0' ? cnt1 : 0));
            }
        }
    }
    ll ans = dp[N*2][N];
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
