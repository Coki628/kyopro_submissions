/*
・ヒューリスティック履修
・これは自力での雑な貪欲解。
　得点を得られるポイントを始点にして、そこから正方形に近い領域が伸ばせるならやる。
　できなかったやつは余った場所で適当に1*1に埋める。
　これでスコア135億点くらい。
・最初0点でびっくりしたんだけど、縦横間違ってたぽい。。H,WとX,Yが逆なの困るよな。
*/

#pragma region mytemplate

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
using pil = pair<int, ll>;
using vvl = vector<vector<ll>>;
using vvi = vector<vector<int>>;
using vvpll = vector<vector<pll>>;
using vvpil = vector<vector<pil>>;
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

template<typename T=ll> vector<T> LIST(ll N) { vector<T> A(N); rep(i, N) cin >> A[i]; return A; }

void print() { cout << '\n'; }
template<typename T> void print(T out) { cout << out << '\n'; }
template<typename T1, typename T2> void print(pair<T1, T2> out) { cout << out.first << ' ' << out.second << '\n'; }
template<typename T> void print(const vector<T> &A) { rep(i, A.size()) { cout << A[i]; if (i != A.size()-1) cout << ' '; } cout << '\n'; }
template<typename T> void print(const deque<T> &A) { vector<T> V(A.begin(), A.end()); print(V); }
template<typename T> void print(const set<T> &S) { vector<T> A(S.begin(), S.end()); print(A); }
#define debug(x) (cout << #x << ": ", print(x));

void Yes() { print("Yes"); }
void No() { print("No"); }
void YES() { print("YES"); }
void NO() { print("NO"); }

#pragma endregion

// 約数列挙
vector<ll> divisors(ll n) {
    vector<ll> res;
    for (ll i=1; i*i<=n; i++) {
        if (n%i == 0) {
            res.pb(i);
            if (n/i != i) res.pb(n/i);
        }
    }
    // sort(ALL(res));
    return res;
}

const ll MX = 10000;
bool grid[MX][MX];

bool check(ll sx, ll sy, ll tx, ll ty) {
    if (tx >= MX or ty >= MX) {
        return false;
    }
    rep(x, sx, tx) {
        rep(y, sy, ty) {
            if (grid[x][y]) {
                return false;
            }
        }
    }
    return true;
}

void paint(ll sx, ll sy, ll tx, ll ty) {
    rep(x, sx, tx) {
        rep(y, sy, ty) {
            grid[x][y] = true;
        }
    }
}

ld calc(ll s, ll r) {
    return 1-pow(1-min(r, s)/(ld)max(r, s), 2);
}

void solve() {
    ll N;
    cin >> N;
    vector<ll> X(N), Y(N), R(N);
    vvl divs;
    rep(i, N) {
        cin >> X[i] >> Y[i] >> R[i];
        divs.eb(divisors(R[i]));
    }
    vvl ans(N);
    ld sm = 0;
    rep(i, N) {
        sort(divs[i].rbegin(), divs[i].rend());
        ll dx = divs[i][divs[i].size()/2];
        ll dy = R[i]/dx;
        if (check(X[i], Y[i], X[i]+dx, Y[i]+dy)) {
            paint(X[i], Y[i], X[i]+dx, Y[i]+dy);
            ans[i] = {X[i], Y[i], X[i]+dx, Y[i]+dy};
            sm += calc(R[i], R[i]);
        }
    }
    rep(i, N) {
        if (ans[i].empty()) {
            bool ok = false;
            rep(x, MX) {
                rep(y, MX) {
                    if (check(x, y, x+1, y+1)) {
                        paint(x, y, x+1, y+1);
                        ans[i] = {x, y, x+1, y+1};
                        ok = true;
                        break;
                    }
                }
                if (ok) break;
            }
        }
    }
    // print(sm);
    for (auto& a : ans) print(a);
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
