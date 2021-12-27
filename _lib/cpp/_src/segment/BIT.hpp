#include "../macros.hpp"

// Binary Indexed Tree
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
        return query(i, i+1);
    }

    void print(int n) {
        rep(i, n) {
            cout << query(i, i+1);
            if (i == n-1) cout << endl;
            else cout << ' ';
        }
    }

    // 区間[l, r]を左から右に向かってx番目の値がある位置
    ll bisearch_fore(int l, int r, ll x) {
        if (l > r) return -1;
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
        if (l > r) return -1;
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
        if (ok != l-1) {
            return ok;
        } else {
            return -1;
        }
    }
};
