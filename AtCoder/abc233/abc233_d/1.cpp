/*
・なんとか自力AC。。
・累積和、Wavelet Matrix
・累積和を取ると、自分より後ろで値が自身+Kの場所を数えられればいい。
　これはWMを使うと殴れるんだけど、負数が使えないので、
　全部正数になるように位置調整する。ってやったんだけど、
　acc[i]+Kにした時負数になるやつを考慮してなくてWAを連発…。
　なんとか通せたけど時間かかりすぎたしこれは反省。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/template.hpp"

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

void solve() {
    ll N, K;
    cin >> N >> K;
    auto A = LIST(N);

    vector<ll> acc(N+1);
    rep(i, N) {
        acc[i+1] = acc[i]+A[i];
    }
    ll need = max(0-min(acc), 0LL);
    vector<ll> tmp(N+1);
    rep(i, N+1) {
        acc[i] += need;
    }
    WaveletMatrix<ll, 60> wm(acc);

    ll ans = 0;
    rep(i, N) {
        need = acc[i]+K;
        if (need < 0) continue;
        ans += wm.range_freq(i+1, N+1, need, need+1);
    }
    print(ans);
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
