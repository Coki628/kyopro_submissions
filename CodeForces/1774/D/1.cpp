/*
・きっちり自力AC！
・実装、BITにぶたん
・1が多い行から少ない行に移す。行毎にBIT生やして愚直シミュ頑張ったら通った。
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
    auto mat = listnd(N, M, 0);
    cin >> mat;

    ll cnt1 = 0;
    vector<BIT<ll>> bit(N, BIT<ll>{M});
    rep(i, N) {
        rep(j, M) {
            if (mat[i][j]) {
                cnt1++;
                bit[i].add(j, 1);
            }
        }
    }
    if (cnt1 % N != 0) {
        print(-1);
        return;
    }

    ll each = cnt1 / N;
    vector<ll> hi, lo;
    rep(i, N) {
        if (bit[i].query(0, M) > each) {
            hi.eb(i);
        } else if (bit[i].query(0, M) < each) {
            lo.eb(i);
        }
    }

    vector<tuple<ll, ll, ll>> ans;
    ll i = 0, j = 0;
    while (i < hi.size() and j < lo.size()) {
        auto &bithi = bit[hi[i]];
        auto &bitlo = bit[lo[j]];
        ll k = 0;
        while (1) {
            k = bithi.bisearch_fore(k, M - 1, 1);
            assert(k != -1);
            if (bitlo[k] == 0) {
                ans.eb(hi[i] + 1, lo[j] + 1, k + 1);
                bithi.add(k, -1);
                bitlo.add(k, 1);
                if (bithi.query(0, M) == each or bitlo.query(0, M) == each) {
                    break;
                }
            }
            k++;
        }
        if (bithi.query(0, M) == each) {
            i++;
        }
        if (bitlo.query(0, M) == each) {
            j++;
        }
    }
    print(ans.size());
    print(ans, '\n');
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
