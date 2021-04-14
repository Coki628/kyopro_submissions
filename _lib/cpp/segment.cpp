/*
・ライブラリ：区間
*/

#include "_tpl.cpp"


template<typename T>
vector<T> accumulate(vector<T> &A, bool indexed=0) {
    int n = A.size();
    auto res = A;
    rep(i, n-1) res[i+1] += res[i];
    if (indexed) res.insert(res.begin(), 0);
    return res;
}


template<typename T> struct Accumulate {
    vector<T> acc;
    int N;
    
    Accumulate(vector<T> &A) {
        N = A.size();
        acc = A;
        rep(i, N-1) acc[i+1] += acc[i];
        acc.insert(acc.begin(), 0);
    }

    T query(int l, int r) {
        return acc[r]-acc[l];
    }

    T get(int i) {
        return query(i, i+1);
    }

    T operator[](int i) {
        return get(i);
    }
};


template<typename Monoid, typename F>
struct SegmentTree {

    int sz;
    vector<Monoid> seg;

    const F f;
    const Monoid M1;

    SegmentTree(int n, const F f, const Monoid &M1) : f(f), M1(M1) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.assign(2 * sz, M1);
    }

    SegmentTree(const F f, const Monoid &M1) : f(f), M1(M1) {}

    void resize(int n) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.resize(2 * sz, M1);
    }

    void clear() {
        seg.clear();
    }

    void set(int k, const Monoid &x) {
        seg[k+sz] = x;
    }

    void build() {
        for(int k = sz - 1; k > 0; k--) {
            seg[k] = f(seg[2*k], seg[2*k+1]);
        }
    }

    void build(vector<Monoid> &A) {
        int n = A.size();
        resize(n);
        rep(i, 0, n) set(i, A[i]);
        build();
    }

    void update(int k, const Monoid &x) {
        k += sz;
        seg[k] = x;
        while(k >>= 1) {
            seg[k] = f(seg[2*k], seg[2*k+1]);
        }
    }

    Monoid query(int a, int b) {
        Monoid L = M1, R = M1;
        for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
            if(a & 1) L = f(L, seg[a++]);
            if(b & 1) R = f(seg[--b], R);
        }
        return f(L, R);
    }

    Monoid operator[](const int &k) const {
        return seg[k+sz];
    }

    Monoid all() {
        return seg[1];
    }

    void print(int n) {
        rep(i, n) {
            cout << query(i, i+1);
            if (i == n-1) cout << endl;
            else cout << ' ';
        }
    }

    template<typename C>
    int find_subtree(int a, const C &check, Monoid &M, bool type) {
        while(a < sz) {
            Monoid nxt = type ? f(seg[2 * a + type], M) : f(M, seg[2 * a + type]);
            if(check(nxt)) a = 2 * a + type;
            else M = nxt, a = 2 * a + 1 - type;
        }
        return a - sz;
    }

    // 区間[a,N)でcheckの条件を満たすような最小位置を返す(なければ-1)
    template<typename C>
    int find_first(int a, const C &check) {
        Monoid L = M1;
        if(a <= 0) {
            if(check(f(L, seg[1]))) return find_subtree(1, check, L, false);
            return -1;
        }
        int b = sz;
        for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
            if(a & 1) {
                Monoid nxt = f(L, seg[a]);
                if(check(nxt)) return find_subtree(a, check, L, false);
                L = nxt;
                ++a;
            }
        }
        return -1;
    }

    // 区間[0,b)でcheckの条件を満たすような最大位置を返す(なければ-1)
    template<typename C>
    int find_last(int b, const C &check) {
        Monoid R = M1;
        if(b >= sz) {
            if(check(f(seg[1], R))) return find_subtree(1, check, R, true);
            return -1;
        }
        int a = sz;
        for(b += sz; a < b; a >>= 1, b >>= 1) {
            if(b & 1) {
                Monoid nxt = f(seg[--b], R);
                if(check(nxt)) return find_subtree(b, check, R, true);
                R = nxt;
            }
        }
        return -1;
    }
};

template<typename Monoid, typename F>
SegmentTree<Monoid, F> get_segment_tree(int N, const F& f, const Monoid& M1) {
    return {N, f, M1};
}

template<typename Monoid, typename F>
SegmentTree<Monoid, F> get_segment_tree(const F& f, const Monoid& M1) {
    return {f, M1};
}

// // 区間[l,r]で左から最初にxに対して比較の条件を満たすような値が出現する位置
// template<typename G> ll bisearch_fore(ll l, ll r, Monoid x, const G &compare) {
//     ll ok = r + 1;
//     ll ng = l - 1;
//     while (ng+1 < ok) {
//         ll mid = (ok+ng) / 2;
//         if (compare(query(l, mid+1), x)) {
//             ok = mid;
//         } else {
//             ng = mid;
//         }
//     }
//     if (ok != r + 1) {
//         return ok;
//     } else {
//         return -1;
//     }
// }

// // 区間[l,r]で右から最初にxに対して比較の条件を満たすような値が出現する位置
// template<typename G> ll bisearch_back(ll l, ll r, Monoid x, const G &compare) {
//     ll ok = l - 1;
//     ll ng = r + 1;
//     while (ok+1 < ng) {
//         ll mid = (ok+ng) / 2;
//         if (compare(query(mid, r+1), x)) {
//             ok = mid;
//         } else {
//             ng = mid;
//         }
//     }
//     if (ok != l - 1) {
//         return ok;
//     } else {
//         return -1;
//     }
// }

// 使用例
// SegmentTree<ll> seg([](ll a, ll b) { return max(a, b); }, -INF);
// stmx.bisearch_back(l, r, x, greater<ll>());


template<typename Monoid, typename F>
struct SegmentTreeIndex {

    int sz;
    vector<pair<Monoid, int>> seg;

    const F f;
    const Monoid M1;

    pair<Monoid, int> compare(const pair<Monoid, int> &a, const pair<Monoid, int> &b) {
        if (a.first == b.first) {
            // 同値はindexが小さい方優先
            if (a.second <= b.second) {
                return a;
            } else {
                return b;
            }
        } else if (f(a.first, b.first) == a.first) {
            return a;
        } else {
            return b;
        }
    }

