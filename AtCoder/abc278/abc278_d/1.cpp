/*
・きっちり自力AC！
・遅延セグ木、区間加算・区間更新
・更新と加算が両方出るので、それ用のモノイドを召喚したものの、
　後から言われたら1点更新なので普通に区間更新やるだけの遅延セグ木でよかった…。
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

#include "datastructure/LazySegmentTree.hpp"

// 区間加算・区間更新・区間最大値取得
struct Func {
    ll add, assign;
    bool update;
    bool operator==(const Func &f) const {
        return add == f.add and assign == f.assign and update == f.update;
    }
};
auto f = [](ll a, ll b) -> ll { return max(a, b); };
auto g = [](ll a, Func b) -> ll {
    if (b.update) {
        return b.add+b.assign;
    } else {
        return a+b.add;
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
const ll T = 0;
const Func E = {0, 0, 0};

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    auto seg = get_lazy_segment_tree(A, f, g, h, T, E);
    ll Q;
    cin >> Q;
    rep(_, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll x;
            cin >> x;
            seg.update(0, N, {0, x, true});
        } elif (op == 2) {
            ll i, x;
            cin >> i >> x;
            i--;
            seg.update(i, {x, 0, false});
        } elif (op == 3) {
            ll i;
            cin >> i;
            i--;
            ll res = seg[i];
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
