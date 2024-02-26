/*
・なんとか自力AC！Eより手こずったけどなんとか通し切った。
・にぶたん、累積和
・食われるスライムを決めて左右ににぶたん、基本は区間和で、
　区間内の値が全部同値だった時だけ合体できない。
　同値がどこまで続くかを判定するためのnxt的な配列は準備しておく。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

void solve(int testcase) {
    ll N;
    cin >> N;
    auto A = LIST(N);

    vector<ll> nxtr(N, -1);
    ll j = -1;
    rep(i, N - 2, -1, -1) {
        if (A[i] != A[i + 1]) {
            j = i + 1;
        }
        nxtr[i] = j;
    }
    Accumulate<ll> acc(A);
    vector<ll> ans(N);
    auto is_all_same = [&](ll l, ll r) {
        ll len = r - l;
        return len >= 2 and (nxtr[l] == -1 or nxtr[l] >= r);
    };
    rep(i, N) {
        ll res = bisearch_min(0, N, [&](ll x) {
            ll l = max(i - x, 0LL);
            ll r = min(i + 1 + x, N);
            ll lcnt = acc.query(l, i);
            ll rcnt = acc.query(i + 1, r);
            if (is_all_same(l, i)) {
                lcnt = A[i - 1];
            }
            if (is_all_same(i + 1, r)) {
                rcnt = A[i + 1];
            }
            return max(lcnt, rcnt) > A[i];
        });
        if (res == N) res = -1;
        ans[i] = res;
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
    rep(t, T) solve(t);

    return 0;
}