    SegmentTreeIndex(int n, const F f, const Monoid &M1) : f(f), M1(M1) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.assign(2 * sz, {M1, -1});
    }

    SegmentTreeIndex(const F f, const Monoid &M1) : f(f), M1(M1) {}

    void resize(int n) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.assign(2 * sz, {M1, -1});
    }

    void set(int k, const Monoid &x) {
        seg[k+sz] = {x, k};
    }

    void build() {
        for(int k = sz - 1; k > 0; k--) {
            seg[k] = compare(seg[2*k], seg[2*k+1]);            
        }
    }

    void build(vector<Monoid> &A) {
        int n = A.size();
        resize(n);
        rep(i, 0, n) set(i, A[i]);
        build();
    }

    void update(int k, const Monoid &x) {
        k += sz;
        seg[k] = {x, k-sz};
        while(k >>= 1) {
            seg[k] = compare(seg[2*k], seg[2*k+1]);
        }
    }

    void add(int k, const Monoid &x) {
        update(k, seg[k+sz].first + x);
    }

    pair<Monoid, int> query(int a, int b) {
        pair<Monoid, int> L = {M1, -1}, R = {M1, -1};
        for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
            if(a & 1) L = compare(L, seg[a++]);
            if(b & 1) R = compare(seg[--b], R);
        }
        return compare(L, R);
    }

    Monoid operator[](const int &k) const {
        return seg[k+sz].first;
    }

    pair<Monoid, int> all() {
        return seg[1];
    }

    void print(int n) {
        rep(i, n) {
            cout << query(i, i+1).first;
            if (i == n-1) cout << endl;
            else cout << ' ';
        }
    }
};

template<typename Monoid, typename F>
SegmentTreeIndex<Monoid, F> get_segment_tree_index(int N, const F& f, const Monoid& M1) {
    return {N, f, M1};
}

template<typename Monoid, typename F>
SegmentTreeIndex<Monoid, F> get_segment_tree_index(const F& f, const Monoid& M1) {
    return {f, M1};
}


// スパーステーブル：構築にO(NlogN)、区間最小(最大)をO(1)で取得
template<typename T, typename F>
struct SparseTable {

    const F f;
    vector<vector<T>> dat;
    vector<ll> height;

    SparseTable(const F f) : f(f) {}

    SparseTable(vector<T> &A, const F f) : f(f) {
        build(A);
    }

    void build(vector<T> &A) {
        ll N = A.size();

        ll h = 0;
        while ((1<<h) <= N) {
            h++;
        }
        dat.resize(h);
        rep(i, 0, h) dat[i].resize(1<<h);
        height.resize(N+1);

        rep(i, 2, N+1) {
            height[i] = height[i>>1] + 1;
        }
        rep(i, 0, N) {
            dat[0][i] = A[i];
        }
        rep(i, 1, h) {
            rep(j, 0, N) {
                dat[i][j] = f(dat[i-1][j], dat[i-1][min(j+(1<<(i-1)), N-1)]);
            }
        }
    }

    // 区間[l,r)でのmin,maxを取得
    T query(ll l, ll r) {
        assert(l < r);
        ll a = height[r-l];
        return f(dat[a][l], dat[a][r-(1<<a)]);
    }

    // 区間[l,r]で左から最初にxに対して比較の条件を満たすような値が出現する位置
    template<typename G> ll bisearch_fore(ll l, ll r, T x, const G &compare) {
        ll ok = r + 1;
        ll ng = l - 1;
        while (ng+1 < ok) {
            ll mid = (ok+ng) / 2;
            if (compare(query(l, mid+1), x)) {
                ok = mid;
            } else {
                ng = mid;
            }
        }
        if (ok != r + 1) {
            return ok;
        } else {
            return -1;
        }
    }

    // 区間[l,r]で右から最初にxに対して比較の条件を満たすような値が出現する位置
    template<typename G> ll bisearch_back(ll l, ll r, T x, const G &compare) {
        ll ok = l - 1;
        ll ng = r + 1;
        while (ok+1 < ng) {
            ll mid = (ok+ng) / 2;
            if (compare(query(mid, r+1), x)) {
                ok = mid;
            } else {
                ng = mid;
            }
        }
        if (ok != l - 1) {
            return ok;
        } else {
            return -1;
        }
    }
    // 使用例
    // stmx.bisearch_back(l, r, x, greater<ll>());
};

template<typename T, typename F>
SparseTable<T, F> get_sparse_table(vector<T> &A, const F& f) {
    return {A, f};
}


template<typename T>
struct BIT {

    int sz;
    vector<T> tree;

    BIT(int n) {
        // 0-indexed
        n++;
        sz = 1;
        while (sz < n) {
            sz *= 2;
        }
        tree.resize(sz);
    }

    // [0, i]を合計する
    T sum(int i) {
        T s = 0;
        i++;
        while (i > 0) {
            s += tree[i-1];
            i -= i & -i;
        }
        return s;
    }

    void add(int i, T x) {
        i++;
        while (i <= sz) {
            tree[i-1] += x;
            i += i & -i;
        }
    }

    // 区間和の取得 [l, r)
    T query(int l, int r) {
        return sum(r-1) - sum(l-1);
    }

    T get(int i) {
        return query(i, i+1);
    }

    void update(int i, T x) {
        add(i, x - get(i));
    }

    T operator[](int i) {
        return get(i);
    }

    // 区間[l, r]を左から右に向かってx番目の値がある位置
    ll bisearch_fore(int l, int r, ll x) {
        ll l_sm = sum(l-1);
        int ok = r + 1;
        int ng = l - 1;
        while (ng+1 < ok) {
            int mid = (ok+ng) / 2;
            if (sum(mid) - l_sm >= x) {
                ok = mid;
            } else {
                ng = mid;
            }
        }
        if (ok != r+1) {
            return ok;
        } else {
            return -1;
        }
    }

    // 区間[l, r]を右から左に向かってx番目の値がある位置
    ll bisearch_back(int l, int r, ll x) {
        ll r_sm = sum(r);
        int ok = l - 1;
        int ng = r + 1;
        while (ok+1 < ng) {
            int mid = (ok+ng) / 2;
            if (r_sm - sum(mid-1) >= x) {
                ok = mid;
            } else {
                ng = mid;
            }
        }
        if (ok != l - 1) {
            return ok;
        } else {
            return -1;
        }
    }
};

// 区間加算BIT(区間加算・区間和取得)
template<typename T>
struct BIT2 {

    int N;
    vector<T> data0, data1;

    BIT2() {};

    BIT2(int N) {
        resize(N);
    }

    void resize(int n) {
        // 添字0が使えないので、内部的には全て1-indexedとして扱う
        N = ++n;
        data0.resize(N);
        data1.resize(N);
    }

    void _add(vector<T> &data, int k, T x) {
        k++;
        while (k < N) {
            data[k] += x;
            k += k & -k;
        }
    }

