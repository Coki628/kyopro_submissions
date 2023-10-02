/*
参考：https://atcoder.jp/contests/abc322/editorial/7303
・遅延セグ木、区間01反転・区間01最大連長取得
・公式解の方針に寄せた。両端から続く長さもそれぞれ01両方持っておく。
　この方が場合分けも簡潔だし、フリップ処理もやることが分かりやすいね。
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

#include "datastructure/LazySegmentTree.hpp"

// 区間01反転・区間01最大連長取得
struct Node {
    ll mx0, mx1, llen0, llen1, rlen0, rlen1, sz;
    operator ll() const {
        return mx1;
    }
};
auto f = [](Node a, Node b) -> Node {
    Node res;
    res.llen0 = a.llen0;
    res.llen1 = a.llen1;
    res.rlen0 = b.rlen0;
    res.rlen1 = b.rlen1;
    res.sz = a.sz + b.sz;
    res.mx0 = max({a.mx0, b.mx0, a.rlen0 + b.llen0});
    res.mx1 = max({a.mx1, b.mx1, a.rlen1 + b.llen1});
    if (a.rlen0 == a.sz) {
        res.llen0 = a.sz + b.llen0;
    }
    if (a.rlen1 == a.sz) {
        res.llen1 = a.sz + b.llen1;
    }
    if (b.llen0 == b.sz) {
        res.rlen0 = a.rlen0 + b.sz;
    }
    if (b.llen1 == b.sz) {
        res.rlen1 = a.rlen1 + b.sz;
    }
    return res;
};
auto g = [](Node a, bool b) -> Node {
    // 偶数回反転したらそのまま
    if (!b) {
        return a;
    } else {
        // 0と1の関係が入れ替わる
        return {a.mx1, a.mx0, a.llen1, a.llen0, a.rlen1, a.rlen0, a.sz};
    }
};
auto h = [](bool a, bool b) -> bool { return a ^ b; };
const Node T = {0, 0, 0, 0, 0, 0, 1};
const bool E = false;

void solve() {
    ll N, Q;
    cin >> N >> Q;
    string S;
    cin >> S;

    auto seg = get_lazy_segment_tree(N, f, g, h, T, E);
    rep(i, N) {
        if (S[i] == '0') {
            seg.set(i, {1, 0, 1, 0, 1, 0, 1});
        } else {
            seg.set(i, {0, 1, 0, 1, 0, 1, 1});
        }
    }
    seg.build();

    rep(_, Q) {
        ll op, l, r;
        cin >> op >> l >> r;
        l--;
        if (op == 1) {
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
