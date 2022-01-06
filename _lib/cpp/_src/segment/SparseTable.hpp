#include "../macros.hpp"

// スパーステーブル：構築にO(NlogN)、区間最小(最大)をO(1)で取得
template<typename T, typename F>
struct SparseTable {

    const F f;
    vector<vector<T>> dat;
    vector<ll> height;

    SparseTable(const F f) : f(f) {}

    SparseTable(const vector<T> &A, const F f) : f(f) {
        build(A);
    }

    void build(const vector<T> &A) {
        ll N = A.size();

        ll h = 0;
        while ((1<<h) <= N) {
            h++;
        }
        dat.resize(h);
        rep(i, h) dat[i].resize(1<<h);
        height.resize(N+1);

        rep(i, 2, N+1) {
            height[i] = height[i>>1] + 1;
        }
        rep(i, N) {
            dat[0][i] = A[i];
        }
        rep(i, 1, h) {
            rep(j, N) {
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