    T _get(vector<T> &data, int k) {
        k++;
        T s = 0;
        while (k) {
            s += data[k];
            k -= k & -k;
        }
        return s;
    }

    // 区間[l,r)に値xを加算
    void add(int l, int r, T x) {
        _add(data0, l, -x*(l-1));
        _add(data0, r, x*(r-1));
        _add(data1, l, x);
        _add(data1, r, -x);
    }

    // 1点加算
    void add(int i, T x) {
        add(i, i+1, x);
    }

    // 区間[l,r)の和を取得
    T query(int l, int r) {
        return _get(data1, r-1) * (r-1) + _get(data0, r-1) - _get(data1, l-1) * (l-1) - _get(data0, l-1);
    }

    // 1点取得
    T get(int i) {
        return query(i, i+1);
    }

    // 1点更新
    void update(int i, T x) {
        add(i, i+1, x - get(i));
    }

    T operator[](int i) {
        return get(i);
    }
};


// // 遅延評価セグメント木(旧)
// template<typename T, typename E>
// struct LazySegmentTree {
//     typedef function<T(T, T)> F;
//     typedef function<T(T, E)> G;
//     typedef function<E(E, E)> H;
//     typedef function<E(E, int)> P;
//     int n;
//     F f;
//     G g;
//     H h;
//     P p;
//     T d1;
//     E d0;
//     vector<T> dat;
//     vector<E> laz;
//     LazySegmentTree(int n_, F f, G g, H h, T d1, E d0,
//             vector<T> v=vector<T>(), P p=[](E a, int b){ return a; }):
//             f(f), g(g), h(h), d1(d1), d0(d0), p(p) {
//         init(n_);
//         if (n_==(int)v.size()) build(n_, v);
//     }
//     void init(int n_) {
//         n = 1;
//         while (n<n_) n *= 2;
//         dat.clear();
//         dat.resize(2*n-1, d1);
//         laz.clear();
//         laz.resize(2*n-1, d0);
//     }
//     void build(int n_, vector<T> v) {
//         for (int i=0;i<n_;i++) dat[i+n-1] = v[i];
//         for (int i=n-2;i>=0;i--)
//             dat[i] = f(dat[i*2+1], dat[i*2+2]);
//     }
//     inline void eval(int len, int k) {
//         if (laz[k]==d0) return;
//         if (k*2+1<n*2-1) {
//             laz[k*2+1] = h(laz[k*2+1], laz[k]);
//             laz[k*2+2] = h(laz[k*2+2], laz[k]);
//         }
//         dat[k] = g(dat[k], p(laz[k], len));
//         laz[k] = d0;
//     }
//     T update(int a, int b, E x, int k, int l, int r) {
//         eval(r-l, k);
//         if (r<=a||b<=l) return dat[k];
//         if (a<=l&&r<=b) {
//             laz[k] = h(laz[k], x);
//             return g(dat[k], p(laz[k], r-l));
//         }
//         return dat[k] = f(update(a, b, x, k*2+1, l, (l+r)/2),
//                           update(a, b, x, k*2+2, (l+r)/2, r));
//     }
//     T update(int a, int b, E x) {
//         return update(a, b, x, 0, 0, n);
//     }
//     T query(int a, int b, int k, int l, int r) {
//         eval(r-l, k);
//         if(r<=a||b<=l) return d1;
//         if(a<=l&&r<=b) return dat[k];
//         T vl = query(a, b, k*2+1, l, (l+r)/2);
//         T vr = query(a, b, k*2+2, (l+r)/2, r);
//         return f(vl, vr);
//     }
//     T query(int a, int b) {
//         return query(a, b, 0, 0, n);
//     }
// };


// 遅延評価セグメント木(beetさん版)
template<typename F, typename G, typename H, typename T, typename E>
struct LazySegmentTree {
    int n, height;
    F f;
    G g;
    H h;
    T ti;
    E ei;
    vector<T> dat;
    vector<E> laz;
    LazySegmentTree(F f, G g, H h, T ti, E ei):
        f(f), g(g), h(h), ti(ti), ei(ei) {}

    void init(int n_){
        n = 1; height = 0;
        while (n<n_) n<<=1, height++;
        dat.assign(2*n, ti);
        laz.assign(2*n, ei);
    }

    void build(int n_) {
        init(n_);
    }

    void build(const vector<T> &v){
        int n_ = v.size();
        init(n_);
        for (int i=0;i<n_;i++) dat[n+i] = v[i];
        for (int i=n-1;i;i--)
        dat[i] = f(dat[(i<<1)|0], dat[(i<<1)|1]);
    }

    inline T reflect(int k){
        return laz[k]==ei?dat[k]:g(dat[k], laz[k]);
    }

    inline void propagate(int k){
        if (laz[k]==ei) return;
        laz[(k<<1)|0] = h(laz[(k<<1)|0], laz[k]);
        laz[(k<<1)|1] = h(laz[(k<<1)|1], laz[k]);
        dat[k] = reflect(k);
        laz[k] = ei;
    }

    inline void thrust(int k){
        for (int i=height;i;i--) propagate(k>>i);
    }

    inline void recalc(int k){
        while (k>>=1)
        dat[k] = f(reflect((k<<1)|0), reflect((k<<1)|1));
    }

    void update(int a, int b, E x){
        if (a>=b) return;
        thrust(a+=n);
        thrust(b+=n-1);
        for (int l=a,r=b+1;l<r;l>>=1,r>>=1) {
            if (l&1) laz[l] = h(laz[l], x), l++;
            if (r&1) --r, laz[r] = h(laz[r], x);
        }
        recalc(a);
        recalc(b);
    }

    void set_val(int a, T x){
        thrust(a+=n);
        dat[a] = x; laz[a] = ei;
        recalc(a);
    }

    T query(int a, int b){
        if (a>=b) return ti;
        thrust(a+=n);
        thrust(b+=n-1);
        T vl = ti, vr = ti;
        for (int l=a,r=b+1;l<r;l>>=1,r>>=1) {
            if (l&1) vl = f(vl, reflect(l++));
            if (r&1) vr = f(reflect(--r), vr);
        }
        return f(vl, vr);
    }

    template<typename C>
    int find(int st, const C &check, T &acc, int k, int l, int r){
        if (l+1==r) {
            acc = f(acc, reflect(k));
            return check(acc)?k-n:-1;
        }
        propagate(k);
        int m = (l+r)>>1;
        if (m<=st) return find(st, check, acc, (k<<1)|1, m, r);
        if (st<=l&&!check(f(acc,dat[k]))) {
            acc = f(acc,dat[k]);
            return -1;
        }
        int vl = find(st, check, acc, (k<<1)|0, l, m);
        if (~vl) return vl;
        return find(st, check, acc, (k<<1)|1, m, r);
    }

