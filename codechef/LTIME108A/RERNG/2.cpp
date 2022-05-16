/*
・Mo's algorithm
・部分点2を狙ったけどset遅すぎTLE。。
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

#include "segment/Mo.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;
    auto A = LIST(N);
    rep(i, N) A[i]--;

    // assert(N <= 50000 and Q <= 50000);

    vector<ll> B(N, -1);
    rep(i, N-1) {
        B[A[i]] = A[i+1];
    }

    Mo mo(N);
    vector<ll> len(Q);
    rep(i, Q) {
        ll l, r;
        cin >> l >> r;
        l--;
        mo.add(l, r);
        len[i] = r - l;
    }

    set<ll> se;
    ll cnt = 0;
    auto add = [&](int i) -> void {
        se.insert(A[i]);
        auto itr = se.find(A[i]);
        if (itr != se.begin()) {
            ll prv = *prev(itr);
            if (B[prv] == A[i]) cnt++;
        }
        if (itr != --se.end()) {
            ll nxt = *next(itr);
            if (B[A[i]] == nxt) cnt++;
        }
        if (itr != se.begin() and itr != --se.end()) {
            ll prv = *prev(itr);
            ll nxt = *next(itr);
            if (B[prv] == nxt) cnt--;
        }
    };
    auto erase = [&](int i) -> void {
        auto itr = se.find(A[i]);
        if (itr != se.begin()) {
            ll prv = *prev(itr);
            if (B[prv] == A[i]) cnt--;
        }
        if (itr != --se.end()) {
            ll nxt = *next(itr);
            if (B[A[i]] == nxt) cnt--;
        }
        if (itr != se.begin() and itr != --se.end()) {
            ll prv = *prev(itr);
            ll nxt = *next(itr);
            if (B[prv] == nxt) cnt++;
        }
        se.erase(A[i]);
    };
    vector<ll> ans(Q);
    auto out = [&](int i) -> void {
        ans[i] = len[i] - cnt;
    };
    mo.build(add, erase, out);
    print(ans, '\n');
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
