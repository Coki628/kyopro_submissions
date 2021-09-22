/*
・動作確認テスト用
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
using vvl = vector<vector<ll>>;
using vvi = vector<vector<int>>;
using vvpll = vector<vector<pll>>;
#define name4(i, a, b, c, d, e, ...) e
#define rep(...) name4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)
#define rep1(i, a) for (ll i = 0, _aa = a; i < _aa; i++)
#define rep2(i, a, b) for (ll i = a, _bb = b; i < _bb; i++)
#define rep3(i, a, b, c) for (ll i = a, _bb = b; (c > 0 && a <= i && i < _bb) or (c < 0 && a >= i && i > _bb); i += c)
#define rrep(i, a, b) for (ll i=(a); i>(b); i--)
#define pb push_back
#define eb emplace_back
#define mkp make_pair
#define ALL(A) A.begin(), A.end()
#define UNIQUE(A) sort(ALL(A)), A.erase(unique(ALL(A)), A.end())
#define elif else if
#define tostr to_string
constexpr ll INF = 1e18;
// constexpr ll INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

template<typename T> vector<vector<T>> list2d(int N, int M, T init) { return vector<vector<T>>(N, vector<T>(M, init)); }
template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) { return vector<vector<vector<T>>>(N, vector<vector<T>>(M, vector<T>(L, init))); }
template<typename T> vector<vector<vector<vector<T>>>> list4d(int N, int M, int L, int O, T init) { return vector<vector<vector<vector<T>>>>(N, vector<vector<vector<T>>>(M, vector<vector<T>>(L, vector<T>(O, init)))); }

template<typename T=ll> vector<T> LIST(ll N) { vector<T> A(N); rep(i, 0, N) cin >> A[i]; return A; }

void print() { cout << '\n'; }
template<typename T> void print(T out) { cout << out << '\n'; }
template<typename T1, typename T2> void print(pair<T1, T2> out) { cout << out.first << ' ' << out.second << '\n'; }
template<typename T> void print(vector<T> A) { rep(i, 0, A.size()) { cout << A[i]; if (i != A.size()-1) cout << ' '; } cout << '\n'; }
template<typename T> void print(deque<T> A) { rep(i, 0, A.size()) { cout << A[i]; if (i != A.size()-1) cout << ' '; } cout << '\n'; }
template<typename T> void print(set<T> S) { vector<T> A(S.begin(), S.end()); print(A); }
#define debug(x) (cout << #x << ": ", print(x));

void Yes() { print("Yes"); }
void No() { print("No"); }
void YES() { print("YES"); }
void NO() { print("NO"); }

// template<int mod> struct ModInt {
//     int x;
//     ModInt() : x(0) {}
//     ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
//     ModInt &operator+=(const ModInt &p) { if((x += p.x) >= mod) x -= mod; return *this; }
//     ModInt &operator-=(const ModInt &p) { if((x += mod - p.x) >= mod) x -= mod; return *this; }
//     ModInt &operator*=(const ModInt &p) { x = (int) (1LL * x * p.x % mod); return *this; }
//     ModInt &operator/=(const ModInt &p) { *this *= p.inverse(); return *this; }
//     ModInt operator-() const { return ModInt(-x); }
//     ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
//     ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
//     ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }
//     ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }
//     bool operator==(const ModInt &p) const { return x == p.x; }
//     bool operator!=(const ModInt &p) const { return x != p.x; }
//     ModInt inverse() const { int a = x, b = mod, u = 1, v = 0, t; while(b > 0) { t = a / b; swap(a -= t * b, b); swap(u -= t * v, v); } return ModInt(u); }
//     ModInt pow(int64_t n) const { ModInt ret(1), mul(x); while(n > 0) { if(n & 1) ret *= mul; mul *= mul; n >>= 1; } return ret; }
//     friend ostream &operator<<(ostream &os, const ModInt &p) { return os << p.x; }
//     friend istream &operator>>(istream &is, ModInt &a) { int64_t t; is >> t; a = ModInt< mod >(t); return (is); }
//     static int get_mod() { return mod; }
//     // operator int() const { return x; }
// };
// using mint = ModInt<MOD>;

template<typename T>
vector<T> accumulate(vector<T> &A, bool indexed=0) {
    int n = A.size();
    auto res = A;
    rep(i, n-1) res[i+1] += res[i];
    if (indexed) res.insert(res.begin(), 0);
    return res;
}

// template<typename T, typename F>
// vector<T> accumulate(vector<T> &A, const F &func=[](T a, T b) { return a + b; }) {
//     int N = A.size();
//     if (!N) return {};
//     vector<T> res(N);
//     res[0] = A[0];
//     rep(i, 1, N) res[i] = func(res[i-1], A[i]);
//     return res;
// }

void solve() {
    // splitとjoin
    // string S = "123:12:23";
    // auto v1 = mapping<ll>(split(S, ':'), [](string s) { return toint(s); });
    // print(v1);
    // auto T1 = join(v1);
    // auto T2 = join(v1, ',');
    // print(T1);
    // print(T2);
    // auto v2 = split(S, ':');
    // auto T3 = join(v2, '.');
    // print(T3);
    // auto T4 = join(v2);
    // print(T4);
    // print(join(v2, '\n'));
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
