/*
・LISをセグ木で。平面走査っぽくやる。
　LISはにぶたんベースを先に覚えたけど、こっちのが理屈は理解できる。
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
    ll M = 500000;
    vvl adj(M + 1);
    rep(i, N) {
        ll x, y;
        cin >> x >> y;
        adj[y].eb(x);
    }

    // seg[x] := 最後にxを使った時の最大個数
    auto seg = get_segment_tree(vector<ll>(M + 1, 0), [](ll a, ll b) { return max(a, b); }, -INF);
    rep(y, M, 0, -1) {
        // 更新後の値を遷移で使わないように昇順ソートにしておく
        sort(ALL(adj[y]));
        for (auto x : adj[y]) {
            seg.update(x, max(seg.query(x + 1, M + 1) + 1, seg[x]));
        }
    }
    ll ans = seg.all();
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