    // 区間[st,N)でcheckの条件を満たすような最小位置を返す(なければ-1)
    template<typename C>
    int find(int st, const C &check){
        T acc = ti;
        return find(st, check, acc, 1, 0, n);
    }

    void update(int i, E x) {
        update(i, i+1, x);
    }

    T operator[](int i) {
        return query(i, i+1);
    }

    void print(int n) {
        rep(i, 0, n) {
            cout << query(i, i+1);
            if (i == n-1) cout << endl;
            else cout << ' ';
        }
    }
};

template<typename F, typename G, typename H, typename T, typename E>
LazySegmentTree<F, G, H, T, E> get_Lazy_segment_tree(const F& f, const G& g, const H& h, const T& ti, const E& ei) {
    return {f, g, h, ti, ei};
}


// 遅延評価セグメント木(うしさん版)
template<typename F, typename G, typename H, typename Monoid, typename OperatorMonoid>
struct LazySegmentTree {
    int sz, height;
    vector<Monoid> data;
    vector<OperatorMonoid> lazy;
    const F f;
    const G g;
    const H h;
    const Monoid M1;
    const OperatorMonoid OM0;

    LazySegmentTree(int n, const F f, const G g, const H h,
                                    const Monoid &M1, const OperatorMonoid OM0)
            : f(f), g(g), h(h), M1(M1), OM0(OM0) {
        sz = 1;
        height = 0;
        while(sz < n) sz <<= 1, height++;
        data.assign(2 * sz, M1);
        lazy.assign(2 * sz, OM0);
    }

    LazySegmentTree(const F f, const G g, const H h,
                                    const Monoid &M1, const OperatorMonoid OM0)
            : f(f), g(g), h(h), M1(M1), OM0(OM0) {}

    void set(int k, const Monoid &x) {
        data[k + sz] = x;
    }

    void build() {
        for(int k = sz - 1; k > 0; k--) {
            data[k] = f(data[2 * k + 0], data[2 * k + 1]);
        }
    }

    void build(vector<Monoid> &A) {
        int n = A.size();
        sz = 1;
        height = 0;
        while(sz < n) sz <<= 1, height++;
        data.assign(2 * sz, M1);
        lazy.assign(2 * sz, OM0);
        rep(i, n) set(i, A[i]);
        build();
    }

    inline void propagate(int k) {
        if(lazy[k] == OM0) return;
        lazy[2 * k + 0] = h(lazy[2 * k + 0], lazy[k]);
        lazy[2 * k + 1] = h(lazy[2 * k + 1], lazy[k]);
        data[k] = apply(k);
        lazy[k] = OM0;
    }

    inline Monoid apply(int k) {
        return lazy[k] == OM0 ? data[k] : g(data[k], lazy[k]);
    }

    inline void recalc(int k) {
        while(k >>= 1) data[k] = f(apply(2 * k + 0), apply(2 * k + 1));
    }

    inline void thrust(int k) {
        for(int i = height; i > 0; i--) propagate(k >> i);
    }

    void update(int a, int b, const OperatorMonoid &x) {
        if(a >= b) return;
        thrust(a += sz);
        thrust(b += sz - 1);
        for(int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
            if(l & 1) lazy[l] = h(lazy[l], x), ++l;
            if(r & 1) --r, lazy[r] = h(lazy[r], x);
        }
        recalc(a);
        recalc(b);
    }

    Monoid query(int a, int b) {
        if(a >= b) return M1;
        thrust(a += sz);
        thrust(b += sz - 1);
        Monoid L = M1, R = M1;
        for(int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
            if(l & 1) L = f(L, apply(l++));
            if(r & 1) R = f(apply(--r), R);
        }
        return f(L, R);
    }

    Monoid operator[](const int &k) {
        return query(k, k + 1);
    }

    void update(int i, OperatorMonoid &x) {
        update(i, i+1, x);
    }

    void print(int n) {
        rep(i, n) {
            cout << query(i, i+1);
            if (i == n-1) cout << endl;
            else cout << ' ';
        }
    }

    template<typename C>
    int find_subtree(int a, const C &check, Monoid &M, bool type) {
        while(a < sz) {
            propagate(a);
            Monoid nxt = type ? f(apply(2 * a + type), M) : f(M, apply(2 * a + type));
            if(check(nxt)) a = 2 * a + type;
            else M = nxt, a = 2 * a + 1 - type;
        }
        return a - sz;
    }

    // 区間[a,N)でcheckの条件を満たすような最小位置を返す(なければ-1)
    template<typename C>
    int find_first(int a, const C &check) {
        Monoid L = M1;
        if(a <= 0) {
            if(check(f(L, apply(1)))) return find_subtree(1, check, L, false);
            return -1;
        }
        thrust(a + sz);
        int b = sz;
        for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
            if(a & 1) {
                Monoid nxt = f(L, apply(a));
                if(check(nxt)) return find_subtree(a, check, L, false);
                L = nxt;
                ++a;
            }
        }
        return -1;
    }

    // 区間[0,b)でcheckの条件を満たすような最大位置を返す(なければ-1)
    template<typename C>
    int find_last(int b, const C &check) {
        Monoid R = M1;
        if(b >= sz) {
            if(check(f(apply(1), R))) return find_subtree(1, check, R, true);
            return -1;
        }
        thrust(b + sz - 1);
        int a = sz;
        for(b += sz; a < b; a >>= 1, b >>= 1) {
            if(b & 1) {
                Monoid nxt = f(apply(--b), R);
                if(check(nxt)) return find_subtree(b, check, R, true);
                R = nxt;
            }
        }
        return -1;
    }
};

template<typename F, typename G, typename H, typename T, typename E>
LazySegmentTree<F, G, H, T, E> get_Lazy_segment_tree(const F& f, const G& g, const H& h, const T& ti, const E& ei) {
    return {f, g, h, ti, ei};
}

template<typename F, typename G, typename H, typename T, typename E>
LazySegmentTree<F, G, H, T, E> get_Lazy_segment_tree(int N, const F& f, const G& g, const H& h, const T& ti, const E& ei) {
    return {N, f, g, h, ti, ei};
}


// Li Chao Tree
template<typename T>
struct DynamicLiChaoTree {

    const ll x_low;
    const ll x_high;
    const T id;
    const bool is_min;

    struct Line {
        T a, b;

        Line(T a, T b) : a(a), b(b) {}

