/*
・実験
・順列全探索の中でビット全探索もしてるので、大きいのは調べられない。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
    // auto A = LIST(N);
    // auto B = LIST(N);

    vector<ll> P(N);
    iota(ALL(P), 1);
    for (auto& perma : permutations(P)) {
        for (auto& permb : permutations(P)) {
            ll mx = 0;
            vector<ll> mxa, mxb;
            rep(bit, 1LL<<N) {
                ll j = 0;
                bool ok = true;
                vector<ll> cura, curb;
                rep(i, N) {
                    if (bit>>i & 1) {
                        cura.eb(perma[i]);
                        while (j < N and permb[j]%perma[i]) j++;
                        if (j < N) curb.eb(permb[j]);
                        j++;
                    }
                    if (j > N) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    if (chmax(mx, (ll)popcount(bit))) {
                        mxa = cura;
                        mxb = curb;
                    }
                }
            }
            debug(perma);
            debug(permb);
            debug(mx);
            debug(mxa);
            debug(mxb);
        }
    }
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
