/*
・きっちり自力AC！
・真ん中固定。MとXはBITに詰めておいて3*3全探索。
　mexは数字が3種類しかないので適当に愚直に求めた。
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
    string S;
    cin >> S;

    ll M = 3;
    vector<BIT<ll>> bit1(M, BIT<ll>{N}), bit2(M, BIT<ll>{N});
    rep(i, N) {
        if (S[i] == 'M') {
            bit1[A[i]].add(i, 1);
        }
        if (S[i] == 'X') {
            bit2[A[i]].add(i, 1);
        }
    }
    ll ans = 0;
    rep(i, 1, N - 1) {
        if (S[i] != 'E') continue;
        rep(j, M) {
            rep(k, M) {
                vector<ll> used(M + 1);
                used[A[i]] = 1;
                used[j] = 1;
                used[k] = 1;
                ll mex = INF;
                rep(x, M + 1) {
                    if (not used[x]) {
                        mex = x;
                        break;
                    }
                }
                assert(mex != INF);
                ll cnt = bit1[j].query(0, i) * bit2[k].query(i + 1, N);
                ans += mex * cnt;
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
