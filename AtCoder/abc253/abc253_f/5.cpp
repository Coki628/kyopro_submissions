/*
・ライブラリ整備：永続セグメント木、永続配列
・単純にセグ木の中で持つ配列を永続配列に置き換えてみた。
　速度もまあ遅いけど、何よりメモリが無理になる。。
　で、結局時系列管理に必要なのって本体というよりその時のルートノードなので、
　ルートノードのポインタだけ返す版も作ってみたんだけど、
　実体コピーするのとメモリ消費変わらんかったんだよね。。
　コピーのコストというより、永続配列を持ったセグ木で20万回とかの更新処理が走るのがつらいっぽい。
　(多分配列の更新の度にノードが増えちゃうので)
・一応、ポインタだけ保持する版も取っておく。
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

#include "common/PersistentArray.hpp"

template<typename Monoid, typename F>
struct PersistentSegmentTree {

    int sz;
    // vector<Monoid> seg;
    PersistentArray<Monoid, 3> seg;
    // ここにtypename付けるとなんか動く、ないと動かない
    using NP = typename PersistentArray<Monoid, 3>::Node*;

    // constなメンバーがいると暗黙コピーができない
    F f;
    Monoid M1;

    PersistentSegmentTree() = default;

    PersistentSegmentTree(int n, const F f, const Monoid &M1) : f(f), M1(M1) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.build(vector<Monoid>(2*sz, M1));
        // seg.assign(2 * sz, M1);
    }

    PersistentSegmentTree(const F f, const Monoid &M1) : f(f), M1(M1) {}

    PersistentSegmentTree(const vector<Monoid>& A, const F f, const Monoid &M1) : f(f), M1(M1) {
        build(A);
    }

    void resize(int n) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.build(vector<Monoid>(2*sz, M1));
        // seg.resize(2 * sz, M1);
    }

    void clear() {
        seg.clear();
    }

    void set(int k, const Monoid &x) {
        seg.update(k+sz, x);
        // seg[k+sz] = x;
    }

    void build() {
        for(int k = sz - 1; k > 0; k--) {
            seg.update(k, f(seg.get(2*k), seg.get(2*k+1)));
            // seg[k] = f(seg[2*k], seg[2*k+1]);
        }
    }

    void build(const vector<Monoid> &A) {
        int n = A.size();
        resize(n);
        rep(i, n) set(i, A[i]);
        build();
    }

    void update(int k, const Monoid &x) {
        k += sz;
        seg.update(k, x);
        // seg[k] = x;
        while(k >>= 1) {
            seg.update(k, f(seg.get(2*k), seg.get(2*k+1)));
            // seg[k] = f(seg[2*k], seg[2*k+1]);
        }
    }

    Monoid query(int a, int b) {
        Monoid L = M1, R = M1;
        for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
            if(a & 1) L = f(L, seg.get(a++));
            if(b & 1) R = f(seg.get(--b), R);
            // if(a & 1) L = f(L, seg[a++]);
            // if(b & 1) R = f(seg[--b], R);
        }
        return f(L, R);
    }

    Monoid operator[](int k) {
        return seg.get(k+sz);
        // return seg[k+sz];
    }

    Monoid all() {
        return seg.get(1);
        // return seg[1];
    }

    void print(int n) {
        for (int i=0; i<n; i++) {
            cout << query(i, i+1);
            if (i == n-1) cout << endl;
            else cout << ' ';
        }
    }

    template<typename C>
    int find_subtree(int a, const C &check, Monoid &M, bool type) {
        while(a < sz) {
            Monoid nxt = type ? f(seg.get(2*a+type), M) : f(M, seg.get(2*a+type));
            // Monoid nxt = type ? f(seg[2 * a + type], M) : f(M, seg[2 * a + type]);
            if(check(nxt)) a = 2 * a + type;
            else M = nxt, a = 2 * a + 1 - type;
        }
        return a - sz;
    }

    // 範囲[a,N)でcheckの条件を満たすような最小位置を返す(なければ-1)
    template<typename C>
    int find_first(int a, const C &check) {
        Monoid L = M1;
        if(a <= 0) {
            if(check(f(L, seg.get(1)))) return find_subtree(1, check, L, false);
            // if(check(f(L, seg[1]))) return find_subtree(1, check, L, false);
            return -1;
        }
        int b = sz;
        for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
            if(a & 1) {
                Monoid nxt = f(L, seg.get(a));
                // Monoid nxt = f(L, seg[a]);
                if(check(nxt)) return find_subtree(a, check, L, false);
                L = nxt;
                ++a;
            }
        }
        return -1;
    }

    // 範囲[0,b)でcheckの条件を満たすような最大位置を返す(なければ-1)
    template<typename C>
    int find_last(int b, const C &check) {
        Monoid R = M1;
        if(b >= sz) {
            if(check(f(seg.get(1), R))) return find_subtree(1, check, R, true);
            // if(check(f(seg[1], R))) return find_subtree(1, check, R, true);
            return -1;
        }
        int a = sz;
        for(b += sz; a < b; a >>= 1, b >>= 1) {
            if(b & 1) {
                Monoid nxt = f(seg.get(--b), R);
                // Monoid nxt = f(seg[--b], R);
                if(check(nxt)) return find_subtree(b, check, R, true);
                R = nxt;
            }
        }
        return -1;
    }

    NP get_root_node() {
        return seg.root;
    }

    void set_root_node(NP np) {
        seg.root = np;
    }
};

template<typename Monoid, typename F>
PersistentSegmentTree<Monoid, F> get_persistent_segment_tree(int N, const F& f, const Monoid& M1) {
    return {N, f, M1};
}

template<typename Monoid, typename F>
PersistentSegmentTree<Monoid, F> get_persistent_segment_tree(const F& f, const Monoid& M1) {
    return {f, M1};
}

template<typename Monoid, typename F>
PersistentSegmentTree<Monoid, F> get_persistent_segment_tree(const vector<Monoid>& A, const F& f, const Monoid& M1) {
    return {A, f, M1};
}

const auto f = [](ll a, ll b) { return a + b; };

void solve() {
    ll H, W, Q;
    cin >> H >> W >> Q;

    vector<PersistentArray<ll, 3>::Node*> history(Q);
    auto seg = get_persistent_segment_tree(f, 0LL);
    seg.build(vector<ll>(W+1, 0));
    vector<pll> upd(H);
    rep(i, Q) {
        history[i] = seg.get_root_node();
        ll op;
        cin >> op;
        if (op == 1) {
            ll wl, wr, x;
            cin >> wl >> wr >> x;
            wl--;

            seg.update(wl, seg[wl]+x);
            seg.update(wr, seg[wr]-x);
        } elif (op == 2) {
            ll h, x;
            cin >> h >> x;
            h--;

            upd[h] = {i, x};
            
        } else {
            ll h, w;
            cin >> h >> w;
            h--; w--;

            ll res = upd[h].second + seg.query(0, w+1);
            seg.set_root_node(history[upd[h].first]);
            res -= seg.query(0, w+1);
            seg.set_root_node(history[i]);
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
