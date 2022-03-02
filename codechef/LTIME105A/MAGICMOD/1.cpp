/*
・これは1番最初に投げた貪欲。変える必要のある最初の要素で合わせて、
　以降それに合わないならNG、みたいにしてるけど、全然嘘。。
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
    auto A =  LIST(N);

    UNIQUE(A);
    if (A.size() < N) {
        NO();
        return;
    }

    set<ll> ok;
    vector<ll> rest, need;
    rep(i, N) {
        if (A[i] <= N) {
            ok.insert(A[i]);
        } else {
            rest.eb(A[i]);
        }
    }
    rep(a, 1, N+1) {
        if (not ok.count(a)) {
            need.eb(a);
        }
    }
    if (need.empty()) {
        YES();
        return;
    }
    ll mod = rest[0]-need[0];
    if (ok.size() and mod < *ok.rbegin()) {
        NO();
        return;
    }
    for (auto a : rest) {
        ok.insert(a%mod);
    }
    vector<ll> ans(ALL(ok)), expected(N);
    iota(ALL(expected), 1);
    if (ans == expected) {
        cout << "YES " << mod << '\n';
    } else {
        NO();
    }
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
