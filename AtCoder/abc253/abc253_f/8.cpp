/*
参考：https://9cguide.appspot.com/15-05.html
・ライブラリ整備：永続遅延セグメント木
・メモリを試しに動的確保してみた。ポインタ変数の良い勉強になった。
　多分、大昔C言語で挫折したあたりの内容。
　今、周辺知識が身についた状態で考えたら、ちゃんと理解できて良かった。
・やっぱりこっちのがパフォーマンスは悪くて、速度で0.79秒、メモリ702MBくらい。
　とはいえ、ちゃんと想定通り動作してよかった。
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

// 参考：https://suisen-cp.github.io/cp-library-cpp/library/datastructure/segment_tree/persistent_lazy_segment_tree.hpp
template<typename F, typename G, typename H, typename Monoid, typename OperatorMonoid>
struct PersistentLazySegmentTree {

    int sz;
    const F f;
    const G g;
    const H h;
    const Monoid M1;
    const OperatorMonoid OM0;

    struct Node {
        // static inline ObjectPool<Node> _pool;
        // static Node *clone(Node *node) {
        //     return &(*_pool.alloc() = *node);
        // }

        static Node *clone(Node *node) {
            // ・Node1個分のメモリを確保：new Node()
            Node *res = new Node();
            // ・ポインタ変数resの値にnodeの値を入れる：*res = *node
            // ・値をもう一度ポインタに切り替えて返す：return &(xxx)
            return &(*res = *node);
        }

        Monoid data;
        OperatorMonoid lazy;
        Node *l, *r;

        // このコンストラクタがないとObjectPoolのメモリ確保が動かない
        Node() {}

        Node(const Monoid &data, const OperatorMonoid &lazy) : data(data), lazy(lazy), l(nullptr), r(nullptr) {}
    };

    PersistentLazySegmentTree(const F f, const G g, const H h,
                              const Monoid &M1, const OperatorMonoid OM0)
            : f(f), g(g), h(h), M1(M1), OM0(OM0) {}

    Node *build(const vector< Monoid > &v) {
        sz = (int) v.size();
        return build(0, (int) v.size(), v);
    }

    Node *merge(Node *l, Node *r) {
        Node *res = new Node(f(l->data, r->data), OM0);
        res->l = l;
        res->r = r;
        return res;
    }

    Node *build(int l, int r, const vector< Monoid > &v) {
        if(l + 1 >= r) return new Node(v[l], OM0);
        return merge(build(l, (l + r) >> 1, v), build((l + r) >> 1, r, v));
    }

    template <bool do_clone = true>
    auto push(Node *node) {
        Node *res = node;
        if constexpr (do_clone) res = Node::clone(res);
        res->l = update_all(res->l, res->lazy);
        res->r = update_all(res->r, res->lazy);
        res->lazy = OM0;
        if constexpr (do_clone) {
            return res;
        } else {
            return;
        }
    }

    Node *update_all(Node *node, const OperatorMonoid &x) {
        if (not node) return nullptr;
        Node *res = Node::clone(node);
        res->data = g(res->data, x);
        res->lazy = h(res->lazy, x);
        return res;
    }

    Node *update(int a, int b, const OperatorMonoid &x, Node *node, int l, int r) {
        if(r <= a || b <= l) {
            return node;
        } else if (a <= l && r <= b) {
            return update_all(node, x);
        } else {
            Node *res = push(node);
            res->l = update(a, b, x, res->l, l, (l + r) >> 1);
            res->r = update(a, b, x, res->r, (l + r) >> 1, r);
            res->data = f(res->l->data, res->r->data);
            return res;
        }
    }

    Node *update(Node *node, int a, int b, const OperatorMonoid &x) {
        return update(a, b, x, node, 0, sz);
    }

    Node *update(Node *node, int k, const OperatorMonoid &x) {
        return update(node, k, k+1, x);
    }

    Monoid query(int a, int b, Node *node, int l, int r, const OperatorMonoid &x) {
        if(r <= a || b <= l) {
            return M1;
        } else if(a <= l && r <= b) {
            return g(node->data, x);
        } else {
            OperatorMonoid y = h(x, node->lazy);
            return f(query(a, b, node->l, l, (l + r) >> 1, y),
                     query(a, b, node->r, (l + r) >> 1, r, y));
        }
    }

    Monoid query(Node* node, int a, int b) {
        return query(a, b, node, 0, sz, OM0);
    }

    Monoid all(Node* node) {
        return node ? node->data : M1;
    }

    Monoid get(Node* node, int a) {
        return query(node, a, a+1);
    }

    void print(Node* t, int n) {
        for (int i=0; i<n; i++) {
            cout << query(t, i, i+1);
            if (i == n-1) cout << endl;
            else cout << ' ';
        }
    }

    // void init_pool(int siz) {
    //     Node::_pool = ObjectPool<Node>(siz);
    // }
    // void clear_pool() {
    //     Node::_pool.clear();
    // }
};

template<typename F, typename G, typename H, typename T, typename E>
PersistentLazySegmentTree<F, G, H, T, E> get_persistent_lazy_segment_tree(const F& f, const G& g, const H& h, const T& ti, const E& ei) {
    return {f, g, h, ti, ei};
}

// 1点加算・区間和取得
auto f = [](ll a, ll b) -> ll { return a + b; };
auto g = [](ll a, ll b) -> ll { return a + b; };
auto h = [](ll a, ll b) -> ll { return a + b; };
const ll T = 0;
const ll E = 0;

void solve() {
    ll H, W, Q;
    cin >> H >> W >> Q;

    auto seg = get_persistent_lazy_segment_tree(f, g, h, T, E);
    // seg.init_pool(15000000);
    vector<decltype(seg)::Node*> history(Q+1);
    history[0] = seg.build(vector<ll>(W+1, 0));
    vector<pll> upd(H);
    rep(i, Q) {
        ll op;
        cin >> op;
        history[i+1] = history[i];
        if (op == 1) {
            ll wl, wr, x;
            cin >> wl >> wr >> x;
            wl--;

            history[i+1] = seg.update(history[i+1], wl, wr, x);
        } elif (op == 2) {
            ll h, x;
            cin >> h >> x;
            h--;

            upd[h] = {i, x};
        } else {
            ll h, w;
            cin >> h >> w;
            h--; w--;

            ll res = upd[h].second + seg.get(history[i+1], w) - seg.get(history[upd[h].first], w);
            print(res);
        }
        // seg.print(history[i+1], W+1);
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
