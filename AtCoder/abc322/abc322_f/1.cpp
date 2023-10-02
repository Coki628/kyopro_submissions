/*
・これは(だいたい)自力WA。
・方針は悪くなかったようなので時間外で色々考えたけど、
　結局乗せるもんがいい感じに整わず。
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
    ll mx0, mx1, lval, rval, llen, rlen;
    operator ll() const {
        return mx1;
    }
};
auto f = [](Node a, Node b) -> Node {
    Node res;
    res.lval = a.lval;
    res.llen = a.llen;
    res.rval = b.rval;
    res.rlen = b.rlen;
    if (a.rval == 1 and b.lval == 1) {
        res.mx1 = max({a.mx1, b.mx1, a.rlen + b.llen});
        res.mx0 = max(a.mx0, b.mx0);
        if (b.rlen == b.mx1) {
            res.rlen = a.rlen + b.rlen;
        }
        if (a.llen == a.mx1) {
            res.llen = a.llen + b.llen;
        }
    } else if (a.rval == 0 and b.lval == 0) {
        res.mx0 = max({a.mx0, b.mx0, a.rlen + b.llen});
        res.mx1 = max(a.mx1, b.mx1);
        if (b.rlen == b.mx0) {
            res.rlen = a.rlen + b.rlen;
        }
        if (a.llen == a.mx0) {
            res.llen = a.llen + b.llen;
        }
    } else {
        res.mx0 = max(a.mx0, b.mx0);
        res.mx1 = max(a.mx1, b.mx1);
    }
    return res;
};
auto g = [](Node a, bool b) -> Node {
    // 偶数回反転したらそのまま
    if (!b) {
        return a;
    } else {
        // 0と1の関係が入れ替わる
        return {a.mx1, a.mx0, 1 - a.lval, 1 - a.rval, a.llen, a.rlen};
    }
};
auto h = [](bool a, bool b) -> bool { return a ^ b; };
const Node T = {0, 0, -1, -1, 1, 1};
const bool E = false;

void solve() {
    ll N, Q;
    cin >> N >> Q;
    string S;
    cin >> S;

    auto seg = get_lazy_segment_tree(N, f, g, h, T, E);
    rep(i, N) {
        if (S[i] == '0') {
            seg.set(i, {1, 0, 0, 0, 1, 1});
        } else {
            seg.set(i, {0, 1, 1, 1, 1, 1});
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
