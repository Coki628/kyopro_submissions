/*
・なんとか自力AC！
・二分探索、最大値の最小化
・最大値の最小化でにぶたん。答えを決め打つと使える区間の範囲が定まるから解ける。
　判定は最初尺取ろうとしてバグらせて累積和にぶたんになった。
　左端固定で1の条件を満たす最短の右端を取って、その区間が0の条件も満たせばOK、みたいな感じ。
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
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    string S;
    cin >> S;
    ll N = S.size();

    vector<ll> A(N);
    rep(i, N) {
        A[i] = S[i] - '0';
    }
    Accumulate<ll> acc0(N), acc1(N);
    rep(i, N) {
        if (A[i] == 0) {
            acc0.set(i, 1);
        } else {
            acc1.set(i, 1);
        }
    }
    acc0.build();
    acc1.build();

    ll total1 = count(ALL(A), 1);
    ll res = bisearch_min(-1, N, [&](ll x) {
        ll need1 = total1 - x;
        if (need1 <= 0) {
            return true;
        }
        rep(l, N) {
            ll r = acc1.bisearch_fore(l, N-1, need1);
            if (r == -1) {
                return false;
            }
            ll cnt0 = acc0.query(l, r);
            if (cnt0 <= x) {
                return true;
            }
        }
        return false;
    });
    print(res);
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
