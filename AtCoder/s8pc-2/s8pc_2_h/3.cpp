/*
・dojo set_d_5_4
・きっちり自力AC！
・遅延セグ木、区間01反転・区間和取得
・これもまあ何回かやって覚えてたしなぁ。。
　indexed入力そのままでいいのが逆に最初答え合わなくて悩んだ。ｗ
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

#include "segment/LazySegmentTree.hpp"

// 区間01反転・区間和取得
struct Node {
    ll cnt0, cnt1;
    operator ll() const { return cnt1; }
};
auto f = [](Node a, Node b) -> Node {
    a.cnt0 += b.cnt0;
    a.cnt1 += b.cnt1;
    return a;
};
auto g = [](Node a, bool b) -> Node {
    // 偶数回反転したらそのまま
    if (!b) {
        return a;
    } else {
        // 0と1の数が入れ替わる
        return {a.cnt1, a.cnt0};
    }
};
auto h = [](bool a, bool b) -> bool { return a^b; };
// { 区間内の0の個数, 区間内の1の個数 }
const Node T = {0, 0};
const bool E = false;

void solve() {
    ll N, Q;
    cin >> N >> Q;

    auto seg = get_lazy_segment_tree(f, g, h, T, E);
    seg.build(vector<Node>(N, {1, 0}));
    rep(i, Q) {
        ll t, l, r;
        cin >> t >> l >> r;
        if (t == 1) {
            seg.update(l, r, 1);
        } else {
            ll res = seg.query(l, r);
            print(res);
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
