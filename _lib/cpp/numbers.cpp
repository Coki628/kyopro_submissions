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

template<typename T> int bisect_left(vector<T> &A, T val) { return lower_bound(ALL(A), val) - A.begin(); }
template<typename T> int bisect_right(vector<T> &A, T val) { return upper_bound(ALL(A), val) - A.begin(); }


// 素数判定 
bool is_prime(ll num) {

    if (num < 2) {
        return false;
    }
    if (set<ll>({2, 3, 5}).count(num)) {
        return true;
    }
    if (num%2 == 0 or num%3 == 0 or num%5 == 0) {
        return false;
    }
    // 疑似素数(2でも3でも割り切れない数字)で次々に割っていく
    ll prime = 7;
    ll step = 4;
    ll num_sqrt = sqrt(num);
    while (prime <= num_sqrt) {
        if (num%prime == 0) {
            return false;
        }
        prime += step;
        step = 6-step;
    }
    return true;
}


// 素数列挙(エラトステネスの篩) 
vector<ll> eratosthenes_sieve(ll n) {

    vector<bool> table(n+1);
    vector<ll> primes;
    rep(i, 2, n+1) {
        if (table[i] == 0) {
            primes.pb(i);
            for (ll j=i+i; j<=n; j+=i) {
                table[j] = 1;
            }
        }
    }
    return primes;
}


// 素因数分解
map<ll, ll> factorize(ll x) {

    map<ll, ll> res;
    for (ll i=2; i*i<=x; i++) {
        while (x%i == 0) {
            x /= i;
            res[i]++;
        }
        if (x == 1) break;
    }
    if (x != 1) res[x]++;
    return res;
}


// 高速素因数分解(osa_k法)、前計算
vector<ll> eratosthenes_sieve(ll n) {

    vector<ll> table(n+1);
    table[1] = 1;
    rep(i, 2, n+1) {
        if (table[i] == 0) {
            for (ll j=i; j<=n; j+=i) {
                table[j] = i;
            }
        }
    }
    return table;
}

// 高速素因数分解(osa_k法)
map<ll, ll> factorize(vector<ll> &table, ll x) {

    map<ll, ll> res;
    while (x != table[x]) {
        res[table[x]]++;
        x /= table[x];
    }
    if (x != 1) {
        res[x]++;
    }
    return res;
}


// 約数列挙
vector<ll> divisors(ll n) {

    vector<ll> res;
    for (ll i=1; i*i<=n; i++) {
        if (n%i == 0) {
            res.pb(i);
            if (n/i != i) res.pb(n/i);
        }
    }
    sort(ALL(res));
    return res;
}


// N進数文字列Sを10進数に
ll ntod(string S, ll n) {
    ll res = 0, k = 1;
    reverse(ALL(S));
    for (char &c : S) {
        res += k*toint(c);
        k *= n;
    }
    return res;
}


// 10進数をN進数文字列に(負数対応版)
// string dton(ll num, ll n) {
//     string res;
//     while (abs(num) > 0) {
//         ll m = num % abs(n);
//         num -= m;
//         res += tochar(m);
//         num /= n;
//     }
//     reverse(ALL(res));
//     if (res != "") {
//         return res;
//     } else {
//         return "0";
//     }
// }
string dton(ll num, ll n, char base='0') {
    string res;
    while (abs(num) > 0) {
        ll m = num % abs(n);
        num -= m;
        res += base+m;
        num /= n;
    }
    reverse(ALL(res));
    if (res != "") {
        return res;
    } else {
        return res+base;
    }
}


// 整数で正確にsqrtを返す
ll isqrt(ll n, bool ceil=false) {
    ll ok = 0;
    ll ng = 3037000500;
    while (ng - ok > 1) {
        ll m = ok + (ng - ok) / 2;
        if (m * m <= n) {
            ok = m;
        } else {
            ng = m;
        }
    }
    if (ceil and ok*ok != n) ok++;
    return ok;
}


// ピタゴラス数(未整備。重複削除とかgcdで互いに素とか考えてない。)
vector<ll> calc(ll m, ll n) {
    ll a = abs(pow(m, 2) - pow(n, 2));
    ll b = 2*m*n;
    ll c = pow(m, 2) + pow(n, 2);
    vector<ll> res = {a, b, c};
    sort(ALL(res));
    return res;
}


// 桁和：O(logN)
ll digit_sum(ll n) {
    ll res = 0;
    while (n > 0) {
        res += n % 10;
        n /= 10;
    }
    return res;
}
