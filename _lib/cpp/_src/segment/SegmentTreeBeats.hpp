#include "../macros.hpp"

// Segment Tree Beats
class SegmentTreeBeats {
    static const ll inf = 1e18;
    struct Node {
        Node *left, *right;
        ll max_v, smax_v, max_c;
        ll min_v, smin_v, min_c;
        ll sum;
        ll len, ladd, lval;
 
        Node() : left(0), right(0), ladd(0), lval(inf) {}
 
        void init(ll x) {
            max_v = min_v = sum = x;
            smax_v = -inf;
            smin_v = inf;
            max_c = min_c = 1;
        }
 
        void init_empty() {
            max_v = smax_v = -inf;
            min_v = smin_v = inf;
            max_c = min_c = 0;
        }
 
        void update_max(ll x) {
            sum += (x - max_v) * max_c;
 
            if (max_v == min_v) {
                max_v = min_v = x;
            } else if (max_v == smin_v) {
                max_v = smin_v = x;
            } else {
                max_v = x;
            }
 
            if (lval != inf && x < lval) {
                lval = x;
            }
        }
 
        void update_min(ll x) {
            sum += (x - min_v) * min_c;
 
            if (max_v == min_v) {
                max_v = min_v = x;
            } else if (max_v == smin_v) {
                min_v = smax_v = x;
            } else {
                min_v = x;
            }
 
            if (lval != inf && lval < x) {
                lval = x;
            }
        }
 
        void addall(ll x) {
            max_v += x;
            if (smax_v != -inf) smax_v += x;
            min_v += x;
            if (smin_v != inf) smin_v += x;
 
            sum += len * x;
            if (lval != inf) {
                lval += x;
            } else {
                ladd += x;
            }
        }
 
        void updateall(ll x) {
            max_v = min_v = x;
            smax_v = -inf;
            smin_v = inf;
            max_c = min_c = len;
 
            sum = len * x;
            lval = x;
            ladd = 0;
        }
 
        void push() {
            if (lval != inf) {
                left->updateall(lval);
                right->updateall(lval);
                lval = inf;
                return;
            }
 
            if (ladd != 0) {
                left->addall(ladd);
                right->addall(ladd);
                ladd = 0;
            }
 
            if (max_v < left->max_v) {
                left->update_max(max_v);
            }
            if (left->min_v < min_v) {
                left->update_min(min_v);
            }
 
            if (max_v < right->max_v) {
                right->update_max(max_v);
            }
            if (right->min_v < min_v) {
                right->update_min(min_v);
            }
        }
 
        void update() {
            sum = left->sum + right->sum;
 
            if (left->max_v < right->max_v) {
                max_v = right->max_v;
                max_c = right->max_c;
                smax_v = max(left->max_v, right->smax_v);
            } else if (left->max_v > right->max_v) {
                max_v = left->max_v;
                max_c = left->max_c;
                smax_v = max(left->smax_v, right->max_v);
            } else {
                max_v = left->max_v;
                max_c = left->max_c + right->max_c;
                smax_v = max(left->smax_v, right->smax_v);
            }
 
            if (left->min_v < right->min_v) {
                min_v = left->min_v;
                min_c = left->min_c;
                smin_v = min(left->smin_v, right->min_v);
            } else if (left->min_v > right->min_v) {
                min_v = right->min_v;
                min_c = right->min_c;
                smin_v = min(left->min_v, right->smin_v);
            } else {
                min_v = left->min_v;
                min_c = left->min_c + right->min_c;
                smin_v = min(left->smin_v, right->smin_v);
            }
        }
    };
 
    int n, n0;
    Node *root;
 
    void _update_min(ll x, int a, int b, Node *nd, int l, int r) {
        if (b <= l || r <= a || nd->max_v <= x) {
            return;
        }
        if (a <= l && r <= b && nd->smax_v < x) {
            nd->update_max(x);
            return;
        }
 
        nd->push();
        _update_min(x, a, b, nd->left, l, (l + r) / 2);
        _update_min(x, a, b, nd->right, (l + r) / 2, r);
        nd->update();
    }
 
    void _update_max(ll x, int a, int b, Node *nd, int l, int r) {
        if (b <= l || r <= a || x <= nd->min_v) {
            return;
        }
        if (a <= l && r <= b && x < nd->smin_v) {
            nd->update_min(x);
            return;
        }
 
        nd->push();
        _update_max(x, a, b, nd->left, l, (l + r) / 2);
        _update_max(x, a, b, nd->right, (l + r) / 2, r);
        nd->update();
    }
 