        inline T get(ll x) const { return a * x + b; }
    };

    struct Node {
        Line x;
        Node *l, *r;

        Node(const Line &x) : x{x}, l{nullptr}, r{nullptr} {}
    };

    Node *root;

    // x_low,x_highは(多分)半開区間[x_low,x_high)あれば大丈夫
    DynamicLiChaoTree(ll x_low, ll x_high, T id, bool is_min=true) : root{nullptr}, x_low(x_low), x_high(x_high), id(id), is_min(is_min) {}

    Node *add_line(Node *t, Line &x, const ll &l, const ll &r, const T &x_l, const T &x_r) {
        if(!t) return new Node(x);

        T t_l = t->x.get(l), t_r = t->x.get(r);

        if(t_l <= x_l && t_r <= x_r) {
            return t;
        } else if(t_l >= x_l && t_r >= x_r) {
        t->x = x;
            return t;
        } else {
            ll m = (l + r) / 2;
            if(m == r) --m;
            T t_m = t->x.get(m), x_m = x.get(m);
            if(t_m > x_m) {
                swap(t->x, x);
                if(x_l >= t_l) t->l = add_line(t->l, x, l, m, t_l, t_m);
                else t->r = add_line(t->r, x, m + 1, r, t_m + x.a, t_r);
            } else {
                if(t_l >= x_l) t->l = add_line(t->l, x, l, m, x_l, x_m);
                else t->r = add_line(t->r, x, m + 1, r, x_m + x.a, x_r);
            }
            return t;
        }
    }

    void add_line(T a, T b) {
        if (!is_min) a *= -1, b *= -1;
        Line x(a, b);
        root = add_line(root, x, x_low, x_high, x.get(x_low), x.get(x_high));
    }

    Node *add_segment(Node *t, Line &x, const ll &a, const ll &b, const ll &l, const ll &r, const T &x_l, const T &x_r) {
        if(r < a || b < l) return t;
        if(a <= l && r <= b) {
            Line y{x};
            return add_line(t, y, l, r, x_l, x_r);
        }
        if(t) {
            T t_l = t->x.get(l), t_r = t->x.get(r);
            if(t_l <= x_l && t_r <= x_r) return t;
        } else {
            t = new Node(Line(0, id));
        }
        ll m = (l + r) / 2;
        if(m == r) --m;
        T x_m = x.get(m);
        t->l = add_segment(t->l, x, a, b, l, m, x_l, x_m);
        t->r = add_segment(t->r, x, a, b, m + 1, r, x_m + x.a, x_r);
        return t;
    }

    void add_segment(const ll &l, const ll &r, T a, T b) {
        if (!is_min) a *= -1, b *= -1;
        Line x(a, b);
        root = add_segment(root, x, l, r - 1, x_low, x_high, x.get(x_low), x.get(x_high));
    }

    T query(const Node *t, const ll &l, const ll &r, const T &x) const {
        if(!t) return id;
        if(l == r) return t->x.get(x);
        ll m = (l + r) / 2;
        if(m == r) --m;
        if(x <= m) return min(t->x.get(x), query(t->l, l, m, x));
        else return min(t->x.get(x), query(t->r, m + 1, r, x));
    }

    T query(const T &x) const {
        if (is_min) return query(root, x_low, x_high, x);
        return -query(root, x_low, x_high, x);
    }
};


// 完備辞書(Wavelet Matrixとセットで使う)
struct SuccinctIndexableDictionary {
    size_t length;
    size_t blocks;
    vector< unsigned > bit, sum;

    SuccinctIndexableDictionary() = default;

    SuccinctIndexableDictionary(size_t length) : length(length), blocks((length + 31) >> 5) {
        bit.assign(blocks, 0U);
        sum.assign(blocks, 0U);
    }

    void set(int k) {
        bit[k >> 5] |= 1U << (k & 31);
    }

    void build() {
        sum[0] = 0U;
        for(int i = 1; i < blocks; i++) {
        sum[i] = sum[i - 1] + __builtin_popcount(bit[i - 1]);
        }
    }

    bool operator[](int k) {
        return (bool((bit[k >> 5] >> (k & 31)) & 1));
    }

    int rank(int k) {
        return (sum[k >> 5] + __builtin_popcount(bit[k >> 5] & ((1U << (k & 31)) - 1)));
    }

    int rank(bool val, int k) {
        return (val ? rank(k) : k - rank(k));
    }
};

// Wavelet Matrix
template< typename T, int MAXLOG >
struct WaveletMatrix {
    size_t length;
    SuccinctIndexableDictionary matrix[MAXLOG];
    int mid[MAXLOG];

    WaveletMatrix() = default;

    WaveletMatrix(vector< T > v) : length(v.size()) {
        vector< T > l(length), r(length);
        for(int level = MAXLOG - 1; level >= 0; level--) {
        matrix[level] = SuccinctIndexableDictionary(length + 1);
        int left = 0, right = 0;
        for(int i = 0; i < length; i++) {
            if(((v[i] >> level) & 1)) {
            matrix[level].set(i);
            r[right++] = v[i];
            } else {
            l[left++] = v[i];
            }
        }
        mid[level] = left;
        matrix[level].build();
        v.swap(l);
        for(int i = 0; i < right; i++) {
            v[left + i] = r[i];
        }
        }
    }

    pair< int, int > succ(bool f, int l, int r, int level) {
        return {matrix[level].rank(f, l) + mid[level] * f, matrix[level].rank(f, r) + mid[level] * f};
    }

    // v[k]
    T access(int k) {
        T ret = 0;
        for(int level = MAXLOG - 1; level >= 0; level--) {
        bool f = matrix[level][k];
        if(f) ret |= T(1) << level;
        k = matrix[level].rank(f, k) + mid[level] * f;
        }
        return ret;
    }

    T operator[](const int &k) {
        return access(k);
    }

    // count i s.t. (0 <= i < r) && v[i] == x
    int rank(const T &x, int r) {
        int l = 0;
        for(int level = MAXLOG - 1; level >= 0; level--) {
        tie(l, r) = succ((x >> level) & 1, l, r, level);
        }
        return r - l;
    }

    // k-th(0-indexed) smallest number in v[l,r)
    T kth_smallest(int l, int r, int k) {
        assert(0 <= k && k < r - l);
        T ret = 0;
        for(int level = MAXLOG - 1; level >= 0; level--) {
        int cnt = matrix[level].rank(false, r) - matrix[level].rank(false, l);
        bool f = cnt <= k;
        if(f) {
            ret |= T(1) << level;
            k -= cnt;
        }
        tie(l, r) = succ(f, l, r, level);
        }
        return ret;
    }

