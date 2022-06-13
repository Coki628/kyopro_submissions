/*
参考：https://twitter.com/americaotogamer/status/1535622849729159169
・ほぼ自力AC！TLからキーワード得ていたけど、これはノーヒントでもいけたんじゃないか。
・座圧、遅延セグ木、区間加算・区間更新・区間和取得、クエリ先読み
・値の増え方は規則的なので、座圧でまとめることを考える。
　これは区間和取得モノイドのszで1の代わりに座圧後の1要素の重みを初期値として設定するやつでいける。
　今回はここに座圧の重みだけでなく、その区間の等差数列の和みたいなやつを使う。
　あと値の増え方の都合上、区間は1-indexedのまま持つと都合がいい。
　クエリ先読みして適切にこれらを準備しておけば、
　後は、区間全体に+日数する、クエリ区間の和を取得、クエリ区間の値を0に更新、
　の3つの操作ができればOK。
　これは区間加算・区間更新・区間和取得ができる要素と作用素が既に用意してある。
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

#include "numbers/arithmetic_sequence_sum.hpp"
#include "segment/LazySegmentTree.hpp"

// 区間加算・区間更新・区間和取得
struct Node {
    mint val, sz;
    operator mint() const { return val; }
};
struct Func {
    mint add, assign;
    bool update;
    bool operator==(const Func &f) const {
        return add == f.add and assign == f.assign and update == f.update;
    }
};
auto f = [](Node a, Node b) -> Node { return { a.val+b.val, a.sz+b.sz }; };
auto g = [](Node a, Func b) -> Node {
    if (b.update) {
        return { a.sz*(b.add+b.assign), a.sz };
    } else {
        return { a.val+a.sz*b.add, a.sz };
    }
};
auto h = [](Func a, Func b) -> Func {
    if (b.update) {
        a.update = true;
        a.add = 0;
        a.assign = b.add+b.assign;
    } else {
        a.add += b.add;
    }
    return a;
};
const Node T = {0, 0};
const Func E = {0, 0, 0};

void solve() {
    ll N, Q;
    cin >> N >> Q;

    ll prv = 0;
    vector<array<ll, 3>> qs;
    vector<ll> tmp = {0, N+1};
    rep(i, Q) {
        ll d, l, r;
        cin >> d >> l >> r;
        r++;
        tmp.eb(l);
        tmp.eb(r);
        ll diff = d - prv;
        qs.pb({diff, l, r});
        prv = d;
    }
    Compress<ll> cp(tmp);
    ll M = cp.size();
    rep(i, Q) {
        qs[i][1] = cp.zip(qs[i][1]);
        qs[i][2] = cp.zip(qs[i][2]);
    }

    auto seg = get_lazy_segment_tree(M-1, f, g, h, T, E);
    rep(i, M-1) {
        seg.set(i, {0, arithmetic_sequence_sum<mint>(cp.unzip(i), 1, cp.unzip(i+1)-cp.unzip(i))});
    }
    seg.build();
    for (auto [d, l, r] : qs) {
        seg.update(0, M-1, {d, 0, false});
        mint res = seg.query(l, r);
        print(res);
        seg.update(l, r, {0, 0, true});
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
