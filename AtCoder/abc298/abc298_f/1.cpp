/*
・きっちり自力AC！
・座圧、平面走査
・列の状態をセグ木で持って、1行ずつ見る。
　その行の分を除いて「セグ木の全体max+その行の総和」終わったら状態戻す。
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
    Compress<ll> cph, cpw;
    vector<array<ll, 3>> RCX;
    rep(i, N) {
        ll r, c, x;
        cin >> r >> c >> x;
        RCX.pb({r, c, x});
        cph.add(r);
        cpw.add(c);
    }
    cph.build();
    cpw.build();
    rep(i, N) {
        auto [r, c, x] = RCX[i];
        RCX[i] = {cph[r], cpw[c], x};
    }

    ll H = cph.size();
    ll W = cpw.size();
    vector<ll> rowsm(H);
    auto seg = get_segment_tree(
        vector<ll>(W, 0LL), [](ll a, ll b) { return max(a, b); }, -INF
    );
    vv<pll> adj(H);
    for (auto [r, c, x] : RCX) {
        rowsm[r] += x;
        adj[r].eb(c, x);
        seg.update(c, seg[c] + x);
    }

    ll ans = -INF;
    rep(h, H) {
        for (auto [c, x] : adj[h]) {
            seg.update(c, seg[c] - x);
        }
        chmax(ans, seg.all() + rowsm[h]);
        for (auto [c, x] : adj[h]) {
            seg.update(c, seg[c] + x);
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
