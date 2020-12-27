/**
 * ・蟻本演習4-4-5
 * ・ダブリング、二分探索、indexセグ木、区間スケジューリング
 * ・なんとか自力AC！時間かかったけどねー。。
 * ・区間スケジューリングの基本に従うと、右端の早いものから取るのが最善。
 * 　今回は区間がたくさん与えられて、その範囲内でなるべくたくさん取る、みたいな形なので、
 * 　「左端がある位置以降にあるものの中で、右端が最も小さいもの」を高速に(logくらいで)取りたい。
 * 　これを実現するために、左端でソートした配列をにぶたんして、その位置以降を範囲として、
 * 　区間最小値のindexを取るために右端をindexセグ木で管理しておく、といった形を取った。
 * ・これである区間の次にはどれを取るのが最善か、が全て出揃うので、それを使って
 * 　さらにダブリングの配列を構築して、x回後の位置を高速に取れるようにする。
 * ・後は各クエリで、最初の位置の取得と何回先まで行けるかを確認すればよく、これは全てlogでできる。
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
constexpr ll INF = 1000000000000000000;
constexpr ll MOD = 1000000007;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { vector<vector<T>> res(N, vector<T>(M, init)); return res; }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { vector<vector<vector<T>>> res(N, vector<vector<T>>(M, vector<T>(L, init))); return res; }

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

ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }

template<typename T> int bisect_left(vector<T> &A, T val) { return lower_bound(ALL(A), val) - A.begin(); }
template<typename T> int bisect_right(vector<T> &A, T val) { return upper_bound(ALL(A), val) - A.begin(); }

template<typename Monoid>
struct SegTreeIndex {
    using F = function<Monoid(Monoid, Monoid)>;

    int sz;
    vector<pair<Monoid, int>> seg;

    const F f;
    const Monoid M1;

    pair<Monoid, int> compare(pair<Monoid, int> a, pair<Monoid, int> b) {
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

    SegTreeIndex(int n, const F f, const Monoid &M1) : f(f), M1(M1) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.assign(2 * sz, {M1, -1});
    }

    SegTreeIndex(const F f, const Monoid &M1) : f(f), M1(M1) {}

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
};

// ダブリング
vvl doubling(int MAX, vector<ll> &A) {

    int N = A.size();
    auto nxt = list2d(MAX, N, -1LL);
    rep(i, 0, N) {
        nxt[0][i] = A[i];
    }
    rep(k, 1, MAX) {
        rep(i, 0, N) {
            if (nxt[k-1][i] != -1) {
                nxt[k][i] = nxt[k-1][nxt[k-1][i]];
            }
        }
    }
    return nxt;
}

template<typename F>
ll bisearch_max(ll mn, ll mx, const F &func) {

    ll ok = mn;
    ll ng = mx;
    while (ok+1 < ng) {
        ll mid = (ok+ng) / 2;
        if (func(mid)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N, Q;
    cin >> N >> Q;
    vector<pll> ILR(N);
    vector<ll> IL(N), IR(N);
    rep(i, 0, N) {
        ll l, r;
        cin >> l >> r;
        ILR[i] = {l, r};
    }
    // 左端でソート
    sort(ALL(ILR));
    // 右端はindexセグ木で管理
    SegTreeIndex<ll> seg(N, [](ll a, ll b) { return min(a, b); }, INF);
    rep(i, 0, N) {
        IL[i] = ILR[i].first;
        seg.set(i, ILR[i].second);
    }
    seg.build();

    // A[i] := 区間iの次にとるべき最善の区間
    vector<ll> A(N);
    rep(i, 0, N) {
        // この区間の終了位置以降で、最も右端が小さい区間を取る
        ll j = bisect_left(IL, ILR[i].second);
        auto [mn, k] = seg.query(j, N);
        A[i] = k;
    }
    // ダブリングでx回後の位置を高速に取れるようにする
    ll MX = 32;
    auto nxt = doubling(MX, A);

    rep(_, 0, Q) {
        ll l, r;
        cin >> l >> r;
        // この左端に対して最初に取れる最善の区間jを取得
        ll i = bisect_left(IL, l);
        ll mn, j;
        tie(mn, j) = seg.query(i, N);
        if (j == -1 or mn > r) {
            print(0);
        } else {
            // 区間jから始めて、あと何回先まで行けるか二分探索する
            ll res = 1;
            res += bisearch_max(0, pow(2, MX), [&](ll m) {
                ll cur = j;
                rrep(k, MX-1, -1) {
                    if (m>>k & 1) {
                        cur = nxt[k][cur];
                        if (cur == -1 or ILR[cur].second > r) {
                            return false;
                        }
                    }
                }
                return true;
            });
            print(res);
        }
    }
    return 0;
}
