/**
 * ・蟻本演習4-4-5
 * ・ダブリング、グリッド、構文解析、重実装
 * ・疲れたー。。なんとか自力AC！
 * ・構文解析パートをがっつりやらされるのはICPCなんだなーって感じ。
 * 　括弧内は再帰させてうまいことやる。
 * ・シフトさせるとこは愚直シミュでOK。各O(N)でできる。
 * ・繰り返し部分はダブリングするんだけど、グリッド->ダブリング用数列->グリッドの変換がゴチャゴチャした。
 * 　ようは各値が1回操作でどこからどこに行ったかを記録して、ダブリングにかけて、
 * 　times回操作後の位置を調べて、それをグリッドに適用すればいいんだけど、まー頭壊れる。。
 * 　うまい人はもっと綺麗にやるんだろうなーって思いながら頑張った。。
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

ll gridtoid(ll i, ll j, ll W) {
    return i*W+j;
}

pll idtogrid(ll id, ll W) {
    return divmod(id, W);
}

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

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N, L;
    cin >> N >> L;
    string S;
    cin >> S;

    auto grid = list2d(N, N, 0LL);
    rep(i, 0, N) {
        rep(j, 0, N) {
            grid[i][j] = N*i + j;
        }
    }

    const string LRUD = "LRUD";
    const string digits = "0123456789";
    const ll MXLOG = 32;
    auto rec = [&](auto&& f, vvl &grid, ll &i) -> void {
        while (i < L) {
            // LRUDの時
            if (LRUD.find(S[i]) != -1) {
                // d := 方向
                char d = S[i];
                i++;
                string cnt = "";
                while (i < L and digits.find(S[i]) != -1) {
                    cnt += S[i];
                    i++;
                }
                // 左シフト
                if (d == 'L') {
                    ll h = toint(cnt) - 1;
                    ll tmp = grid[h][0];
                    rep(j, 0, N-1) {
                        grid[h][j] = grid[h][j+1];
                    }
                    grid[h][N-1] = tmp;
                // 右シフト
                } else if (d == 'R') {
                    ll h = toint(cnt) - 1;
                    ll tmp = grid[h][N-1];
                    rrep(j, N-1, 0) {
                        grid[h][j] = grid[h][j-1];
                    }
                    grid[h][0] = tmp;
                // 上シフト
                } else if (d == 'U') {
                    ll w = toint(cnt) - 1;
                    ll tmp = grid[0][w];
                    rep(j, 0, N-1) {
                        grid[j][w] = grid[j+1][w];
                    }
                    grid[N-1][w] = tmp;
                // 下シフト
                } else {
                    ll w = toint(cnt) - 1;
                    ll tmp = grid[N-1][w];
                    rrep(j, N-1, 0) {
                        grid[j][w] = grid[j-1][w];
                    }
                    grid[0][w] = tmp;
                }
            // 括弧が来たら、内側を再帰的に処理
            } else if (S[i] == '(') {
                // この括弧内処理前のグリッドを取っておく
                vvl bk = grid;
                i++;
                f(f, grid, i);
                i++;
                string cnt = "";
                while (i < L and digits.find(S[i]) != -1) {
                    cnt += S[i];
                    i++;
                }
                // times := 括弧内を繰り返す回数
                ll times = toint(cnt);
                // P[i] := (番号iの出発位置, 番号iの到着位置)
                vector<pll> P(N*N);
                rep(j, 0, N) {
                    rep(k, 0, N) {
                        P[bk[j][k]].first = gridtoid(j, k, N);
                        P[grid[j][k]].second = gridtoid(j, k, N);
                    }
                }
                // A[i] := iが次に行く位置
                vector<ll> A(N*N);
                rep(j, 0, N*N) {
                    A[P[j].first] = P[j].second;
                }
                auto nxt = doubling(MXLOG, A);
                // B[i] := iがtimes回後に行く位置
                vector<ll> B(N*N);
                rep(j, 0, N*N) {
                    ll cur = j;
                    rrep(k, MXLOG-1, -1) {
                        if (times>>k & 1) {
                            cur = nxt[k][cur];
                        }
                    }
                    B[j] = cur;
                }
                rep(j, 0, N) {
                    rep(k, 0, N) {
                        auto [h, w] = idtogrid(B[gridtoid(j, k, N)], N);
                        grid[h][w] = bk[j][k];
                    }
                }
            } else if (S[i] == ')') {
                return;
            }
        }
        return;
    };
    ll i = 0;
    rec(rec, grid, i);

    for (auto &row : grid) {
        rep(i, 0, N) {
            row[i]++;
        }
        print(row);
    }
    return 0;
}
