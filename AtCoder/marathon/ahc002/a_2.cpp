/*
・ヒューリスティック履修
・DFS、バックトラック
・これも自力。行き止まったら状態戻して別の方に進む。
　やるだけやって、2秒ギリギリで再帰打ち切って終了。そこまでの最善を出力。
　スコアはさすがにだいぶ伸びて296万くらい。
・この後色々改善しようとしたけど、結局これより良いのは出せなかった。
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

const vector<pii> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

const int N = 50;
const int NN = N*N, H = N, W = N;
int T[N][N], P[N][N];

vector<char> mp = {'U', 'D', 'L', 'R'};
vector<bool> used(NN);

void solve() {
    ll sh, sw;
    cin >> sh >> sw;
    rep(i, N) {
        rep(j, N) {
            cin >> T[i][j];
        }
    }
    rep(i, N) {
        rep(j, N) {
            cin >> P[i][j];
        }
    }

    auto start = clock();
    string ans, cur;
    ll score = 0, mx = 0;
    auto rec = [&](auto&& f, ll h, ll w) -> bool {
        // 2秒前に打ち切り
        auto curt = clock();
        if (curt-start > 1900000) {
            return false;
        }
        rep(i, 4) {
            auto [dh, dw] = directions[i];
            ll nh = h+dh;
            ll nw = w+dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
            if (used[T[nh][nw]]) continue;
            used[T[nh][nw]] = true;
            cur += mp[i];
            score += P[nh][nw];
            if (!f(f, nh, nw)) {
                return false;
            }
            score -= P[nh][nw];
            cur.pop_back();
            used[T[nh][nw]] = false;
        }
        if (score > mx) {
            mx = score;
            ans = cur;
        }
        return true;
    };
    used[T[sh][sw]] = true;
    score += P[sh][sw];
    rec(rec, sh, sw);
    // print(mx);
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
