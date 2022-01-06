#include "../base.hpp"

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

    void build(const vector<Monoid> &A) {
        int n = A.size();
        resize(n);
        for (int i=0; i<n; i++) set(i, A[i]);
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
        for (int i=0; i<n; i++) {
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
