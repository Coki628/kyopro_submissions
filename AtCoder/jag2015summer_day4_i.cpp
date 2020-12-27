/**
 * ・蟻本演習4-4-4
 * ・なんとか自力AC！
 * ・式変形、直線の式を高速化するDP、Li Chao Tree
 * ・式変形はyukico409より全然複雑じゃないんだけど、2次元DPなのと、添字に使う時間tとは別の単位を
 * 　直線の式で扱うので、ちょっと勝手が違う。(強い人には同じに見えるのかもしれないけど。。)
 * ・結論としては、各時間tそれぞれに個別にLi Chao Treeを持たせて直線の式を管理。
 * ・yukico409と同じで、歌わない遷移を含めた状態で直線の式を追加しようとすると合わないので、
 * 　歌う遷移 → 直線の式の追加 → 歌わない遷移 の順でやる。
 * ・時間を後ろから更新すると、前から直線の式の最大を貰ってくる時に、
 * 　今回分の更新を拾わないで済むので実装が楽。(まあ貰う元が違うだけで仕組みは普通のDPと一緒)
 * ・他にもまあ色々あったけどソース内コメント参照。
 * ・計算量が4000^2=1600万にLi Chao Treeのlogが乗るので結構きついかと思ったけど、
 * 　案外余裕でAC0.26秒。colopl2018_qual_dは5000^2で思いっきりTLEしたのでちょっと非自明。
 * 　多分、logがかかるxの範囲が狭いのと、add_lineはlog1つだけどadd_segmentはlog2つなのが原因かと。
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

    DynamicLiChaoTree(ll x_low, ll x_high, T id, bool is_min=1) : root{nullptr}, x_low(x_low), x_high(x_high), id(id), is_min(is_min) {}

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

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N, T;
    cin >> N >> T;
    vector<tuple<ll, ll, ll>> FTP(N);
    rep(i, 0, N) {
        ll t, p, f;
        cin >> t >> p >> f;
        FTP[i] = {f, t, p};
    }
    // 順番は自由とあるが、曲間のfの絶対値を小さくしたいのでfでソート順が最善
    sort(ALL(FTP));

    auto dp = list2d(N+1, T+1, -INF);
    dp[0][0] = 0;
    // 時間毎でT+1個作る
    vector<DynamicLiChaoTree<ll>> lct(T+1, {0, 10000, INF, false});
    rep(i, 1, N+1) {
        auto [f, t, p] = FTP[i-1];
        rrep(j, T, -1) {
            // この曲を歌う場合の遷移
            if (j-t > 0) {
                chmax(dp[i][j], lct[j-t].query(f) + p - f*f);
            // 初回(t=0)だけは、fにかかわる分をノーコストで遷移させる
            } else if (j-t == 0) {
                chmax(dp[i][j], dp[i-1][j-t] + p);
            }
            if (dp[i][j] > -INF) {
                // この曲iを歌った場合の直線の式を時間jに追加
                lct[j].add_line(2*f, dp[i][j] - f*f);
            }
            // この曲を歌わない場合の遷移
            chmax(dp[i][j], dp[i-1][j]);
        }
    }
    ll ans = max(dp[N]);
    print(ans);

    // ll FMX = 10007;
    // auto dp = list3d(N+1, T+1, FMX, -INF);
    // rep(k, 0, FMX) dp[0][0][k] = 0;
    // rep(i, 0, N) {
    //     auto [f, t, p] = FTP[i];
    //     rep(j, 0, T+1) {
    //         rep(k, 0, FMX) {
    //             chmax(dp[i+1][j][k], dp[i][j][k]);
    //             if (j-t >= 0) {
    //                 chmax(dp[i+1][j][k], dp[i][j-t][f] + p-(f-k)*(f-k));
    //             }
    //         }
    //     }
    // }
    // ll ans = 0;
    // rep(j, 0, T+1) rep(k, 0, FMX) chmax(ans, dp[N][j][k]);
    // print(ans);
    return 0;
}