    // k-th(0-indexed) largest number in v[l,r)
    T kth_largest(int l, int r, int k) {
        return kth_smallest(l, r, r - l - k - 1);
    }

    // count i s.t. (l <= i < r) && (v[i] < upper)
    int range_freq(int l, int r, T upper) {
        int ret = 0;
        for(int level = MAXLOG - 1; level >= 0; level--) {
        bool f = ((upper >> level) & 1);
        if(f) ret += matrix[level].rank(false, r) - matrix[level].rank(false, l);
        tie(l, r) = succ(f, l, r, level);
        }
        return ret;
    }

    // count i s.t. (l <= i < r) && (lower <= v[i] < upper)
    int range_freq(int l, int r, T lower, T upper) {
        return range_freq(l, r, upper) - range_freq(l, r, lower);
    }

    // max v[i] s.t. (l <= i < r) && (v[i] < upper)
    T prev_value(int l, int r, T upper) {
        int cnt = range_freq(l, r, upper);
        return cnt == 0 ? T(-1) : kth_smallest(l, r, cnt - 1);
    }

    // min v[i] s.t. (l <= i < r) && (lower <= v[i])
    T next_value(int l, int r, T lower) {
        int cnt = range_freq(l, r, lower);
        return cnt == r - l ? T(-1) : kth_smallest(l, r, cnt);
    }
    };

    template< typename T, int MAXLOG >
    struct CompressedWaveletMatrix {
    WaveletMatrix< int, MAXLOG > mat;
    vector< T > ys;

    CompressedWaveletMatrix(const vector< T > &v) : ys(v) {
        sort(begin(ys), end(ys));
        ys.erase(unique(begin(ys), end(ys)), end(ys));
        vector< int > t(v.size());
        for(int i = 0; i < v.size(); i++) t[i] = get(v[i]);
        mat = WaveletMatrix< int, MAXLOG >(t);
    }

    inline int get(const T& x) {
        return lower_bound(begin(ys), end(ys), x) - begin(ys);
    }

    T access(int k) {
        return ys[mat.access(k)];
    }

    T operator[](const int &k) {
        return access(k);
    }

    int rank(const T &x, int r) {
        auto pos = get(x);
        if(pos == ys.size() || ys[pos] != x) return 0;
        return mat.rank(pos, r);
    }

    T kth_smallest(int l, int r, int k) {
        return ys[mat.kth_smallest(l, r, k)];
    }

    T kth_largest(int l, int r, int k) {
        return ys[mat.kth_largest(l, r, k)];
    }

    int range_freq(int l, int r, T upper) {
        return mat.range_freq(l, r, get(upper));
    }

    int range_freq(int l, int r, T lower, T upper) {
        return mat.range_freq(l, r, get(lower), get(upper));
    }

    T prev_value(int l, int r, T upper) {
        auto ret = mat.prev_value(l, r, get(upper));
        return ret == -1 ? T(-1) : ys[ret];
    }

    T next_value(int l, int r, T lower) {
        auto ret = mat.next_value(l, r, get(lower));
        return ret == -1 ? T(-1) : ys[ret];
    }
};


