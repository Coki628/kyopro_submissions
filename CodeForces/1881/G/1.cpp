/*
参考：https://www.youtube.com/watch?v=ng9OJM2J5yA
・自力ならず。方針は悪くなかった。
・クエリ、連続部分列の回文判定、区間加算、遅延セグ木
・この回文判定は、長さ2の隣接と長さ3の両端だけチェックすればいい。
　これに気付けたのは良かった。で、遅延セグ木に両端2要素だけ持たせる方針も良かった。
　でも単位元を演算の対象に含めてしまっていたり、
　長さ1なのに左から2番目とかを見てしまっていたりで、
　マージ時の判定とか処理の詰めが色々甘かった。
　なお、この変則的な取得時のマージに対して、
　更新操作側で区間加算が普通に機能するのか心配だったけど、
　そこは問題なく動いた。
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
using mint = ModInt<26>;
#include "template.hpp"

#include "datastructure/LazySegmentTree.hpp"

// 区間加算、区間回文存在判定取得(両端から1,2番目の値を持つ)
struct Node {
    // 区間長, 回文があるか
    ll sz, has;
    // 左端から1,2番目の値、右端から1,2番目の値
    mint l0, l1, r0, r1;
    operator ll() const {
        return has;
    }
};
auto f = [](Node a, Node b) -> Node {
    // 単位元は演算に関与させない
    if (a.sz == 0) return b;
    if (b.sz == 0) return a;
    assert(a.sz >= 1 and b.sz >= 1);

    Node res;
    res.sz = a.sz + b.sz;
    res.l0 = a.l0;
    res.r0 = b.r0;
    if (a.sz == 1 and b.sz == 1) {
        res.l1 = b.l0;
        res.r1 = a.r0;
    } else if (a.sz == 1 and b.sz >= 2) {
        res.l1 = b.l0;
        res.r1 = b.r1;
    } else if (a.sz >= 2 and b.sz == 1) {
        res.l1 = a.l1;
        res.r1 = a.r0;
    } else {
        res.l1 = a.l1;
        res.r1 = b.r1;
    }
    // 判定はa,bの長さが足りてるかしっかりチェックする
    res.has = a.has || b.has;
    if (a.sz >= 1 and b.sz >= 1 and a.r0 == b.l0) {
        res.has = 1;
    }
    if (a.sz >= 2 and b.sz >= 1 and a.r1 == b.l0) {
        res.has = 1;
    }
    if (a.sz >= 1 and b.sz >= 2 and a.r0 == b.l1) {
        res.has = 1;
    }
    return res;
};
auto g = [](Node a, mint b) -> Node {
    if (a.sz == 0) {
        return a;
    } else if (a.sz == 1) {
        return {a.sz, a.has, a.l0 + b, a.l1, a.r0 + b, a.r1};
    } else {
        return {a.sz, a.has, a.l0 + b, a.l1 + b, a.r0 + b, a.r1 + b};
    }
};
auto h = [](mint a, mint b) -> mint { return a + b; };
const Node T = {0, 0, 0, 0, 0, 0};
const mint E = 0;

void solve() {
    ll N, M;
    cin >> N >> M;
    string S;
    cin >> S;
    vector<Node> A(N);
    rep(i, N) {
        A[i] = {1, false, S[i] - 'a', 0, S[i] - 'a', 0};
    }

    auto seg = get_lazy_segment_tree(A, f, g, h, T, E);
    rep(i, M) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll l, r, x;
            cin >> l >> r >> x;
            l--;
            seg.update(l, r, x);
        } else {
            ll l, r;
            cin >> l >> r;
            l--;
            ll has = seg.query(l, r);
            if (has) {
                NO();
            } else {
                YES();
            }
        }
    }
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