    void _add_val(ll x, int a, int b, Node *nd, int l, int r) {
        if (b <= l || r <= a) {
            return;
        }
        if (a <= l && r <= b) {
            nd->addall(x);
            return;
        }
 
        nd->push();
        _add_val(x, a, b, nd->left, l, (l + r) / 2);
        _add_val(x, a, b, nd->right, (l + r) / 2, r);
        nd->update();
    }
 
    void _update_val(ll x, int a, int b, Node *nd, int l, int r) {
        if (b <= l || r <= a) {
            return;
        }
        if (a <= l && r <= b) {
            nd->updateall(x);
            return;
        }
 
        nd->push();
        _update_val(x, a, b, nd->left, l, (l + r) / 2);
        _update_val(x, a, b, nd->right, (l + r) / 2, r);
        nd->update();
    }
 
    ll _query_max(int a, int b, Node *nd, int l, int r) {
        if (b <= l || r <= a) {
            return -inf;
        }
        if (a <= l && r <= b) {
            return nd->max_v;
        }
        nd->push();
        ll lv = _query_max(a, b, nd->left, l, (l + r) / 2);
        ll rv = _query_max(a, b, nd->right, (l + r) / 2, r);
        return max(lv, rv);
    }
 
    ll _query_min(int a, int b, Node *nd, int l, int r) {
        if (b <= l || r <= a) {
            return inf;
        }
        if (a <= l && r <= b) {
            return nd->min_v;
        }
        nd->push();
        ll lv = _query_min(a, b, nd->left, l, (l + r) / 2);
        ll rv = _query_min(a, b, nd->right, (l + r) / 2, r);
        return min(lv, rv);
    }
 
    ll _query_sum(int a, int b, Node *nd, int l, int r) {
        if (b <= l || r <= a) {
            return 0;
        }
        if (a <= l && r <= b) {
            return nd->sum;
        }
        nd->push();
        ll lv = _query_sum(a, b, nd->left, l, (l + r) / 2);
        ll rv = _query_sum(a, b, nd->right, (l + r) / 2, r);
        return lv + rv;
    }
 
public:
    SegmentTreeBeats(vector<ll> a) : n(a.size()) {
        n0 = 1;
        while (n0 < n) n0 <<= 1;
 
        Node *nds = new Node[2 * n0];
        root = nds;
 
        nds[0].len = n0;
        for (int i = 0; i < n0 - 1; ++i) {
            nds[i].left = &nds[2 * i + 1];
            nds[i].right = &nds[2 * i + 2];
            nds[2 * i + 1].len = nds[2 * i + 2].len = (nds[i].len >> 1);
        }
 
        for (int i = 0; i < n; ++i) nds[n0 - 1 + i].init(a[i]);
        for (int i = n; i < n0; ++i) nds[n0 - 1 + i].init_empty();
        for (int i = n0 - 2; i >= 0; i--) nds[i].update();
    }
    SegmentTreeBeats(int n) : SegmentTreeBeats(vector<ll>(n, 0)) {}
 
    void update_min(int a, int b, ll x) { _update_min(x, a, b, root, 0, n0); }
 
    void update_max(int a, int b, ll x) { _update_max(x, a, b, root, 0, n0); }
 
    void add_val(int a, int b, ll x) { _add_val(x, a, b, root, 0, n0); }
 
    void update_val(int a, int b, ll x) { _update_val(x, a, b, root, 0, n0); }
 
    ll query_max(int a, int b) { return _query_max(a, b, root, 0, n0); }
 
    ll query_min(int a, int b) { return _query_min(a, b, root, 0, n0); }
 
    ll query_sum(int a, int b) { return _query_sum(a, b, root, 0, n0); }

    ll get(int i) {
        return query_sum(i, i+1);
    }

    ll operator[](int i) {
        return query_sum(i, i+1);
    }

    void update(int i, ll x) {
        update_val(i, i+1, x);
    }

    void add(int i, ll x) {
        add_val(i, i+1, x);
    }

    void print(int n) {
        rep(i, n) {
            cout << query_sum(i, i+1);
            if (i == n-1) cout << endl;
            else cout << ' ';
        }
    }
};
