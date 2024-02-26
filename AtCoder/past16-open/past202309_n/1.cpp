/*
・きっちり自力AC！
・クエリ先読み座圧、遅延セグ木、区間乗算・一点更新・区間和取得
・K^iのi部分が、要素の出し入れによって変化してしまうので、それに対応する。
　これは、ある値が追加された時、それより大きい値はi+1するし、
　削除された時には、それより大きい値がi-1となる、と表せる。
　これは区間乗算ができれば対応可。値を入れる時には一点更新したい。
　都度、全体の和が欲しい。これは区間和。以上3つが可能な遅延セグ木を用意する。
　また、新しく値を追加する時には自身より小さい要素の個数を数えて
　K^iのiが何なのか確認する必要があるが、これはBITとかで別途数えておけばいい。
　値の取りうる範囲は広いので、操作を適切にやるために先読み座圧とかしておく。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

// 区間乗算・区間更新・区間和取得
struct Func {
    mint mul, assign;
    bool update;
    bool operator==(const Func &f) const {
        return mul == f.mul and assign == f.assign and update == f.update;
    }
};
auto f = [](mint a, mint b) -> mint { return a + b; };
auto g = [](mint a, Func b) -> mint {
    if (b.update) {
        return b.mul * b.assign;
    } else {
        return a * b.mul;
    }
};
auto h = [](Func a, Func b) -> Func {
    if (b.update) {
        a.update = true;
        a.mul = 1;
        a.assign = b.mul * b.assign;
    } else {
        a.mul *= b.mul;
    }
    return a;
};
const mint T = 0;
const Func E = {1, 0, 0};

void solve() {
    ll Q, K;
    cin >> Q >> K;

    Compress<pll> cp;
    vector<tuple<char, ll, ll>> qs;
    map<ll, vector<ll>> adj;
    rep(i, Q) {
        char op;
        ll x;
        cin >> op >> x;
        if (op == '+') {
            cp.add({x, i});
            adj[x].pb(i);
            qs.pb({op, x, i});
        } else {
            assert(adj[x].size());
            ll j = adj[x].back();
            adj[x].pop_back();
            qs.pb({op, x, j});
        }
    }

    cp.build();
    ll N = cp.size();
    auto seg = get_lazy_segment_tree(N, f, g, h, T, E);
    BIT<ll> bit(N);
    mint invk = (mint)1 / K;
    for (auto [op, x, i] : qs) {
        if (op == '+') {
            ll j = cp[{x, i}];
            ll cnt = bit.query(0, j);
            seg.update(j, {1, mint(K).pow(cnt) * x, true});
            bit.add(j, 1);
            seg.update(j + 1, N, {K, 0, false});
        } else {
            ll j = cp[{x, i}];
            seg.update(j, {1, 0, true});
            bit.add(j, -1);
            seg.update(j + 1, N, {invk, 0, false});
        }
        mint res = seg.all();
        print(res);
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
