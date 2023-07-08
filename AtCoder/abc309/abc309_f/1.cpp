/*
・終了後自力AC。時間内に正解の方針生えなかった。。
・h<=w<=dとしておいて、hについてソート、wについてセグ木の添字、
　dについてセグ木の値みたいにすれば、自身より大きい所の最大値みたいにして最適を取れる。
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
    vector<array<ll, 3>> boxes;
    Compress<ll> cph, cpw;
    rep(i, N) {
        ll h, w, d;
        cin >> h >> w >> d;
        boxes.pb({h, w, d});
        sort(ALL(boxes[i]));
        cph.add(boxes[i][0]);
        cpw.add(boxes[i][1]);
    }
    cph.build();
    cpw.build();
    ll H = cph.size();
    ll W = cpw.size();

    vvl adj(H);
    rep(i, N) {
        auto &[h, w, d] = boxes[i];
        adj[cph[h]].eb(i);
        w = cpw[w];
    }
    auto seg = get_segment_tree(W, [](ll a, ll b) { return max(a, b); }, -INF);
    rep(i, H - 1, -1, -1) {
        for (auto j : adj[i]) {
            auto [h, w, d] = boxes[j];
            ll mxd = seg.query(w + 1, W);
            if (mxd > d) {
                Yes();
                return;
            }
        }
        for (auto j : adj[i]) {
            auto [h, w, d] = boxes[j];
            seg.update(w, max(seg[w], d));
        }
    }
    No();
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
