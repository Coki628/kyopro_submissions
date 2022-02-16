/*
・dojo set_e_3_4
・自力AC！いい感じ。
・遅延セグ木、区間和取得を応用
・ちょっと悩んだけど、自力でちゃんと通せてよかった。
　arc115_eで座圧した時みたいな感じで、要素を重み付けしておく。
　今回はこれが10冪での重み付けになる。
・ちょっともたついたのが、初期化の時に値の方は、既に重みを適用済の値を入れないとだね。
　そこを1にしてて、合わない何でだー、ってなってた。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

#include "../../../_lib/cpp/_src/segment/LazySegmentTree.hpp"

// 区間更新・区間和取得
struct Node {
    mint val, sz;
    operator mint() const { return val; }
};
auto f = [](Node a, Node b) -> Node { return { a.val+b.val, a.sz+b.sz }; };
auto g = [](Node a, ll b) -> Node { return { a.sz*b, a.sz }; };
auto h = [](ll a, ll b) -> ll { return b; };
const Node T = {0, 0};
// 要素が取りうる範囲外の値にする
const ll E = INF;

void solve() {
    ll N, Q;
    cin >> N >> Q;

    auto seg = get_lazy_segment_tree(f, g, h, T, E);
    vector<Node> nodes(N);
    rep(i, N) {
        nodes[i] = {pow(10, N-i-1, MOD), pow(10, N-i-1, MOD)};
    }
    seg.build(nodes);
    rep(i, Q) {
        ll l, r, d;
        cin >> l >> r >> d;
        l--;
        seg.update(l, r, d);
        mint res = seg.query(0, N);
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
