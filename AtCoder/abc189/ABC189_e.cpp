/**
 * 参考：https://atcoder.jp/contests/abc189/editorial
 * 　　　https://qiita.com/yuba/items/7fb6a49adfda8fa466d8
 * ・自力ならず。でも学び多かったしOK。
 * ・アフィン変換、行列の積、累積積
 * ・2次元座標全体の移動は、3*3行列で管理すると効率よく扱える。
 * 　行列累乗の時みたいに遷移を、
 * 　x[i] = a*x[i-1] + b*y[i-1] + c*1
 * 　y[i] = a*x[i-1] + b*y[i-1] + c*1
 * 　定数項用のダミー = 0 + 0 + 1
 * 　と考えれば、座標を動かす操作を行列にプロットできる。
 * 　で、行列累乗がそうだったように、遷移行列同士を先に掛け算して、
 * 　最後に初期値と掛けると結果の値が分かる、というのがここでも使える。
 * ・ここまで考えがまとまって実装するも、なぜか答えが合わない。。すげー悩んだ。
 * 　比較的実装方針が近めな人のと比較したりしてよーく精査すると、分かった。
 * 　遷移行列を掛け算して累積積としていく時、
 * 　「mat[i] = mat[i-1]*今回の操作」みたいにやるとダメで、
 * 　「mat[i] = 今回の操作*mat[i-1]」ってやらないといけなかった。
 * 　行列の乗算が交換法則が成り立たないのは分かるんだけど、普通に考えると
 * 　いつものDPみたく前者の向きでやりたくなると思うんだよなー。
 * 　実際、行列累乗でmat_powする時は res = res*mat の向きでやってて問題が起きない。
 * 　なんで逆なんだろー。。。
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

// 行列の積
template<typename T> vector<vector<T>> mat_dot(const vector<vector<T>> &A, const vector<vector<T>> &B) {
    int n1 = A.size();
    int n2 = A[0].size();
    int m2 = B[0].size();
    auto res = list2d(n1, m2, (T)0);
    rep(i, 0, n1) {
        rep(j, 0, m2) {
            rep(k, 0, n2) {
                res[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return res;
}

// 右回り
const vvl rot90 = {
    {0, 1, 0},
    {-1, 0, 0},
    {0, 0, 1},
};

// 左回り
const vvl rot270 = {
    {0, -1, 0},
    {1, 0, 0},
    {0, 0, 1},
};

// x = p で反転
vvl move_x(ll p) {
    const vvl res = {
        {-1, 0, 2*p},
        {0, 1, 0},
        {0, 0, 1},
    };
    return res;
}

// y = p で反転
vvl move_y(ll p) {
    const vvl res = {
        {1, 0, 0},
        {0, -1, 2*p},
        {0, 0, 1},
    };
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N;
    cin >> N;
    vector<pll> XY(N);
    rep(i, 0, N) {
        cin >> XY[i].first >> XY[i].second;
    }
    ll M;
    cin >> M;
    vector<tuple<ll, ll, ll, ll>> event;
    rep(i, 0, M) {
        ll op, p = -1;
        cin >> op;
        if (op == 3 or op == 4) {
            cin >> p;
        }
        event.pb({i+1, 0, op, p});
    }
    ll Q;
    cin >> Q;
    rep(i, 0, Q) {
        ll a, b;
        cin >> a >> b;
        event.pb({a, 1, b, i});
    }
    sort(ALL(event));

    vvl base = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
    };
    vector<pll> ans(Q);
    for (auto& [a, b, c, d] : event) {
        // op
        if (b == 0) {
            if (c == 1) {
                base = mat_dot(rot90, base);
            } elif (c == 2) {
                base = mat_dot(rot270, base);
            } elif (c == 3) {
                base = mat_dot(move_x(d), base);
            } else {
                base = mat_dot(move_y(d), base);
            }
        // query
        } else {
            c--;
            auto [x, y] = XY[c];
            vvl cur = {
                {x},
                {y},
                {1},
            };
            auto res = mat_dot(base, cur);
            ans[d] = {res[0][0], res[1][0]};
        }
    }
    for (auto &p : ans) print(p);
}
