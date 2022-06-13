/*
・遅延セグ木、区間更新・区間和取得
・こっちでもやってみた。これだと境界付近も気にしなくていいし、
　ほんとにやるだけっぽくできるね。
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

#include "segment/LazySegmentTree.hpp"

// 区間更新・区間和取得
struct Node {
    ll val, sz;
    operator ll() const { return val; }
};
auto f = [](Node a, Node b) -> Node { return { a.val+b.val, a.sz+b.sz }; };
auto g = [](Node a, ll b) -> Node { return { a.sz*b, a.sz }; };
auto h = [](ll a, ll b) -> ll { return b; };
const Node T = {0, 0};
// 要素が取りうる範囲外の値にする
const ll E = INF;

void solve() {
    ll N, Q, X;
    cin >> N >> Q >> X;
    X--;
    auto P = LIST(N);
    rep(i, N) P[i]--;

    ll xi = find(ALL(P), X) - P.begin();
    auto low = get_lazy_segment_tree(N, f, g, h, T, E);
    auto hi = get_lazy_segment_tree(N, f, g, h, T, E);
    rep(i, N) {
        low.set(i, {0, 1});
        hi.set(i, {0, 1});
        if (P[i] < X) {
            low.set(i, {1, 1});
        }
        if (P[i] > X) {
            hi.set(i, {1, 1});
        }
    }
    low.build();
    hi.build();
    rep(_, Q) {
        ll op, l, r;
        cin >> op >> l >> r;
        l--;

        bool hasx = l <= xi and xi < r;
        ll lowcnt = low.query(l, r);
        ll hicnt = hi.query(l, r);
        low.update(l, r, 0);
        hi.update(l, r, 0);
        if (op == 1) {
            ll i = l;
            ll j = l + lowcnt + hasx;
            low.update(i, i+lowcnt, 1);
            hi.update(j, j+hicnt, 1);
            if (hasx) {
                xi = j - 1;
            }
        } else {
            ll i = l;
            ll j = l + hicnt + hasx;
            hi.update(i, i+hicnt, 1);
            low.update(j, j+lowcnt, 1);
            if (hasx) {
                xi = j - 1;
            }
        }
    }
    ll ans = xi + 1;
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
