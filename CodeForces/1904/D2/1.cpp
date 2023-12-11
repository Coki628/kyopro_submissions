/*
・セグ木にぶたん
・D1が解けてしまえば、このD2はデータ構造頑張るだけなので問題ない。
　左右それぞれ直近の出現位置を覚えて、跨げない条件2つはセグ木で。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N), B(N);
    cin >> A >> B;

    rep(i, N) {
        if (A[i] > B[i]) {
            NO();
            return;
        }
    }
    auto sega = get_segment_tree(A, [](ll a, ll b) { return max(a, b); }, -INF);
    auto segb = get_segment_tree(B, [](ll a, ll b) { return min(a, b); }, INF);
    vector<ll> nxtl(N, -1), nxtr(N, -1);
    vector<ll> mp(N + 1, -1);
    rep(i, N) {
        if (mp[B[i]] != -1) {
            nxtl[i] = mp[B[i]];
        }
        mp[A[i]] = i;
    }
    mp.assign(N + 1, -1);
    rep(i, N - 1, -1, -1) {
        if (mp[B[i]] != -1) {
            nxtr[i] = mp[B[i]];
        }
        mp[A[i]] = i;
    }
    rep(i, N) {
        if (A[i] == B[i]) continue;
        bool ok = false;
        if (nxtr[i] != -1) {
            ll r1 = sega.find_first(i + 1, [&](ll a) { return a > B[i]; });
            ll r2 = segb.find_first(i + 1, [&](ll b) { return b < B[i]; });
            if (r1 == -1) r1 = N;
            if (r2 == -1) r2 = N;
            if (nxtr[i] < min(r1, r2)) {
                ok = true;
            }
        }
        if (nxtl[i] != -1) {
            ll l1 = sega.find_last(i, [&](ll a) { return a > B[i]; });
            ll l2 = segb.find_last(i, [&](ll b) { return b < B[i]; });
            if (nxtl[i] > max(l1, l2)) {
                ok = true;
            }
        }
        // rep(j, i + 1, N) {
        //     if (A[j] > B[i]) break;
        //     if (B[j] < B[i]) break;
        //     if (A[j] == B[i]) {
        //         ok = true;
        //         break;
        //     }
        // }
        // rep(j, i - 1, -1, -1) {
        //     if (A[j] > B[i]) break;
        //     if (B[j] < B[i]) break;
        //     if (A[j] == B[i]) {
        //         ok = true;
        //         break;
        //     }
        // }
        if (not ok) {
            NO();
            return;
        }
    }
    YES();
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
