/*
・自力AC！やったね。
・クエリ、区間ソート、遅延セグ木、区間更新・区間和取得
・区間ソートについては、前に文字列でBIT26本生やすクエリ問やった時(abc285_f)と似た考察が通用する。
　今回も値は11種しかないので、状況は似てる。
　遅延セグ木を11本生やして、区間内に11回に分けて順番に並べていく感じになる。
・ちなみに本番中はllだったものをintにして出しなおしたら、0.51→0.36秒に速度改善。
　その後QUFiumも試したが、そっちはほぼ変化なかった。
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

// 区間更新・区間和取得
struct Node {
    int val, sz;
    operator int() const { return val; }
};
auto f = [](Node a, Node b) -> Node { return { a.val + b.val, a.sz + b.sz }; };
auto g = [](Node a, int b) -> Node { return { a.sz * b, a.sz }; };
auto h = [](int a, int b) -> int { return b; };
const Node T = {0, 0};
// 要素が取りうる範囲外の値にする
const int E = MOD;

void solve() {
    int M = 10;
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    cin >> A;

    vector<LazySegmentTree<decltype(f), decltype(g), decltype(h), Node, int>> seg(
        M + 1,
        {vector<Node>(N, {0, 1}), f, g, h, T, E}
    );
    rep(i, N) {
        seg[A[i]].update(i, 1);
    }
    rep(_, Q) {
        int op, l, r;
        cin >> op >> l >> r;
        l--;
        if (op == 1) {
            vector<int> C(M + 1);
            rep(i, M + 1) {
                C[i] = seg[i].query(l, r);
                seg[i].update(l, r, 0);
            }
            int s = l;
            rep(i, M + 1) {
                int t = s + C[i];
                seg[i].update(s, t, 1);
                s = t;
            }
        } else if (op == 2) {
            vector<int> C(M + 1);
            rep(i, M + 1) {
                C[i] = seg[i].query(l, r);
                seg[i].update(l, r, 0);
            }
            int t = r;
            rep(i, M + 1) {
                int s = t - C[i];
                seg[i].update(s, t, 1);
                t = s;
            }
        } else {
            int res = 0;
            rep(i, 1, M + 1) {
                res += seg[i].query(l, r) * i;
            }
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
