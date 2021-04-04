/**
 * ・自力AC！ヒントは得ていたけど、ちゃんと通せて嬉しい！
 * ・座標圧縮、遅延セグ木、区間和取得・区間加算・区間更新
 * ・座圧して遅延セグ木に乗せる、は初めてやったかな。
 * ・区間和取得の時にペアで使う要素数の方に、普通は初期値で1にするけど、
 * 　ここを座圧した長さに変えると、あとはほぼいつも通りセグ木が使える、
 * 　的なことをTLで誰かが話してるの聞いて、それならできるかも、と着手。
 * ・まあ当然、貼るだけみたいな簡単ではなかった。普通にやろうとすると、
 * 　N^2のDPに遷移Nだけどlogにできる、くらいの感じまでしかならない。
 * 　なんとか各要素で遷移させないで、まとめてやれないか考えてみる。
 * 　とりあえず貰うDPで考えて、各要素にどのくらい遷移してこれるか考えると、
 * 　ほぼ全部できる。自分と同じ位置以外。でもこの自分の位置っていうのは、
 * 　それぞれ値が異なるので、これを差し引くのはまとめてできない。
 * 　これでほぼ詰んでたんだけど、ガチャガチャいじって観察してたら良い方針が生える。
 * ・総和-自分が欲しいけど、自分-総和ってやると正負は逆だけど
 * 　欲しい値になってるよね、となる。これなら一括で総和を引くだけなのでまとめられる。
 * 　これで次また総和を引けばまた正負が変わるけど絶対値では合ってる。
 * 　最後に、やった回数の偶奇によって*-1すれば、正しい答えになる。
 * 　modintで負数を当てにするのとかやった覚えなくて不安だけど、
 * 　まあ多分合うだろう…。(実際ちゃんと使えた。)
 * 　2乗愚直DP書いてみて大きいサンプル合ったので、これで頑張ることに決めた。
 * 　これが当たり方針でACに繋がるんだけど、まーここからも長かった。
 * ・さて、値が残るところの遷移はこれでいいんだけど、
 * 　各位置でA[i]以下しか使えないので、A[i]超の部分は消す必要がある。遷移してこれないからね。
 * 　で、具体的にはそれは区間更新で0にすればいいんだけど、
 * 　さっきの総和を引くところで、区間更新じゃなくて区間加算を使ってしまっている。
 * 　普通にやるとこれは同時にできない。
 * 　つい最近それをBeatsで対応したけど、今回は座圧してしまう関係上、
 * 　乗せるモノイドがただの値じゃなくて、{値、区間長}なので、
 * 　パッケージ化してしまっているBeatsではそのまま使えない。中身は魔境なので改造も困難。
 * ・ここで、はまやんさんがその問題の記事で普通の遅延セグ木で更新と加算を同時に
 * 　やっていたのを思いだす。記事のコードをよく読んで、頑張って作用素の管理方法を読み解く。
 * 　まずはそっちの問題でAC確認。で、llをmintに変えたりしてこっちでも実装。
 * 　無事AC！！長かったー。AC1.994秒。ギリギリー。。
 * 　まあ50万に座圧と遅延セグのlogはかなり重そうだけど、それでももう少し速くなりそうだよなー。
 * ・あと座圧ね、0を追加して、半開区間っぽくするために、
 * 　「その値のところは含まない、その手前まで」みたいにしてある。
 * ・座圧ライブラリのVerify。unzipでかなり無駄なもん作ってることに気付いたので。
 * 　ちょっと速くなって、AC1.86秒。メモリも軽くなって90MB→63MBに。
 * ・さらに新しく作ったにぶたんベースの座圧ライブラリのVerify。
 * 　やっぱり良くなって、AC1.67秒、メモリ39MB。
 * ・定数のはずのunordered_mapより、vectorにぶたんのlogのが速いんだねやっぱり。
 * 　(ちなみにmapで試すとTLEするからunordered_mapでもmapよりは速い。)
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
#define name4(i, a, b, c, d, e, ...) e
#define rep(...) name4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)
#define rep1(i, a) for(ll i = 0, _aa = a; i < _aa; i++)
#define rep2(i, a, b) for(ll i = a, _bb = b; i < _bb; i++)
#define rep3(i, a, b, c) for(ll i = a, _bb = b; (a <= i && i < _bb) or (a >= i && i > _bb); i += c)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define mkp make_pair
#define ALL(A) A.begin(), A.end()
#define elif else if
constexpr ll INF = 1e18;
// constexpr ll INF = LONG_LONG_MAX;
// constexpr ll MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-10;

const string digits = "0123456789";
const string ascii_lowercase = "abcdefghijklmnopqrstuvwxyz";
const string ascii_uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string ascii_letters = ascii_lowercase + ascii_uppercase;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { return vector<vector<T>>(N, vector<T>(M, init)); }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { return vector<vector<vector<T>>>(N, vector<vector<T>>(M, vector<T>(L, init))); }
template<typename T> vector<vector<vector<vector<T>>>> list4d(int N, int M, int L, int O, T init) { return vector<vector<vector<vector<T>>>>(N, vector<vector<vector<T>>>(M, vector<vector<T>>(L, vector<T>(O, init)))); }

template<typename T=ll> vector<T> LIST(ll N) { vector<T> A(N); rep(i, 0, N) cin >> A[i]; return A; }

void print() { cout << '\n'; }
void print(ld out) { cout << fixed << setprecision(15) << out << '\n'; }
void print(double out) { cout << fixed << setprecision(15) << out << '\n'; }
template<typename T> void print(T out) { cout << out << '\n'; }
template<typename T1, typename T2> void print(pair<T1, T2> out) { cout << out.first << ' ' << out.second << '\n'; }
template<typename T> void print(vector<T> A) { rep(i, 0, A.size()) { cout << A[i]; cout << (i == A.size()-1 ? '\n' : ' '); } }
template<typename T> void print(deque<T> A) { rep(i, 0, A.size()) { cout << A[i]; cout << (i == A.size()-1 ? '\n' : ' '); } }
template<typename T> void print(set<T> S) { vector<T> A(S.begin(), S.end()); print(A); }

void Yes() { print("Yes"); }
void No() { print("No"); }
void YES() { print("YES"); }
void NO() { print("NO"); }

ll floor(ll a, ll b) { if (a < 0) { return (a-b+1) / b; } else { return a / b; } }
ll ceil(ll a, ll b) { if (a >= 0) { return (a+b-1) / b; } else { return a / b; } }
template<typename T> pll divmod(ll a, T b) { ll d = a / b; ll m = a % b; return {d, m}; }
template<typename T> bool chmax(T &x, T y) { return (y > x) ? x = y, true : false; }
template<typename T> bool chmin(T &x, T y) { return (y < x) ? x = y, true : false; }

template<typename T> T sum(vector<T> &A) { T res = 0; for (T a: A) res += a; return res; }
template<typename T> T max(vector<T> &A) { return *max_element(ALL(A)); }
template<typename T> T min(vector<T> &A) { return *min_element(ALL(A)); }

ll toint(string s) { ll res = 0; for (char c : s) { res *= 10; res += (c - '0'); } return res; }
int toint(char num) { return num - '0'; }
char tochar(int num) { return '0' + num; }
int ord(char c) { return (int)c; }
char chr(int a) { return (char)a; }

ll pow(int x, int n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(int x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, int n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, ll n) { ll res = 1; rep(_, 0, n) res *= x; return res; }
ll pow(ll x, ll n, int mod) { ll res = 1; while (n > 0) { if (n & 1) { res = (res * x) % mod; } x = (x * x) % mod; n >>= 1; } return res; }

int popcount(ll S) { return __builtin_popcountll(S); }
ll gcd(ll a, ll b) { return __gcd(a, b); }
ll lcm(ll x, ll y) { return (x * y) / gcd(x, y); }

template<typename T> int bisect_left(vector<T> &A, T val) { return lower_bound(ALL(A), val) - A.begin(); }
template<typename T> int bisect_right(vector<T> &A, T val) { return upper_bound(ALL(A), val) - A.begin(); }
template<typename F> ll bisearch_min(ll mn, ll mx, const F &func) { ll ok = mx, ng = mn; while (ng+1 < ok) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }
template<typename F> ll bisearch_max(ll mn, ll mx, const F &func) { ll ok = mn, ng = mx; while (ok+1 < ng) { ll mid = (ok+ng) / 2; if (func(mid)) ok = mid; else ng = mid; } return ok; }
template<typename T> unordered_map<T, ll> Counter(vector<T> &A) { unordered_map<T, ll> res; for (T a : A) res[a]++; return res; }
unordered_map<char, ll> Counter(string &S) { unordered_map<char, ll> res; for (char c : S) res[c]++; return res; }

template<int mod> struct ModInt {
    int x;
    ModInt() : x(0) {}
    ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
    ModInt &operator+=(const ModInt &p) { if((x += p.x) >= mod) x -= mod; return *this; }
    ModInt &operator-=(const ModInt &p) { if((x += mod - p.x) >= mod) x -= mod; return *this; }
    ModInt &operator*=(const ModInt &p) { x = (int) (1LL * x * p.x % mod); return *this; }
    ModInt &operator/=(const ModInt &p) { *this *= p.inverse(); return *this; }
    ModInt operator-() const { return ModInt(-x); }
    ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
    ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
    ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }
    ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }
    bool operator==(const ModInt &p) const { return x == p.x; }
    bool operator!=(const ModInt &p) const { return x != p.x; }
    ModInt inverse() const { int a = x, b = mod, u = 1, v = 0, t; while(b > 0) { t = a / b; swap(a -= t * b, b); swap(u -= t * v, v); } return ModInt(u); }
    ModInt pow(int64_t n) const { ModInt ret(1), mul(x); while(n > 0) { if(n & 1) ret *= mul; mul *= mul; n >>= 1; } return ret; }
    friend ostream &operator<<(ostream &os, const ModInt &p) { return os << p.x; }
    friend istream &operator>>(istream &is, ModInt &a) { int64_t t; is >> t; a = ModInt< mod >(t); return (is); }
    static int get_mod() { return mod; }
    // operator int() const { return x; }
    // operator ll() const { return x; }
};
using mint = ModInt<MOD>;

// 遅延評価セグメント木(非再帰)
template<typename T, typename E>
struct LazySegTree {
    using F = function<T(T, T)>;
    using G = function<T(T, E)>;
    using H = function<E(E, E)>;
    int n, height;
    F f;
    G g;
    H h;
    T ti;
    E ei;
    vector<T> dat;
    vector<E> laz;
    LazySegTree(F f, G g, H h, T ti, E ei):
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
    int find(int st, C &check, T &acc, int k, int l, int r){
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

    template<typename C>
    int find(int st, C &check){
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

// 座標圧縮
template<typename T>
struct Compress {

    int N;
    vector<T> dat;

    Compress(vector<T> A) {
        sort(A.begin(), A.end());
        A.erase(unique(A.begin(), A.end()), A.end());
        N = A.size();
        dat = A;
    }

    int zip(T x) {
        return bisect_left(dat, x);
    }

    T unzip(int x) {
        return dat[x];
    }

    int operator[](T x) {
        return zip(x);
    }

    int size() {
        return dat.size();
    }

    vector<T> zip(vector<T> &A) {
        int M = A.size();
        vector<int> res(M);
        rep(i, M) res[i] = zip(A[i]);
        return res;
    }
};

// 区間和取得・区間加算・区間更新
struct Func {
    mint add, assign;
    bool update;
    bool operator==(const Func &f)const{
        return add == f.add and assign == f.assign and update == f.update;
    }
};
using pmm = pair<mint, mint>;
auto f = [](pmm a, pmm b) -> pmm { return { a.first+b.first, a.second+b.second }; };
auto g = [](pmm a, Func b) -> pmm {
    if (b.update) {
        return { a.second*(b.add+b.assign), a.second };
    } else {
        return { a.first+a.second*b.add, a.second };
    }
};
auto h = [](Func a, Func b) -> Func { 
    if (not b.update) {
        a.add += b.add;
    } else {
        a.update = 1;
        a.add = 0;
        a.assign = b.add+b.assign;
    }
    return a;
};

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    A.insert(A.begin(), 0);
    Compress<ll> cp(A);
    ll M = cp.size();

    vector<ll> B(M);
    rep(i, 0, M-1) {
        B[i] = cp.unzip(i+1)-cp.unzip(i);
    }
    vector<pmm> B2(M);
    //  値と圧縮した区間長をペアで持つ
    rep(i, M) B2[i] = {0, B[i]};

    LazySegTree<pmm, Func> seg(f, g, h, {0, 0}, {0, 0, 0});
    seg.build(B2);
    seg.update(0, cp[A[1]], {1, 0, 0});
    rep(i, 2, N+1) {
        mint sm = seg.query(0, M).first;
        // if (i%2 == 1) print(sm*-1);
        // else print(sm);
        ll mi = cp[A[i]];
        // 今回遷移がある位置(区間加算で総和を引く)
        seg.update(0, mi, {-sm, 0, 0});
        // 今回遷移がない位置(区間更新で0にする)
        seg.update(mi, M, {0, 0, 1});
    }
    mint ans = seg.query(0, M).first;
    if (N%2 == 0) ans = -ans;
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
