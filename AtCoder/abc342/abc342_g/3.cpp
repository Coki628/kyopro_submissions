/*
参考：https://atcoder.jp/contests/abc342/submissions/50580301
　　　https://atcoder.jp/contests/abc342/submissions/50480272
　　　https://ikatakos.com/pot/programming_algorithm/data_structure/segment_tree
ライブラリ整備：双対セグ木
・クエリ系、区間chmax・1点取得・履歴削除、双対セグ木
・区間chmaxで更新に使った値を全てmultisetで覚えておく。
　こんな重いもん乗せて大丈夫なのかと思うけど、うまくやると大丈夫。
・さて、基本的にはTLEになった遅延セグ木とだいたい同じことを双対セグ木でやるでいい。
　今まで遅延セグ木で困ったこと無かったので、初めて使った。
　やはり各ノードにmultisetを乗せるのは重いのだが、
　無駄な再生成を極力避けることで、間に合うようになってる。
　具体的には、関数hのf1を参照じゃなくて実体にしたり、
　戻り値にmoveを使わなかったりすると、TLEになる。
　遅延セグ木だとここをいくら工夫しても、関数gで要素にマージする時に、
　要素側のmultisetを毎回生成しまくるからダメなんだと思う。
　こっちみたいに要素に持たせるのを単一の値にできればいいんだけど、
　遅延セグ木は適用させた作用素は消えちゃうから、
　どうしても要素側にも何が削除されたかとかの情報を持たなきゃいけない。
　双対セグ木は作用素を何も伝搬させないで、
　1点取得の時に都度取りに行くみたいなイメージなので、
　結果的に要素側には履歴情報は持たせなくてよくなってる。
・ちなみにmultisetに持たせる型をllからintにしたらかなり速くなった。2.63秒→1.78秒。
・今回負数は使わないので、負数を削除の目印としてmultisetを1本にした。
　意外とこれは速くならず、1.83秒。
　結局1本が持ってる要素数は2本の時の合計と変わらないからだろうか。
　なんとなくsetとかmapって持ってる要素数が増えると結構遅くなるイメージあるし。
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

#include "datastructure/DualSegmentTree.hpp"

auto g = [](ll val, const multiset<int> &func) -> ll {
    if (func.size()) {
        chmax(val, (ll)*--func.end());
    }
    return val;
};
auto h = [](multiset<int> &f1, const multiset<int> &f2) -> multiset<int> {
    for (auto &a : f2) {
        if (a < 0) {
            auto itr = f1.find(-a);
            assert(itr != f1.end());
            f1.erase(itr);
        } else {
            f1.insert(a);
        }
    }
    return move(f1);
};
const ll T = -INF;
const multiset<int> E;

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    auto seg = get_dual_segment_tree(A, g, h, T, E);
    ll Q;
    cin >> Q;
    vector<array<ll, 3>> qs(Q);
    rep(i, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll l, r, x;
            cin >> l >> r >> x;
            l--;
            multiset<int> func;
            func.insert(x);
            seg.update(l, r, func);
            qs[i] = {l, r, x};
        } else if (op == 2) {
            ll j;
            cin >> j;
            j--;
            auto [l, r, x] = qs[j];
            multiset<int> func;
            func.insert(-x);
            seg.update(l, r, func);
        } else {
            ll j;
            cin >> j;
            j--;
            auto res = (ll)seg[j];
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
