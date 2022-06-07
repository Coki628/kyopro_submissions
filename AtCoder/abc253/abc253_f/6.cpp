/*
参考：https://suisen-cp.github.io/cp-library-cpp/library/datastructure/segment_tree/persistent_lazy_segment_tree.hpp
　　　https://ei1333.github.io/library/structure/segment-tree/persistent-segment-tree.cpp
・ライブラリ整備：永続遅延セグメント木
・頑張って作った。suisenさんのロジックを、うしさんの永続セグ木に移植した。
・これだと20万のN,Qで0.7秒、875MBだった。速度はいいけどやっぱりメモリがきついね。。
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

// 参考：https://suisen-cp.github.io/cp-library-cpp/library/util/object_pool.hpp
template <typename T, bool auto_extend = false>
struct ObjectPool {
    using value_type = T;
    using value_pointer_type = T*;

    template <typename U>
    using container_type = std::conditional_t<auto_extend, std::deque<U>, std::vector<U>>;

    container_type<value_type> pool;
    container_type<value_pointer_type> stock;
    decltype(stock.begin()) it;

    ObjectPool() : ObjectPool(0) {}
    ObjectPool(int siz) : pool(siz), stock(siz) {
        clear();
    }

    int capacity() const { return pool.size(); }
    int size() const { return it - stock.begin(); }

    value_pointer_type alloc() {
        if constexpr (auto_extend) ensure();
        return *it++;
    }

    void free(value_pointer_type t) {
        *--it = t;
    }

    void clear() {
        int siz = pool.size();
        it = stock.begin();
        for (int i = 0; i < siz; i++) stock[i] = &pool[i];
    }

    void ensure() {
        if (it != stock.end()) return;
        int siz = stock.size();
        for (int i = siz; i <= siz * 2; ++i) {
            stock.push_back(&pool.emplace_back());
        }
        it = stock.begin() + siz;
    }
};

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
        static inline ObjectPool<Node> _pool;
        static Node *clone(Node *node) {
            return &(*_pool.alloc() = *node);
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
        auto t = new Node(f(l->data, r->data), OM0);
        t->l = l;
        t->r = r;
        return t;
    }

    Node *build(int l, int r, const vector< Monoid > &v) {
        if(l + 1 >= r) return new Node(v[l], OM0);
        return merge(build(l, (l + r) >> 1, v), build((l + r) >> 1, r, v));
    }

    template <bool do_clone = true>
    auto push(Node *node) {
        auto res = node;
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
        auto res = Node::clone(node);
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
            auto res = push(node);
            return merge(update(a, b, x, res->l, l, (l + r) >> 1), update(a, b, x, res->r, (l + r) >> 1, r));
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

    void init_pool(int siz) {
        Node::_pool = ObjectPool<Node>(siz);
    }
    void clear_pool() {
        Node::_pool.clear();
    }
};

// 区間加算・区間和取得
struct Node {
    ll val, sz;
    operator ll() const { return val; }
};
auto f = [](Node a, Node b) -> Node { return { a.val+b.val, a.sz+b.sz }; };
auto g = [](Node a, ll b) -> Node { return { a.val+a.sz*b, a.sz }; };
auto h = [](ll a, ll b) -> ll { return a + b; };
const Node T = {0, 0};
const ll E = 0;

using PLST = PersistentLazySegmentTree<
    function<Node(Node, Node)>,
    function<Node(Node, ll)>,
    function<ll(ll, ll)>,
    Node, ll
>;

void solve() {
    ll H, W, Q;
    cin >> H >> W >> Q;

    PLST seg(f, g, h, T, E);
    seg.init_pool(15000000);
    vector<PLST::Node*> history(Q+1);
    history[0] = seg.build(vector<Node>(W+1, {0, 1}));
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
