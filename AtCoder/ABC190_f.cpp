/**
 * ・オーバーフローにドハマりして時間内ACならず。。。なんで for (int a : ans) とかしたんだ。。
 * ・BIT、転倒数数え上げ
 * ・2回目以降は差分が1個だけなので、その分だけ再計算すればいいやつ。
 * 　区間内[l:r)内でx未満の、みたいなのを探すのに、wavelet matrixでぶん殴り。。O(1)でよかったんだね。
 * ・それはいいんだけど今回はオーバーフローに反省。たまにしかint使わないのにたまにやらかすのつらい。。
 */

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
using vvl = vector<vector<ll>>;
using vvi = vector<vector<int>>;
using vvpll = vector<vector<pll>>;
#define rep(i, a, b) for (ll i=(a); i<(b); i++)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define tostr to_string
#define ALL(A) A.begin(), A.end()
#define elif else if
// constexpr ll INF = LONG_LONG_MAX;
constexpr ll INF = 1e18;
constexpr ll MOD = 1000000007;

const string digits = "0123456789";
const string ascii_lowercase = "abcdefghijklmnopqrstuvwxyz";
const string ascii_uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string ascii_letters = ascii_lowercase + ascii_uppercase;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { return vector<vector<T>>(N, vector<T>(M, init)); }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { return vector<vector<vector<T>>>(N, vector<vector<T>>(M, vector<T>(L, init))); }
template<typename T> vector<vector<vector<vector<T>>>> list4d(int N, int M, int L, int O, T init) { return vector<vector<vector<vector<T>>>>(N, vector<vector<vector<T>>>(M, vector<vector<T>>(L, vector<T>(O, init)))); }

vector<ll> LIST(ll N) { vector<ll> A(N); rep(i, 0, N) cin >> A[i]; return A; }

void print(ld out) { cout << fixed << setprecision(15) << out << '\n'; }
void print(double out) { cout << fixed << setprecision(15) << out << '\n'; }
template<typename T> void print(T out) { cout << out << '\n'; }
template<typename T1, typename T2> void print(pair<T1, T2> out) { cout << out.first << ' ' << out.second << '\n'; }
template<typename T> void print(vector<T> A) { rep(i, 0, A.size()) { cout << A[i]; cout << (i == A.size()-1 ? '\n' : ' '); } }
template<typename T> void print(set<T> S) { vector<T> A(S.begin(), S.end()); print(A); }

void Yes() { print("Yes"); }
void No() { print("No"); }
void YES() { print("YES"); }
void NO() { print("NO"); }

ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }
pll divmod(ll a, ll b) { ll d = a / b; ll m = a % b; return {d, m}; }
template<typename T> bool chmax(T &x, T y) { return (y > x) ? x = y, true : false; }
template<typename T> bool chmin(T &x, T y) { return (y < x) ? x = y, true : false; }

template<typename T> T sum(vector<T> A) { T res = 0; for (T a: A) res += a; return res; }
template<typename T> T max(vector<T> A) { return *max_element(ALL(A)); }
template<typename T> T min(vector<T> A) { return *min_element(ALL(A)); }

ll toint(string s) { ll res = 0; for (char c : s) { res *= 10; res += (c - '0'); } return res; }
int toint(char num) { return num - '0'; }
char tochar(int num) { return '0' + num; }
int ord(char c) { return (int)c; }
char chr(int a) { return (char)a; }

ll pow(ll x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }
ll lcm(ll x, ll y) { return (x * y) / gcd(x, y); }

template<typename T> int bisect_left(vector<T> &A, T val) { return lower_bound(ALL(A), val) - A.begin(); }
template<typename T> int bisect_right(vector<T> &A, T val) { return upper_bound(ALL(A), val) - A.begin(); }

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
};

ll check(vector<ll> &A) {
    ll N = A.size();
    BIT<ll> bit(N);

    ll res = 0;
    rep(i, 0, N) {
        res += i - bit.query(0, A[i]);
        bit.add(A[i], 1);
    }
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N;
    cin >> N;
    auto A = LIST(N);

    vector<ll> ans(N);
    ans[0] = check(A);
    auto B = A;
    rep(i, 0, N) B.pb(A[i]);
    WaveletMatrix<ll, 20> wm(B);
    rep(i, 0, N-1) {
        ll cur = 0;
        cur += wm.range_freq(i+1, i+N, A[i]+1, N);
        cur -= wm.range_freq(i+1, i+N, 0, A[i]);
        ans[i+1] = ans[i]+cur;
    }
    for (ll a : ans) print(a);
    return 0;
}
