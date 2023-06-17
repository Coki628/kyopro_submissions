/*
・終了後自力AC。。悔しい。
・主客転倒、座圧BIT
・自身より小さい値の数だけ自分のindexが後ろに行く。
　これを数えるために座圧BITに値を入れていく。
　すると他の集合との比較分はまとめて数えられる。
　自身と同じ集合にある分は、同じ集合内で自分より小さい値の数 * 他の集合の数
　でまとまる。1-indexedになる分も他の集合の数と掛けると後から調整できる。
・これは落ち着いて考えれば時間内いけてもよかったよなぁ。。
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
    ll N, M;
    cin >> N >> M;
    Compress<ll> cp;
    auto A = listnd(N, M, 0LL);
    rep(i, N) {
        cin >> A[i];
        sort(ALL(A[i]));
        rep(j, M) {
            cp.add(A[i][j]);
        }
    }
    cp.build();
    ll L = cp.size();
    rep(i, N) {
        rep(j, M) {
            A[i][j] = cp[A[i][j]];
        }
    }

    ll ans = 0;
    BIT<ll> bit(L);
    rep(i, N - 1, -1, -1) {
        rep(j, M) {
            // 他の集合との比較分 + 同じ集合内で自分より小さい値の数 * 他の集合の数
            ans += bit.query(0, A[i][j]) + j * (N - i - 1);
        }
        rep(j, M) {
            bit.add(A[i][j], 1);
        }
        // 1-indexed補正
        // 集合iの要素数 * 他の集合の数
        ans += M * (N - i - 1);
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
