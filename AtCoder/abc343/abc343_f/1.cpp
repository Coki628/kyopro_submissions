/*
・きっちり自力AC！
・クエリ系、1点更新、2番目に大きい値の個数、セグ木
・セグ木に乗せる。1,2番目に大きい値とその個数を持てばいいが、
　変数4つくらいのモノイド作ると場合分け地獄がつらそう、、と言うことで、
　mapで管理して適当に楽することにした。多分大丈夫だとは思ったけど、
　計算量がきつくないかどうかは祈る部分もあった。無事通って良かった。
・ちなみに、mapが全部llだと0.85秒、intにしたら0.69秒で結構速くなった。
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

void solve() {
    ll N, Q;
    cin >> N >> Q;
    vector<ll> A(N);
    cin >> A;

    auto f = [](const map<int, int> &a, const map<int, int> &b) {
        map<int, int> res;
        for (auto [k, v] : a) {
            res[k] += v;
        }
        for (auto [k, v] : b) {
            res[k] += v;
        }
        while (res.size() > 2) {
            res.erase(res.begin());
        }
        return res;
    };
    auto seg = get_segment_tree(N, f, map<int, int>());
    rep(i, N) {
        seg.set(i, {{A[i], 1}});
    }
    seg.build();
    rep(_, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll p, x;
            cin >> p >> x;
            p--;
            A[p] = x;
            seg.update(p, {{A[p], 1}});
        } else {
            ll l, r;
            cin >> l >> r;
            l--;
            auto C = seg.query(l, r);
            if(C.size() < 2) {
                print(0);
            } else {
                auto [k, v] = *prev(C.end(), 2);
                print(v);
            }
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
