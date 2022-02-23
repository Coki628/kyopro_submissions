/*
・自力AC！
・累積和、前計算
・悩んだ。2乗が効くのでその前提で考える。
　kを固定すると、当然連続したk個に+Xしたい。この連続した区間を全探索、
　でも左右にもっと伸ばした方がいい場合もある。そこまで全部見ると3乗なのでどうにかする。
　左,右端を固定した時の累積和の最大値が知りたい。これは2乗が効くなら前計算できるので、
　L[i] := 左端がiの時の累積和の最大値、みたいのをやる。
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
    ll N, X;
    cin >> N >> X;
    auto A = LIST(N);

    Accumulate<ll> acc(A);
    vector<ll> L(N+1), R(N+1);
    ll mx = 0;
    rep(i, N) {
        rep(j, i+1, N+1) {
            chmax(mx, acc.query(i, j));
            chmax(L[i], acc.query(i, j));
            chmax(R[j], acc.query(i, j));
        }
    }
    vector<ll> ans = {mx};
    rep(k, 1, N+1) {
        rep(i, N-k+1) {
            chmax(mx, acc.query(i, i+k)+X*k+R[i]+L[i+k]);
        }
        ans.eb(mx);
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
