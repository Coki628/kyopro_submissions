/*
・これはMLE。。NODESの固定値減らしてもダメだった…。
・Rectagle Sum
・Nyaanさん版を持ってきたら内部実装が永続セグ木だった。CFはメモリに厳しい。
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

template<typename T, typename F, int NODES = 20000000>
struct PersistentSegmentTree {
    using ll = long long;
    struct Node {
        T data;
        Node *l, *r;
        Node() {
        }
        Node(const T &_data) : data(_data), l(nullptr), r(nullptr) {
        }
    };

    Node *pool;
    int pid;
    ll N;
    const F f;
    const T ID;
    Node *nil;
    vector<Node *> roots;

    PersistentSegmentTree(const vector<T> &v, const F &f_, const T &ID_)
        : pid(0),
          f(f_),
          ID(ID_),
          nil(nullptr) {
        pool = new Node[NODES];
        nil = my_new(ID);
        nil->l = nil->r = nil;
        roots.reserve(262144);
        roots.push_back(build(v));
    }

    PersistentSegmentTree(const ll &N_, const F &f_, const T &ID_)
        : pid(0),
          N(N_),
          f(f_),
          ID(ID_),
          nil(nullptr) {
        pool = new Node[NODES];
        nil = my_new(ID);
        nil->l = nil->r = nil;
        roots.reserve(262144);
        roots.push_back(nil);
    }

    Node *my_new(const T &data) {
        pool[pid].data = data;
        pool[pid].l = pool[pid].r = nil;
        return &(pool[pid++]);
    }

    Node *merge(Node *l, Node *r) {
        pool[pid].data = f(l->data, r->data);
        pool[pid].l = l;
        pool[pid].r = r;
        return &(pool[pid++]);
    }

    Node *build(const vector<T> &v) {
        N = (ll)v.size();
        return build(0, (ll)v.size(), v);
    }

    Node *build(ll l, ll r, const vector<T> &v) {
        if (l + 1 == r) return my_new(v[l]);
        ll m = (l + r) >> 1;
        return merge(build(l, m, v), build(m, r, v));
    }

private:
    Node *update_(ll a, const T &x, Node *n, ll l, ll r) {
        if (l + 1 == r) return my_new(x);
        ll m = (l + r) >> 1;
        if (a < m) return merge(update_(a, x, n->l, l, m), n->r);
        return merge(n->l, update_(a, x, n->r, m, r));
    }
    Node *add_(ll a, const T &x, Node *n, ll l, ll r) {
        if (l + 1 == r) return my_new(f(x, n->data));
        ll m = (l + r) >> 1;
        if (a < m) return merge(add_(a, x, n->l, l, m), n->r);
        return merge(n->l, add_(a, x, n->r, m, r));
    }
    T query_(ll a, ll b, Node *n, ll l, ll r) {
        if (n == nil) return ID;
        if (r <= a or b <= l) return ID;
        if (a <= l and r <= b) return n->data;
        ll m = (l + r) >> 1;
        return f(query_(a, b, n->l, l, m), query_(a, b, n->r, m, r));
    }

public:
    Node *update(Node *n, ll k, const T &x) {
        Node *root = update_(k, x, n, 0, N);
        roots.push_back(root);
        return root;
    }
    Node *update(int t, ll k, const T &x) {
        Node *root = update_(k, x, roots[t], 0, N);
        roots.push_back(root);
        return root;
    }
    Node *update(ll k, const T &x) {
        Node *root = update_(k, x, roots.back(), 0, N);
        roots.push_back(root);
        return root;
    }

    Node *add(Node *n, ll k, const T &x) {
        Node *root = add_(k, x, n, 0, N);
        roots.push_back(root);
        return root;
    }
    Node *add(int t, ll k, const T &x) {
        Node *root = add_(k, x, roots[t], 0, N);
        roots.push_back(root);
        return root;
    }
    Node *add(ll k, const T &x) {
        Node *root = add_(k, x, roots.back(), 0, N);
        roots.push_back(root);
        return root;
    }

    T query(Node *n, ll a, ll b) {
        return query_(a, b, n, 0, N);
    }
    T query(int t, ll a, ll b) {
        return query_(a, b, roots[t], 0, N);
    }
    T query(ll a, ll b) {
        return query_(a, b, roots.back(), 0, N);
    }

    Node *new_tree() {
        return nil;
    }
};

template<typename T, typename U, typename F> struct RectangleSum {
    PersistentSegmentTree<U, F> seg;
    vector<T> xs, ys;
    vector<U> ws;
    vector<int> ord;

    RectangleSum(
        const vector<T> &xs_, const vector<T> &ys_, const vector<U> &ws_,
        const F &f
    )
        : seg({(int)xs_.size() + 1, f, U(0)}) {
        int N = xs_.size();
        xs.reserve(N);
        ys.reserve(N);
        ws.reserve(N);
        ord.resize(N);
        iota(begin(ord), end(ord), 0);
        sort(begin(ord), end(ord), [&](int i, int j) {
            return xs_[i] < xs_[j];
        });
        for (auto &i : ord) {
            xs.push_back(xs_[i]);
            ys.push_back(ys_[i]);
            ws.push_back(ws_[i]);
        }
        iota(begin(ord), end(ord), 0);
        sort(begin(ord), end(ord), [&](int i, int j) { return ys[i] < ys[j]; });
        vector<T> ys2;
        ys2.reserve(N);
        for (auto &i : ord) {
            seg.add(i, ws[i]);
            ys2.push_back(ys[i]);
        }
        ys.swap(ys2);
    }

    // [ [x1, 0], [x2, y] )
    U rect_sum(T x1, T x2, T y) {
        int l = lower_bound(begin(xs), end(xs), x1) - begin(xs);
        int r = lower_bound(begin(xs), end(xs), x2) - begin(xs);
        int u = lower_bound(begin(ys), end(ys), y) - begin(ys);
        return seg.query(u, l, r);
    }

    // [ [x1, y1], [x2, y2] )
    U rect_sum(T x1, T y1, T x2, T y2) {
        if (x1 >= x2 || y1 >= y2) return U(0);
        int l = lower_bound(begin(xs), end(xs), x1) - begin(xs);
        int r = lower_bound(begin(xs), end(xs), x2) - begin(xs);
        int d = lower_bound(begin(ys), end(ys), y1) - begin(ys);
        int u = lower_bound(begin(ys), end(ys), y2) - begin(ys);
        return seg.query(u, l, r) - seg.query(d, l, r);
    }
};

void solve() {
    ll N, Q;
    cin >> N >> Q;
    vector<int> xs, ys;
    vector<ll> ws;
    rep(i, N) {
        ll h, w;
        cin >> h >> w;
        xs.eb(w);
        ys.eb(h);
        ws.eb(w * h);
    }

    auto f = [](ll u, ll v) { return u + v; };
    RectangleSum<int, ll, decltype(f)> rect(xs, ys, ws, f);
    rep(i, Q) {
        ll hs, ws, hb, wb;
        cin >> hs >> ws >> hb >> wb;
        ll res = rect.rect_sum(ws + 1, hs + 1, wb, hb);
        print(res);
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