// Segment Tree Beats
template<class T> class SegmentTreeBeats {
    T inf;
    size_t length;
    vector<T>
    node_max_first,node_max_second,count_max_first,
    node_min_first,node_min_second,count_min_first,
    node_sum,lazy_add,lazy_update;
    vector<pair<int,int>> range;
    stack<int> down,up;
    inline void internal_chmax(int k, long long x) {
        node_sum[k] += (x - node_max_first[k]) * count_max_first[k];
        if(node_max_first[k] == node_min_first[k]) node_max_first[k] = node_min_first[k] = x;
        else if(node_max_first[k] == node_min_second[k]) node_max_first[k] = node_min_second[k] = x;
        else node_max_first[k] = x;
        if(lazy_update[k] != inf && x < lazy_update[k]) lazy_update[k] = x;
    }
    inline void internal_chmin(int k, long long x) {
        node_sum[k] += (x - node_min_first[k]) * count_min_first[k];
        if(node_max_first[k] == node_min_first[k]) node_max_first[k] = node_min_first[k] = x;
        else if(node_max_second[k] == node_min_first[k]) node_min_first[k] = node_max_second[k] = x;
        else node_min_first[k] = x;
        if(lazy_update[k] != inf && lazy_update[k] < x) lazy_update[k] = x;
    }
    inline void internal_add(int k, long long x) {
        node_max_first[k] += x;
        if(node_max_second[k] != -inf) node_max_second[k] += x;
        node_min_first[k] += x;
        if(node_min_second[k] != inf) node_min_second[k] += x;
        node_sum[k] += x * (range[k].second - range[k].first);
        (lazy_update[k] != inf ? lazy_update[k]:lazy_add[k]) += x;
    }
    inline void internal_update(int k, long long x) {
        node_max_first[k] = x; node_max_second[k] = -inf;
        node_min_first[k] = x; node_min_second[k] = inf;
        count_max_first[k] = count_min_first[k] = (range[k].second - range[k].first);
        node_sum[k] = x * (range[k].second - range[k].first);
        lazy_update[k] = x;
        lazy_add[k] = 0;
    }
    inline void propagate(int k) {
        if(length-1 <= k) return;
        if(lazy_update[k] != inf) {
            internal_update(2*k+0, lazy_update[k]);
            internal_update(2*k+1, lazy_update[k]);
            lazy_update[k] = inf;
            return;
        }
        if(lazy_add[k] != 0) {
            internal_add(2*k+0, lazy_add[k]);
            internal_add(2*k+1, lazy_add[k]);
            lazy_add[k] = 0;
        }
        if(node_max_first[k] < node_max_first[2*k+0]) {
            internal_chmax(2*k+0, node_max_first[k]);
        }
        if(node_min_first[2*k+0] < node_min_first[k]) {
            internal_chmin(2*k+0, node_min_first[k]);
        }
        if(node_max_first[k] < node_max_first[2*k+1]) {
            internal_chmax(2*k+1, node_max_first[k]);
        }
        if(node_min_first[2*k+1] < node_min_first[k]) {
            internal_chmin(2*k+1, node_min_first[k]);
        }
    }
    inline void merge(int k) {
        node_sum[k] = node_sum[2*k+0] + node_sum[2*k+1];
        if(node_max_first[2*k+0] < node_max_first[2*k+1]) {
            node_max_first[k] = node_max_first[2*k+1];
            count_max_first[k] = count_max_first[2*k+1];
            node_max_second[k] = max(node_max_first[2*k+0], node_max_second[2*k+1]);
        }
        else if(node_max_first[2*k+0] > node_max_first[2*k+1]) {
            node_max_first[k] = node_max_first[2*k+0];
            count_max_first[k] = count_max_first[2*k+0];
            node_max_second[k] = max(node_max_second[2*k+0], node_max_first[2*k+1]);
        }
        else {
            node_max_first[k] = node_max_first[2*k+0];
            count_max_first[k] = count_max_first[2*k+0] + count_max_first[2*k+1];
            node_max_second[k] = max(node_max_second[2*k+0], node_max_second[2*k+1]);
        }
        if(node_min_first[2*k+0] < node_min_first[2*k+1]) {
            node_min_first[k] = node_min_first[2*k+0];
            count_min_first[k] = count_min_first[2*k+0];
            node_min_second[k] = min(node_min_second[2*k+0], node_min_first[2*k+1]);
        }
        else if(node_min_first[2*k+0] > node_min_first[2*k+1]) {
            node_min_first[k] = node_min_first[2*k+1];
            count_min_first[k] = count_min_first[2*k+1];
            node_min_second[k] = min(node_min_first[2*k+0], node_min_second[2*k+1]);
        }
        else {
            node_min_first[k] = node_min_first[2*k+0];
            count_min_first[k] = count_min_first[2*k+0] + count_min_first[2*k+1];
            node_min_second[k] = min(node_min_second[2*k+0], node_min_second[2*k+1]);
        }
    }
    inline void up_merge(void){
        while(up.size()) {
            merge(up.top());
            up.pop();
        }
    }
    inline void down_propagate(const int& k) {
        propagate(k);
        down.push(2*k+0);
        down.push(2*k+1);
    }
public:
    SegmentTreeBeats(const int num,const T inf = (1LL<<60)) {
        vector<T> a(num,0);
        *this = SegmentTreeBeats(a,inf);
    }
    SegmentTreeBeats(const vector<T>& a,const T inf = (1LL<<60)) : inf(inf){
        int num = a.size();
        for (length = 1; length <= num; length *= 2);
        node_max_first.resize(2*length);
        node_max_second.resize(2*length);
        count_max_first.resize(2*length);
        node_min_first.resize(2*length);
        node_min_second.resize(2*length);
        count_min_first.resize(2*length);
        node_sum.resize(2*length);
        range.resize(2*length);
        lazy_add.resize(2*length);
        lazy_update.resize(2*length);

        for(int i=0; i<2*length; ++i) lazy_add[i] = 0, lazy_update[i] = inf;
        for(int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
        for(int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);

        for(int i=0; i<num; ++i) {
            node_max_first[length+i] = node_min_first[length+i] = node_sum[length+i] = a[i];
            node_max_second[length+i] = -inf;
            node_min_second[length+i] = inf;
            count_max_first[length+i] = count_min_first[length+i] = 1;
        }
        for(int i=num; i<length; ++i) {
            node_max_first[length+i] = node_max_second[length+i] = -inf;
            node_min_first[length+i] = node_min_second[length+i] = inf;
            count_max_first[length+i] = count_min_first[length+i] = 0;
        }
        for(int i=length-1; i; --i) merge(i);
    }
    inline void range_chmin(int a, int b, long long x) {
        down.push(1);
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a || node_max_first[k] <= x) continue;
            if(a <= range[k].first && range[k].second <= b && node_max_second[k] < x) {
                internal_chmax(k, x);
                continue;
            }
            down_propagate(k);
            up.push(k);
        }
        up_merge();
    }
    inline void range_chmax(int a, int b, long long x,int k = 1) {
        down.push(1);
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a || x <= node_min_first[k]) continue;
            if(a <= range[k].first && range[k].second <= b && x < node_min_second[k]) {
                internal_chmin(k, x);
                continue;
            }
            down_propagate(k);
            up.push(k);
        }
        up_merge();
    }
    inline void range_add(int a, int b, long long x,int k = 1) {
        down.push(1);
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a) continue;
            if(a <= range[k].first && range[k].second <= b) {
                internal_add(k, x);
                continue;
            }
            down_propagate(k);
            up.push(k);
        }
        up_merge();
    }
    inline void range_update(int a, int b, long long x,int k = 1) {
        down.push(1);
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a) continue;
            if(a <= range[k].first && range[k].second <= b) {
                internal_update(k, x);
                continue;
            }
            down_propagate(k);
            up.push(k);
        }
        up_merge();
    }
    inline T get_max(int a, int b, int k = 1) {
        down.push(1);
        long long v = inf;
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a) continue;
            if(a <= range[k].first && range[k].second <= b) {
                v = max(v,node_max_first[k]);
                continue;
            }
            down_propagate(k);
        }
        return v;
    }
    inline T get_min(int a, int b, int k = 1) {
        down.push(1);
        long long v = inf;
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a) continue;
            if(a <= range[k].first && range[k].second <= b) {
                v = min(v,node_min_first[k]);
                continue;
            }
            down_propagate(k);
        }
        return v;
    }
    inline T get_sum(int a, int b, int k = 1) {
        down.push(1);
        long long v = 0;
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a) continue;
            if(a <= range[k].first && range[k].second <= b) {
                v += node_sum[k];
                continue;
            }
            down_propagate(k);
        }
        return v;
    }

    T get(int i) {
        return get_sum(i, i+1);
    }

    T operator[](int i) {
        return get(i);
    }

    void update(int i, T x) {
        range_update(i, i+1, x);
    }

    void add(int i, T x) {
        range_add(i, i+1, x);
    }
};


struct Mo {
    int n;
    vector< pair< int, int > > lr;

    explicit Mo(int n) : n(n) {}

    // クエリを半開区間[l,r)で順番に追加
    void add(int l, int r) {
        lr.emplace_back(l, r);
    }

    template< typename AL, typename AR, typename EL, typename ER, typename O >
    void build(const AL &add_left, const AR &add_right, const EL &erase_left, const ER &erase_right, const O &out) {
        int q = (int) lr.size();
        int bs = n / min< int >(n, sqrt(q));
        vector< int > ord(q);
        iota(begin(ord), end(ord), 0);
        sort(begin(ord), end(ord), [&](int a, int b) {
            int ablock = lr[a].first / bs, bblock = lr[b].first / bs;
            if(ablock != bblock) return ablock < bblock;
            return (ablock & 1) ? lr[a].second > lr[b].second : lr[a].second < lr[b].second;
        });
        int l = 0, r = 0;
        for(auto idx : ord) {
            while(l > lr[idx].first) add_left(--l);
            while(r < lr[idx].second) add_right(r++);
            while(l < lr[idx].first) erase_left(l++);
            while(r > lr[idx].second) erase_right(--r);
            out(idx);
        }
    }

