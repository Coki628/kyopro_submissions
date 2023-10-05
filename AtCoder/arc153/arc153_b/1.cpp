/*
参考：https://twitter.com/nok0_kyopro/status/1614262035893870595
　　　https://atcoder.jp/contests/arc153/submissions/38005492
・ライブラリ整備
・グリッド回転、縦横独立、区間反転、平衡二分木
・こどふぉで区間反転使ったので、TLで話だけ聞いてたこれやってみた。
　問題見たら全然自力でできなかった。縦横独立で処理していいのね…。
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

// see: https://nyaannyaan.github.io/library/rbst/rbst-base.hpp
template<typename Node> struct RBSTBase {
    using Ptr = Node *;
    template<typename... Args> inline Ptr my_new(Args... args) {
        return new Node(args...);
    }
    inline void my_del(Ptr t) {
        delete t;
    }
    inline Ptr make_tree() const {
        return nullptr;
    }

    // for avoiding memory leak, activate below
    /*
    using Ptr = shared_ptr<Node>;
    template <typename... Args>
    inline Ptr my_new(Args... args) {
        return make_shared<Node>(args...);
    }
    inline void my_del(Ptr t) {}
    Ptr make_tree() {return Ptr();}
    */

    int size(Ptr t) const {
        return count(t);
    }

    Ptr merge(Ptr l, Ptr r) {
        if (!l || !r) return l ? l : r;
        if (int((rng() * (l->cnt + r->cnt)) >> 32) < l->cnt) {
            push(l);
            l->r = merge(l->r, r);
            return update(l);
        } else {
            push(r);
            r->l = merge(l, r->l);
            return update(r);
        }
    }

    pair<Ptr, Ptr> split(Ptr t, int k) {
        if (!t) return {nullptr, nullptr};
        push(t);
        if (k <= count(t->l)) {
            auto s = split(t->l, k);
            t->l = s.second;
            return {s.first, update(t)};
        } else {
            auto s = split(t->r, k - count(t->l) - 1);
            t->r = s.first;
            return {update(t), s.second};
        }
    }

    Ptr build(int l, int r, const vector<decltype(Node::key)> &v) {
        if (l + 1 == r) return my_new(v[l]);
        int m = (l + r) >> 1;
        Ptr pm = my_new(v[m]);
        if (l < m) pm->l = build(l, m, v);
        if (m + 1 < r) pm->r = build(m + 1, r, v);
        return update(pm);
    }

    Ptr build(const vector<decltype(Node::key)> &v) {
        return build(0, (int)v.size(), v);
    }

    template<typename... Args> void insert(Ptr &t, int k, const Args &...args) {
        auto x = split(t, k);
        t = merge(merge(x.first, my_new(args...)), x.second);
    }

    void erase(Ptr &t, int k) {
        auto x = split(t, k);
        auto y = split(x.second, 1);
        my_del(y.first);
        t = merge(x.first, y.second);
    }

protected:
    static uint64_t rng() {
        static uint64_t x_ = 88172645463325252ULL;
        return x_ ^= x_ << 7, x_ ^= x_ >> 9, x_ & 0xFFFFFFFFull;
    }

    inline int count(const Ptr t) const {
        return t ? t->cnt : 0;
    }

    virtual void push(Ptr) = 0;

    virtual Ptr update(Ptr) = 0;
};

template<typename T, typename E> struct LazyReversibleRBSTNode {
    typename RBSTBase<LazyReversibleRBSTNode>::Ptr l, r;
    T key, sum;
    E lazy;
    int cnt;
    bool rev;

    LazyReversibleRBSTNode(const T &t = T(), const E &e = E())
        : l(),
          r(),
          key(t),
          sum(t),
          lazy(e),
          cnt(1),
          rev(false) {
    }
};

// see: https://nyaannyaan.github.io/library/rbst/lazy-reversible-rbst.hpp
template<
    typename T, typename E, T (*f)(T, T), T (*g)(T, E), E (*h)(E, E),
    T (*ts)(T)>
struct LazyReversibleRBST : RBSTBase<LazyReversibleRBSTNode<T, E>> {
    using Node = LazyReversibleRBSTNode<T, E>;
    using base = RBSTBase<LazyReversibleRBSTNode<T, E>>;
    using base::merge;
    using base::split;
    using typename base::Ptr;

    LazyReversibleRBST() = default;

    void toggle(Ptr t) {
        if (!t) return;
        swap(t->l, t->r);
        t->sum = ts(t->sum);
        t->rev ^= true;
    }

    T fold(Ptr &t, int a, int b) {
        auto x = split(t, a);
        auto y = split(x.second, b - a);
        auto ret = sum(y.first);
        t = merge(x.first, merge(y.first, y.second));
        return ret;
    }

    void reverse(Ptr &t, int a, int b) {
        auto x = split(t, a);
        auto y = split(x.second, b - a);
        toggle(y.first);
        t = merge(x.first, merge(y.first, y.second));
    }

    void apply(Ptr &t, int a, int b, const E &e) {
        auto x = split(t, a);
        auto y = split(x.second, b - a);
        propagate(y.first, e);
        t = merge(x.first, merge(y.first, y.second));
    }

protected:
    inline T sum(const Ptr t) const {
        return t ? t->sum : T();
    }

    Ptr update(Ptr t) override {
        push(t);
        t->cnt = 1;
        t->sum = t->key;
        if (t->l) t->cnt += t->l->cnt, t->sum = f(t->l->sum, t->sum);
        if (t->r) t->cnt += t->r->cnt, t->sum = f(t->sum, t->r->sum);
        return t;
    }

    void push(Ptr t) override {
        if (t->rev) {
            if (t->l) toggle(t->l);
            if (t->r) toggle(t->r);
            t->rev = false;
        }
        if (t->lazy != E()) {
            if (t->l) propagate(t->l, t->lazy);
            if (t->r) propagate(t->r, t->lazy);
            t->lazy = E();
        }
    }

    void propagate(Ptr t, const E &x) {
        t->lazy = h(t->lazy, x);
        t->key = g(t->key, x);
        t->sum = g(t->sum, x);
    }
};

using T = ll;
using E = ll;
T f(T a, T b) { return a + b; }
T g(T a, E b) { return a + b; }
T h(E a, E b) { return a + b; }
T ts(T a) { return a; }

void solve() {
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    rep(h, H) {
        cin >> grid[h];
    }

    vector<ll> ph(H), pw(W);
    iota(ALL(ph), 0);
    iota(ALL(pw), 0);
    LazyReversibleRBST<T, E, f, g, h, ts> rbst;
    auto pht = rbst.build(ph);
    auto pwt = rbst.build(pw);

    ll Q;
    cin >> Q;
    rep(_, Q) {
        ll a, b;
        cin >> a >> b;
        rbst.reverse(pht, 0, a);
        rbst.reverse(pht, a, H);
        rbst.reverse(pwt, 0, b);
        rbst.reverse(pwt, b, W);
    }

    vector<string> ans(H, string(W, '.'));
    rep(h, H) {
        rep(w, W) {
            ans[h][w] = grid[rbst.fold(pht, h, h + 1)][rbst.fold(pwt, w, w + 1)];
        }
    }
    rep(h, H) {
        print(ans[h]);
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
