/*
・ヒューリスティック履修
・山登り
・終わった時点で結構上下左右に余白がありそうだったので、
　ちょっと早めに終わって、N個全部上下左右チェックして伸ばせそうなら伸ばす、
　の処理を追加した。前と後ろで微妙に違う添字ゲーがつらかった。
・ビジュアライザで見た感じ、結構埋まってる場所が増えたように感じたんだけど、
　結果は436億くらいでちょい下がった。。まあこれくらいは誤差だろうけど、
　少なくともあんま改善にはなってなかったんだな。。
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

// [l,r)の範囲で乱数生成
mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
ll randrange(ll l, ll r) {
    uniform_int_distribution<ll> rand(l, r-1);
    return rand(mt);
}

const ll MX = 10000;
bool used[MX][MX];
int ids[MX][MX];

bool check(ll sx, ll sy, ll tx, ll ty) {
    if (tx >= MX or ty >= MX) {
        return false;
    }
    rep(x, sx, tx) {
        rep(y, sy, ty) {
            if (used[x][y]) {
                return false;
            }
        }
    }
    return true;
}
bool check(vector<ll> &v) {
    return check(v[0], v[1], v[2], v[3]);
}

void paint(ll sx, ll sy, ll tx, ll ty, ll a) {
    rep(x, sx, tx) {
        rep(y, sy, ty) {
            used[x][y] = true;
            ids[x][y] = a;
        }
    }
}
void paint(vector<ll> &v, ll a) {
    paint(v[0], v[1], v[2], v[3], a);
}

void erase(ll sx, ll sy, ll tx, ll ty) {
    rep(x, sx, tx) {
        rep(y, sy, ty) {
            used[x][y] = false;
            ids[x][y] = -1;
        }
    }
}
void erase(vector<ll> &v) {
    erase(v[0], v[1], v[2], v[3]);
}

ll get_s(ll sx, ll sy, ll tx, ll ty) {
    return (tx-sx)*(ty-sy);
}
ll get_s(vector<ll> &v) {
    return get_s(v[0], v[1], v[2], v[3]);
}

ld calc(ll s, ll r) {
    return 1-pow(1-min(r, s)/(ld)max(r, s), 2);
}

void solve() {
    rep(i, MX) rep(j, MX) ids[i][j] = -1;
    ll N;
    cin >> N;
    vector<ll> X(N), Y(N), R(N);
    rep(i, N) {
        cin >> X[i] >> Y[i] >> R[i];
    }
    vvl ans(N);
    vector<ll> S(N, 1);
    ld cur = 0;
    rep(i, N) {
        paint(X[i], Y[i], X[i]+1, Y[i]+1, i);
        ans[i] = {X[i], Y[i], X[i]+1, Y[i]+1};
        cur += calc(S[i], R[i]);
    }

    auto start = clock();
    while (clock()-start <= 4200000) {
    // while (1) {
        ll i = randrange(0, N);
        ll d = randrange(0, 4);
        ll len = randrange(1, 100);
        // 負方向
        if (d < 2) {
            if (ans[i][d]-len < 0) continue;
            erase(ans[i]);
            ans[i][d] -= len;
            // 空いてるかチェック
            if (check(ans[i])) {
                ld nxt = cur;
                nxt -= calc(S[i], R[i]);
                S[i] = get_s(ans[i]);
                nxt += calc(S[i], R[i]);
                // 良くなれば採用
                if (nxt > cur) {
                    cur = nxt;
                } else {
                    // 状態戻し
                    ans[i][d] += len;
                    S[i] = get_s(ans[i]);
                }
            } else {
                ans[i][d] += len;
            }
            paint(ans[i], i);
        // 正方向
        } else {
            if (ans[i][d]+len > MX) continue;
            erase(ans[i]);
            ans[i][d] += len;
            if (check(ans[i])) {
                ld nxt = cur;
                nxt -= calc(S[i], R[i]);
                S[i] = get_s(ans[i]);
                nxt += calc(S[i], R[i]);
                if (nxt > cur) {
                    cur = nxt;
                } else {
                    ans[i][d] -= len;
                    S[i] = get_s(ans[i]);
                }
            } else {
                ans[i][d] -= len;
            }
            paint(ans[i], i);
        }
    }

    // 最後にN個全部周囲見て、伸ばせるだけ伸ばす
    rep(i, N) {
        if (S[i] >= R[i]) continue;
        rep(d, 4) {
            // 負方向
            if (d < 2) {
                auto tmp = ans[i];
                tmp[d]--;
                while (tmp[d] >= 0 and not used[tmp[0]][tmp[1]] and get_s(tmp) < R[i]) {
                    tmp[d]--;
                }
                tmp[d]++;
                ll len = ans[i][d]-tmp[d];
                assert(ans[i][d]-len >= 0);
                if (len == 0) continue;
                erase(ans[i]);
                ans[i][d] -= len;
                // 空いてるかチェック
                if (check(ans[i])) {
                    ld nxt = cur;
                    nxt -= calc(S[i], R[i]);
                    S[i] = get_s(ans[i]);
                    nxt += calc(S[i], R[i]);
                    // 良くなれば採用
                    if (nxt > cur) {
                        cur = nxt;
                    } else {
                        // 状態戻し
                        ans[i][d] += len;
                        S[i] = get_s(ans[i]);
                    }
                } else {
                    ans[i][d] += len;
                }
                paint(ans[i], i);
            // 正方向
            } else {
                auto tmp = ans[i];
                tmp[d]++;
                while (tmp[d] <= MX and not used[tmp[2]-1][tmp[3]-1] and get_s(tmp) < R[i]) {
                    tmp[d]++;
                }
                tmp[d]--;
                ll len = tmp[d]-ans[i][d];
                assert(ans[i][d]+len <= MX);
                if (len == 0) continue;
                erase(ans[i]);
                ans[i][d] += len;
                if (check(ans[i])) {
                    ld nxt = cur;
                    nxt -= calc(S[i], R[i]);
                    S[i] = get_s(ans[i]);
                    nxt += calc(S[i], R[i]);
                    if (nxt > cur) {
                        cur = nxt;
                    } else {
                        ans[i][d] -= len;
                        S[i] = get_s(ans[i]);
                    }
                } else {
                    ans[i][d] -= len;
                }
                paint(ans[i], i);
            }
            if (S[i] >= R[i]) break;
        }
    }
    // print(cur);
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