    // add:   区間が伸びる時の処理(引数はmoのindex)
    // erase: 区間が縮む時の処理(引数はmoのindex)
    // out:   クエリに回答する処理(引数はクエリのindex)
    // 伸縮時に左右で処理に違いがなければadd,eraseは1つずつでOK
    template< typename A, typename E, typename O >
    void build(const A &add, const E &erase, const O &out) {
        build(add, add, erase, erase, out);
    }
};


// スライド最小値(比較関数、元の数列、遷移回数、遷移幅、遷移の重み)
template<typename T, typename F>
vector<T> slide_min(const F &func, vector<T> &A, ll k, ll w=1, ll v=0) {

    ll N = A.size();
    auto res = A;
    rep(a, 0, w) {
        deque<pair<int, T>> que;
        int i = 0;
        while (i*w+a < N) {
            ll val = A[i*w+a] - i*v;
            while (!que.empty() and func(que.back().second, val) == val) {
                que.pop_back();
            }
            que.pb({i, val});
            res[i*w+a] = que.front().second + i*v;
            if (que.front().first == i-k) {
                que.pop_front();
            }
            i++;
        }
    }
    return res;
}


// マージソートによる転倒数取得
// 座圧BITより速いけど、参照渡しやめるとバグるので、
// 元の列もまだ使う場合はコピーしてからやる。
ll get_inversion(vector<ll> &a) {
    int n = a.size();
    if (n <= 1) { return 0; }

    ll cnt = 0;
    vector<ll> b(a.begin(), a.begin()+n/2);
    vector<ll> c(a.begin()+n/2, a.end());

    cnt += get_inversion(b);
    cnt += get_inversion(c);

    int ai = 0, bi = 0, ci = 0;
    // merge の処理
    while (ai < n) {
        if ( bi < b.size() && (ci == c.size() || b[bi] <= c[ci]) ) {
            a[ai++] = b[bi++];
        } else {
            cnt += n / 2 - bi;
            a[ai++] = c[ci++];
        }
    }
    return cnt;
}


// 2つの閉区間seg1,seg2から、重複を除いた長さを返す
ll merge_segment(pll seg1, pll seg2) {
    auto& [l1, r1] = seg1;
    auto& [l2, r2] = seg2;
    if (l1 > l2) {
        swap(l1, l2);
        swap(r1, r2);
    }
    ll ln1 = r1-l1+1;
    ll ln2 = r2-l2+1;
    if (ln1 <= 0 and ln2 <= 0) {
        return 0;
    } elif (ln2 <= 0 or l2 <= r1 and r2 <= r1) {
        return ln1;
    } elif (l2 <= r1 and r2 > r1) {
        return ln1 + ln2 - (r1-l2+1);
    } else {
        return ln1 + ln2;
    }
}


// 閉区間の範囲を管理
template<typename T>
struct RangeSet{
    set<pair<T,T>> st;
    T TINF;
 
    RangeSet(){
        TINF=numeric_limits<T>::max()/2;
        st.emplace(TINF,TINF);
        st.emplace(-TINF,-TINF);
    }
    // [l,r] covered?
    bool covered(T l,T r){
        assert(l<=r);
        auto ite=prev(st.lower_bound({l+1,l+1}));
        return ite->first<=l and r<=ite->second;
    }
    bool covered(T x){
        return covered(x,x);
    }
    // [l, r]がカバーされているなら，その区間を返す. されていないなら[-TINF,-TINF]を返す
    pair<T,T> covered_by(T l,T r){
        assert(l<=r);
        auto ite=prev(st.lower_bound({l+1,l+1}));
        if(ite->first<=l and r<=ite->second) return *ite;
        return make_pair(-TINF,-TINF);
    }
    pair<T,T> covered_by(T x){
        return covered_by(x,x);
    }
    // insert[l,r], 増加量を返す
    T insert(T l,T r){
        assert(l<=r);
        auto ite=prev(st.lower_bound({l+1,l+1}));
        if(ite->first<=l and r<=ite->second) return T(0);
        T sum_erased=T(0);
        if(ite->first<=l and l<=ite->second+1){
            l=ite->first;
            sum_erased+=ite->second-ite->first+1;
            ite=st.erase(ite);
        }else ite=next(ite);
        while(r>ite->second){
            sum_erased+=ite->second-ite->first+1;
            ite=st.erase(ite);
        }
        if(ite->first-1<=r and r<=ite->second){
            sum_erased+=ite->second-ite->first+1;
            r=ite->second;
            st.erase(ite);
        }
        st.emplace(l,r);
        return r-l+1-sum_erased;
    }
    T insert(T x){
        return insert(x,x);
    }
    // erase [l,r], 減少量を返す
    T erase(T l,T r){
        assert(l<=r);
        auto ite=prev(st.lower_bound({l+1,l+1}));
        if(ite->first<=l and r<=ite->second){
            // 完全に1つの区間に包含されている
            if(ite->first<l)  st.emplace(ite->first,l-1);
            if(r<ite->second) st.emplace(r+1,ite->second);
            st.erase(ite);
            return r-l+1;
        }
 
        T ret=T(0);
        if(ite->first<=l and l<=ite->second){
            ret+=ite->second-l+1;// 消えた
            if(ite->first<l) st.emplace(ite->first,l-1);
            ite=st.erase(ite);// 次へ
        }else ite=next(ite);
        while(ite->second<=r){
            ret+=ite->second-ite->first+1;
            ite=st.erase(ite);
        }
        // 右端が区間の間にあるか
        if(ite->first<=r and r<=ite->second){
            ret+=r-ite->first+1;
            if(r<ite->second) st.emplace(r+1,ite->second);
            st.erase(ite);
        }
        return ret;
    }
    T erase(T x){
        return erase(x,x);
    }
    // number of range
    int size(){
        return (int)st.size()-2;
    }
    // mex [x,~)
    int mex(T x=0){
        auto ite=prev(st.lower_bound({x+1,x+1}));
        if(ite->first<=x and x<=ite->second) return ite->second+1;
        else return x;
    }
    void output(){
        cout<<"RangeSet : ";
        for(auto &p:st){
            if(p.first==-TINF or p.second==TINF) continue;
            cout<<"["<<p.first<<", "<<p.second<<"] ";
        }
        cout<<"\n";
    }
};
