/*
・この元々書いて方も、[1,N)の所だけ直して投げたら通った…。
　最初からこれで通ってれば40分近く多く時間が残ってWAも0なので、
　まじでもったいないケアレスミスからの致命傷だったな。。
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
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    vvpli fact(N);
    ll mn2 = INF, mn3 = INF;
    rep(i, N) {
        fact[i] = factorize(A[i]);
        ll cur2 = 0, cur3 = 0;
        for (auto [k, v] : fact[i]) {
            if (k == 2) {
                cur2 = v;
            } elif (k == 3) {
                cur3 = v;
            }
        }
        chmin(mn2, cur2);
        chmin(mn3, cur3);
    }
    map<ll, ll> C;
    for (auto [k, v] : fact[0]) {
        if (k == 2 or k == 3) {
            continue;
        }
        C[k] = v;
    }
    ll ans = 0;
    rep(i, N) {
        for (auto [k, v] : fact[i]) {
            if (k == 2) {
                ans += v - mn2;
            } elif (k == 3) {
                ans += v - mn3;
            } else {
                if (C[k] != v) {
                    print(-1);
                    return;
                }
            }
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
