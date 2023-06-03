/*
・きっちり自力AC！
・平面走査っぽくやったけど、mapに詰めて集計だけで行けたっぽい。。
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
    ll W, H;
    cin >> W >> H;
    ll N;
    cin >> N;
    vector<pll> P;
    rep(i, N) {
        ll p, q;
        cin >> p >> q;
        P.eb(p, q);
    }
    ll M1, M2;
    cin >> M1;
    vector<ll> A(M1);
    cin >> A;
    cin >> M2;
    vector<ll> B(M2);
    cin >> B;

    A.pb(INF);
    B.pb(INF);
    M1++, M2++;
    vvl adj(M1);
    rep(i, N) {
        auto [p, q] = P[i];
        ll j = bisect_left(A, p);
        ll k = bisect_left(B, q);
        adj[j].eb(k);
    }

    ll mn = INF, mx = -INF;
    auto segmn = get_segment_tree(
        vector<ll>(M2), [](ll a, ll b) { return min(a, b); }, INF
    );
    auto segmx = get_segment_tree(
        vector<ll>(M2), [](ll a, ll b) { return max(a, b); }, -INF
    );
    rep(i, M1) {
        for (auto k : adj[i]) {
            segmn.update(k, segmn[k] + 1);
            segmx.update(k, segmx[k] + 1);
        }
        chmin(mn, segmn.all());
        chmax(mx, segmx.all());
        for (auto k : adj[i]) {
            segmn.update(k, segmn[k] - 1);
            segmx.update(k, segmx[k] - 1);
        }
    }
    print(mkp(mn, mx));
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
